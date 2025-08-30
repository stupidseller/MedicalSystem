#include "src/ui/widgets/common/login_dialog.h"
#include "src/ui/widgets/patient/patient_main_window.h"
#include <QApplication>
#include <QDialog>

// 声明两个函数，用于管理程序状态
void showLoginDialog();
void showMainWindow(const QString &userName);

// 全局指针，指向当前的主窗口
PatientMainWindow *mainWindow = nullptr;

// 显示主窗口的函数
void showMainWindow(const QString &userName) {
    // 创建并显示主窗口
    mainWindow = new PatientMainWindow(userName);

    // 连接登出信号：当主窗口请求登出时...
    QObject::connect(mainWindow, &PatientMainWindow::logoutRequested, [&]() {
        // 安全地删除当前的主窗口
        mainWindow->deleteLater();
        mainWindow = nullptr;
        // 重新调用显示登录窗口的函数
        showLoginDialog();
    });

    mainWindow->resize(1280, 820);
    mainWindow->show();
}

// 显示登录窗口的函数
void showLoginDialog() {
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // 登录成功，显示主窗口
        // 这里可以从 loginDialog 获真实的用户姓名
        showMainWindow("张患者"); // 使用一个示例名字
    } else {
        // 用户关闭了登录窗口，退出整个应用程序
        qApp->quit();
    }
}

int main(int argc, char *argv[])
{
    // 关键修正：必须在创建 QApplication 对象之前设置这些全局属性
    // 这样可以确保程序在高分辨率屏幕上正确缩放
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);

    // 启动程序，首先显示登录对话框
    showLoginDialog();

    // 启动 Qt 的事件循环
    // 程序将在此处持续运行，直到调用 qApp->quit()
    return a.exec();
}