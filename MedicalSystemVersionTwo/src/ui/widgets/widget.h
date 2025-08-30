#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

class Widget : public QObject
{
    Q_OBJECT

public:
    explicit Widget(QObject *parent = nullptr);
    ~Widget();
signals:
    // 登录结果
    void loginSucceeded(const QString &message);
    void loginFailed(const QString &message);

    // 注册结果
    void registerSucceeded(const QString &message);
    void registerFailed(const QString &message);

public slots:
    void on_connectServerBtn_clicked();

    // 新增：给 LoginDialog 连接的槽
    void sendLoginData(const QString &username,
                       const QString &password,
                       const QString &roleText);

    void sendRegisterData(const QString &username,
                          const QString &email,
                          const QString &password,
                          const QString &userType,
                          const QString &department);

private slots:
    void slotConnected();
        void slotReadyRead();
        void slotDisconnected();
        void slotError(QAbstractSocket::SocketError error);
private:
    void init();
    void ensureConnected();
private:
    QTcpSocket *myTcpClient = nullptr;
    bool connectStatus = false;

    // 你可以改成配置读取
    QString serverIp   = "192.168.253.136";
    quint16 serverPort = 9999;
};
#endif // WIDGET_H
