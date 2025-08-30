#include "LoginHandler.h"
#include <QDebug> // 用于打印调试信息

LoginHandler::LoginHandler(QObject *parent) : QObject(parent)
{
}

void LoginHandler::loginPatient(const QString &email, const QString &code)
{
    qDebug() << "[C++] Received patient login request. Email:" << email << "Code:" << code;

    // --- 伪代码：未来在这里实现真实的登录逻辑 ---
    // 1. 验证输入是否为空
    // 2. 查询数据库或调用API
    // 3. 根据结果发射不同信号
    if (email == "patient@test.com" && code == "123456") {
        qDebug() << "[C++] Patient login successful.";
        emit loginSuccess(); // 发射登录成功信号
    } else {
        qDebug() << "[C++] Patient login failed.";
        emit loginFailed("邮箱或验证码错误"); // 发射登录失败信号
    }
}

void LoginHandler::loginDoctor(const QString &employeeId, const QString &password)
{
    qDebug() << "[C++] Received doctor login request. Employee ID:" << employeeId;

    // --- 伪代码：未来在这里实现真实的登录逻辑 ---
    if (employeeId == "doc001" && password == "password") {
        qDebug() << "[C++] Doctor login successful.";
        emit loginSuccess();
    } else {
        qDebug() << "[C++] Doctor login failed.";
        emit loginFailed("工号或密码错误");
    }
}