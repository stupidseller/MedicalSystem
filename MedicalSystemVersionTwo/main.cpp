#include "src/ui/widgets/common/login_dialog.h"
#include "src/ui/widgets/widget.h"
#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);

    Widget tcp(&a);
    tcp.on_connectServerBtn_clicked(); // 可选：开机连

    // 2) 创建登录对话框
    LoginDialog loginDialog;

    // 3)  UI → TCP | 连接信号 → 槽（这一步就是让 emit “调用东西”）
    QObject::connect(&loginDialog, &LoginDialog::loginRequested,
                         &tcp,        &Widget::sendLoginData);
    QObject::connect(&loginDialog, &LoginDialog::registerRequested,
                         &tcp,        &Widget::sendRegisterData);

    // TCP → UI（占位处理：弹框 + 可选 accept()）
    QObject::connect(&tcp, &Widget::loginSucceeded, &loginDialog,
                         [&](const QString &msg){
                             QMessageBox::information(&loginDialog, "登录成功",
                                                      msg.isEmpty() ? "欢迎回来！" : msg);
                             // 预留：成功后关闭登录框 → main里 exec() 返回 Accepted
                             loginDialog.accept();
                         });

    QObject::connect(&tcp, &Widget::loginFailed, &loginDialog,
                     [&](const QString &msg){
                         QMessageBox::warning(&loginDialog, "登录失败",
                                               msg.isEmpty() ? "请检查账号或密码" : msg);
                         // 失败不关闭，留在登录页
                     });

    QObject::connect(&tcp, &Widget::registerSucceeded, &loginDialog,
                     [&](const QString &msg){
                         QMessageBox::information(&loginDialog, "注册成功",
                                                  msg.isEmpty() ? "账户已创建，请登录" : msg);
                         // 注册成功 → 回到登录页，但不关闭对话框
                         loginDialog.onLoginTabClicked();
                     });
    QObject::connect(&tcp, &Widget::registerFailed, &loginDialog,
                     [&](const QString &msg){
                         QMessageBox::warning(&loginDialog, "注册失败",
                                               msg.isEmpty() ? "请检查注册信息" : msg);
                     });


    if (loginDialog.exec() == QDialog::Accepted) {
            QMessageBox::information(nullptr, "占位提示", "（预留）这里将切换到主页面。");
            return 0;
    }

    // 用户取消/关闭登录框，则退出程序
    return 0;
}
