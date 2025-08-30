#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QIntValidator>
#include <QSqlRecord>
#include <QJsonObject>
#include <QMap>
#include <QJsonParseError>
const int MAXLINK = 99;//最大连接数

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // init sql
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("hospital_management.db");

    if( !db.open() ) {
        QMessageBox::critical(this, "Error", "Open database fail");
        return;
    }

    QSqlQuery query;
        if (!query.exec("SELECT user_id, phone FROM users")) {
            QMessageBox::critical(this, "SQL Error", "数据库查询失败");
            return;
        }
    init();
}

Widget::~Widget()
{
    delete ui;
}

//初始化函数,根据个人的编程习惯处理即可
void Widget::init()
{
    //1 创建一个TcpServer对象
    myTcpServer = new QTcpServer(this);
    //设置端口可输入的范围,端口范围的选择是在合理的范围内,需要学生理解基本的端口概念
    ui->serverPort->setValidator(new QIntValidator(1, 65535, this));
    ui->clientPort->setValidator(new QIntValidator(1, 65535, this));
}

//启动服务器使之监听响应端口,接受来自客户端的连接请求
void Widget::on_startServerBtn_clicked()
{
    qDebug() << "on_startServerBtn_clicked()";
    QString ipAddress;//字符串的地址形式,因为用户的输入应该都是字符串

    //方法1.手动获>取用户手工输入的ip地址
    ipAddress = ui->serverIP->text();
    if(ipAddress.isEmpty()){//如果没有手动设置ip地址,则自动获取
        //方法2.遍历服务器所有ip
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        qDebug() << ipAddressesList;
        // 默认情况下使用本地的非localhost127.0.0.1的本地IPV4地址
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                ui->serverIP->setText(ipAddress);
                break;
            }
        }
    }
//    qDebug() << ipAddress;

    //获取端口
    QString port = ui->serverPort->text();
    if(port.isEmpty()){//如果没有输入端口号,则默认使用一个端口号
        port = "9999";
        ui->serverPort->setText(port);
    }

    //在指定的IP和端口绑定并启动监听
    bool result = myTcpServer->listen(QHostAddress(ipAddress),(qint16)(port.toInt()));
    if(!result){
        //QMessageBox::warning(this,"错误","不能绑定启动");
        ui->tips->setPlainText(QString("服务器在[%1:%2]上绑定失败").arg(ipAddress).arg(port));
        return;
    }else{
       ui->tips->setPlainText(QString("服务器在[%1:%2]上绑定成功").arg(ipAddress).arg(port));
       ui->startServerBtn->setDisabled(true);//绑定启动成功后设置按钮为禁用状态
    }

    //设置最大连接数,可以通过常量设定
    myTcpServer->setMaxPendingConnections(MAXLINK);
    //接受用户的连接,通过信号和槽的方式实现,不是传统的while循环监听
    //如果有新客户端接入时(这就是信号和槽的好处)
    connect(myTcpServer, &QTcpServer::newConnection, this, &Widget::slotNewConnection);
    //Qt4的信号和槽的处理方式,确保出错可以得到处理
    connect(myTcpServer,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(slotAcceptError(QAbstractSocket::SocketError)));
}
//有一个新的客户端连入时
void Widget::slotNewConnection()
{
    qDebug() << "slotNewConnection()";
    //获取新创建连接的客户端对象
    myTcpClient = myTcpServer->nextPendingConnection();
    //将新连入的客户端加入到客户端列表中
    clients.append(myTcpClient);
    //客户端有消息发送过来时,读取消息并显示
    connect(myTcpClient, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    //客户端断开时,主要处理提示信息和更新客户端列表
    connect(myTcpClient,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    //客户端接入,主要处理提示信息并更新客户端列表
    connect(myTcpClient,SIGNAL(connected()),this,SLOT(slotConnected()));
    QString msg = QString("客户端[%1:%2]已经接入").
            arg(myTcpClient->peerAddress().toString()).
            arg(myTcpClient->peerPort());
    ui->tips->append(msg);
}
//客户端连接成功准备读取信息
void Widget::slotReadyRead()
{
    qDebug() << "slotReadyRead()";

    QTcpSocket *sock = qobject_cast<QTcpSocket*>(sender());
    if (!sock) return;

    // 追加到该socket的缓冲
    QByteArray &buf = recvBuf[sock];
    buf.append(sock->readAll());

    // 一次处理多条行消息
        while (true) {
            int nl = buf.indexOf('\n');
            if (nl < 0) break;                 // 没有完整一行，等下次
            QByteArray line = buf.left(nl);    // 取一行（不含换行）
            buf.remove(0, nl + 1);             // 丢弃这一行（含换行）

            if (line.trimmed().isEmpty()) continue;

            // 解析JSON
            QJsonParseError perr{};
            QJsonDocument doc = QJsonDocument::fromJson(line, &perr);
            if (perr.error != QJsonParseError::NoError || !doc.isObject()) {
                qDebug() << "recv invalid json:" << line;
                // 不知道具体类型，统一报错
                sendJson(sock, QJsonObject{
                    {"type","error"},
                    {"success",false},
                    {"message","invalid json"}
                });
                continue;
               }

               handleMessage(sock, doc.object());
          }
}
//客户端连接错误时的处理方式
void Widget::slotAcceptError(QAbstractSocket::SocketError error)
{
    qDebug() << "slotAcceptError(QAbstractSocket::SocketError error)" << error;
}

//客户端断开连接时
void Widget::slotDisconnected()
{
    qDebug() << "slotDisconnected()";
    //获取信号的发送者QObject对象,需要强转为客户端对象
    QTcpSocket * currentClient = qobject_cast<QTcpSocket *>(this->sender());
    QString msg = QString("客户端[%1:%2]退出").arg(currentClient->peerAddress().toString()).arg(currentClient->peerPort());
    ui->tips->append(msg);

    //退出时删除客户端,如果和当前发送信号的客户端的ip和端口完全相同,则从客户端队列中删除
    for(int i=0;i < clients.length();i++){
        if(clients.at(i)->peerAddress() == currentClient->peerAddress() &&
            clients.at(i)->peerPort() == currentClient->peerPort()){
            clients.removeAt(i);//移除对应的客户端
            break;
        }
    }
}
//给客户端发送信息
void Widget::on_clientSendBtn_clicked()
{
    qDebug() << "on_clientSendBtn_clicked()";
    //获取客户端的ip和port
    QString clientIp = ui->clientIp->text();
    QString clientPort = ui->clientPort->text();
    //遍历客户端列表,匹配是否存在该客户端
    qDebug() << clients.size();
    for(int i=0;i < clients.size();i++){
        //如果ip和port都是在客户端列表存在
        if(clients.at(i)->peerAddress().toString()==clientIp &&
            clients.at(i)->peerPort() == clientPort.toInt()){
            QString msg = ui->message->toPlainText();//获取文本框内容
            clients.at(i)->write(msg.toUtf8());//将信息写入客户端,避免乱码的产生使用了utf8
            ui->tips->append(msg);
            break;
        }
    }
    ui->message->clear();//点击发送按钮后清空文本框区域
}

void Widget::slotConnected()
{
    QTcpSocket * currentClient = qobject_cast<QTcpSocket *>(this->sender());
    QString msg = QString("客户端[%1:%2]已连接").arg(currentClient->peerAddress().toString()).arg(currentClient->peerPort());
    ui->tips->append(msg);
}

void Widget::handleMessage(QTcpSocket *sock, const QJsonObject &obj)
{
    const QString type = obj.value("type").toString();
    if (type == "login") {
        handleLogin(sock, obj);
    } else if (type == "register") {
        handleRegister(sock, obj);
    } else {
        qDebug() << "unknown type:" << type << obj;
        sendError(sock, "error", QString("unknown type: %1").arg(type));
    }
}

void Widget::handleLogin(QTcpSocket *sock, const QJsonObject &obj)
{
    const QString userOrEmailOrPhone = obj.value("username").toString().trimmed();
    const QString password    = obj.value("password").toString();
    const QString role        = obj.value("role").toString().trimmed(); // 'patient'/'doctor'

    if (userOrEmailOrPhone.isEmpty() || password.isEmpty() || role.isEmpty()) {
        sendJson(sock, QJsonObject{
            {"type","login_result"},
            {"success",false},
            {"message","参数不完整"}
        });
        return;
    }

    // 用默认连接查询
    QSqlQuery q;
    q.prepare(R"SQL(
            SELECT user_id, user_type, name
            FROM users
            WHERE (name = :id OR email = :id OR phone = :id)
              AND password = :pwd
              AND user_type = :role
            LIMIT 1
        )SQL");
        q.bindValue(":id",   userOrEmailOrPhone);
        q.bindValue(":pwd",  password);
        q.bindValue(":role", role);

        if (!q.exec()) {
                qWarning() << "[login] SQL error:" << q.lastError().text();
                sendJson(sock, QJsonObject{{"type","login_result"},{"success",false},{"message","数据库错误"}});
                return;
            }

        if (q.next()) {
                const int userId       = q.value("user_id").toInt();
                const QString userType = q.value("user_type").toString();
                const QString name     = q.value("name").toString();
                sendJson(sock, QJsonObject{
                    {"type","login_result"},
                    {"success",true},
                    {"message","登录成功"},
                    {"user_id",userId},
                    {"user_type",userType},
                    {"name",name}
                });
            } else {
                sendJson(sock, QJsonObject{{"type","login_result"},{"success",false},{"message","用户名/邮箱/手机或密码/身份不匹配"}});
            }
        }

void Widget::handleRegister(QTcpSocket *sock, const QJsonObject &obj)
{
    const QString name      = obj.value("username").toString().trimmed(); // 前端叫 username，这里映射到 name
    const QString email     = obj.value("email").toString().trimmed();
    const QString password  = obj.value("password").toString();
    const QString userType  = obj.value("user_type").toString().trimmed(); // 'patient'/'doctor'
    // const QString department = obj.value("department").toString().trimmed(); // 表里没有，忽略

    if (name.isEmpty() || password.isEmpty() || userType.isEmpty()) {
        sendJson(sock, QJsonObject{{"type","register_result"},{"success",false},{"message","参数不完整"}});
        return;
    }
    if (!email.isEmpty() && !email.contains('@')) {
        sendJson(sock, QJsonObject{{"type","register_result"},{"success",false},{"message","邮箱格式不正确"}});
        return;
    }
    if (userType != "patient" && userType != "doctor") {
        sendJson(sock, QJsonObject{{"type","register_result"},{"success",false},{"message","用户类型非法"}});
        return;
    }

    // 先查重（email 唯一，name 非唯一，这里可选校验 email）
    if (!email.isEmpty()) {
        QSqlQuery check;
        check.prepare("SELECT 1 FROM users WHERE email = :e LIMIT 1");
        check.bindValue(":e", email);
        if (!check.exec()) {
            qWarning() << "[register] check email error:" << check.lastError().text();
            sendJson(sock, QJsonObject{{"type","register_result"},{"success",false},{"message","数据库错误"}});
            return;
        }
        if (check.next()) {
            sendJson(sock, QJsonObject{{"type","register_result"},{"success",false},{"message","该邮箱已被注册"}});
            return;
        }
    }

    // 插入（性别/生日/手机号/证件号可为空；created_at/updated_at 有默认值）
    QSqlQuery ins;
    ins.prepare(R"SQL(
        INSERT INTO users(user_type, name, email, password)
        VALUES(:t, :n, :e, :p)
    )SQL");
    ins.bindValue(":t", userType);
    ins.bindValue(":n", name);
    if (email.isEmpty())
        ins.bindValue(":e", QVariant(QVariant::String)); // NULL
    else
        ins.bindValue(":e", email);
    ins.bindValue(":p", password); // 先明文，后续可替换为哈希

    if (!ins.exec()) {
        qWarning() << "[register] insert error:" << ins.lastError().text();
        sendJson(sock, QJsonObject{{"type","register_result"},{"success",false},{"message","插入失败（数据库错误）"}});
        return;
    }

    sendJson(sock, QJsonObject{{"type","register_result"},{"success",true},{"message","注册成功"}});
}


void Widget::sendJson(QTcpSocket *sock, const QJsonObject &obj)
{
    QJsonDocument doc(obj);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);
    payload.append('\n'); // 按行协议
    sock->write(payload);
    sock->flush();
}

void Widget::sendError(QTcpSocket *sock, const QString &type, const QString &msg)
{
    sendJson(sock, QJsonObject{
        {"type", type},
        {"success", false},
        {"message", msg}
    });
}
