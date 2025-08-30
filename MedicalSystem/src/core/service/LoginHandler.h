#pragma once

#include <QObject>
#include <QString>

class LoginHandler : public QObject
{
Q_OBJECT // 启用信号和槽机制

public:
    explicit LoginHandler(QObject *parent = nullptr);

signals:
    // 定义信号，用于通知QML登录结果
    void loginSuccess();
    void loginFailed(const QString &reason);

public slots:
    // 定义可被QML调用的槽函数
    Q_INVOKABLE void loginPatient(const QString &email, const QString &code);
    Q_INVOKABLE void loginDoctor(const QString &employeeId, const QString &password);
};