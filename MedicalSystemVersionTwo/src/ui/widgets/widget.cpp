#include "widget.h"
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QAbstractSocket>

Widget::Widget(QObject *parent)
    : QObject(parent)
{
    init();
}

Widget::~Widget(){}


void Widget::init()
{   // 只创建一次，不要在这里重复 new
    connectStatus = false;

    if (!myTcpClient) {
        myTcpClient = new QTcpSocket(this);
    }

    connect(myTcpClient, &QTcpSocket::connected,
                this,        &Widget::slotConnected);
    connect(myTcpClient, &QTcpSocket::readyRead,
            this,        &Widget::slotReadyRead);
    connect(myTcpClient, &QTcpSocket::disconnected,
            this,        &Widget::slotDisconnected);


    connect(myTcpClient, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
                this,        &Widget::slotError);}


// 当点击连接到服务器按钮时
void Widget::on_connectServerBtn_clicked()
{
    if (connectStatus) return;
    // 如果 serverIp 是域名或 IPv4 字符串，这个重载最稳
    myTcpClient->connectToHost(serverIp, serverPort);
}

void Widget::ensureConnected()
{
    if (!connectStatus) {
        on_connectServerBtn_clicked();
        // 可选：阻塞等待 1 秒（若你允许轻微阻塞）
        // myTcpClient->waitForConnected(1000);
    }
}

void Widget::sendLoginData(const QString &username,
                           const QString &password,
                           const QString &roleText)
{
    QString role = roleText;
    if (role.contains("患")) role = "patient";
    else if (role.contains("医")) role = "doctor";

    QJsonObject obj{
        {"type", "login"},
        {"username", username},
        {"password", password},
        {"role", role}
    };
    QJsonDocument doc(obj);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);
    payload.append('\n');

    ensureConnected();

    if (myTcpClient->state() == QAbstractSocket::ConnectedState) {
        myTcpClient->write(payload);
        myTcpClient->flush();
    } else {
        qDebug() << "[login] not connected";
        // TODO: 需要的话，这里可以把 payload 暂存到队列，等 connected 再发
    }
}

void Widget::sendRegisterData(const QString &username,
                              const QString &email,
                              const QString &password,
                              const QString &userType,
                              const QString &department)
{
    QJsonObject obj{
        {"type", "register"},
        {"username", username},
        {"email", email},
        {"password", password},
        {"user_type", userType}
    };
    if (userType == "doctor"){
        obj.insert("department", department);
    }

    QJsonDocument doc(obj);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);
    payload.append('\n');

    ensureConnected();

    if (myTcpClient->state() == QAbstractSocket::ConnectedState) {
        myTcpClient->write(payload);
        myTcpClient->flush();
    } else {
        qDebug() << "[register] not connected yet, drop this try";
        // TODO: 同上，可排队
    }
}


void Widget::slotConnected()
{
    connectStatus = true;
    qDebug() << "Connected to" << myTcpClient->peerAddress().toString()
             << ":" << myTcpClient->peerPort();
}

//读取服务器发送的信息
void Widget::slotReadyRead()
{
    while (myTcpClient->canReadLine()) {
        const QByteArray line = myTcpClient->readLine().trimmed();
        if (line.isEmpty()) continue;

        QJsonParseError err{};
        QJsonDocument doc = QJsonDocument::fromJson(line, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            qDebug() << "recv (non-json):" << line;
            continue;
        }

        QJsonObject obj = doc.object();
        const QString type = obj.value("type").toString();
        const bool ok = obj.value("success").toBool();
        const QString msg = obj.value("message").toString();

        if (type == "login_result") {
            if (ok) emit loginSucceeded(msg.isEmpty() ? "登录成功" : msg);
            else    emit loginFailed   (msg.isEmpty() ? "用户名或密码错误" : msg);
        } else if (type == "register_result") {
            if (ok) emit registerSucceeded(msg.isEmpty() ? "注册成功" : msg);
            else    emit registerFailed   (msg.isEmpty() ? "注册失败" : msg);
        } else {
            qDebug() << "unknown msg type:" << type << obj;
        }
    }
}

void Widget::slotDisconnected()
{
    qDebug() << "Disconnected";
    connectStatus = false;
}


void Widget::slotError(QAbstractSocket::SocketError error)
{
    qDebug() << "socket error:" << error << myTcpClient->errorString();
    connectStatus = false;
}
//end slots
