#include "src/ui/widgets/common/login_dialog.h"
#include "src/ui/widgets/widget.h"
#include "src/ui/widgets/patient/patient_main_window.h"
#include <QApplication>
#include <QMessageBox>
#include <QCoreApplication>

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

    // 用于承接登录后要传给主界面的信息
        int loggedInUserId = -1;
        QString loggedInName;
        QString loggedInUserType;

    // TCP → UI（占位处理：弹框 + 可选 accept()）
    QObject::connect(&tcp, &Widget::loginSucceededDetail, &loginDialog,
                         [&](int uid, const QString &name, const QString &type){
        loggedInUserId = uid;
                                 loggedInName   = name;
                                 loggedInUserType = type;
                                 QMessageBox::information(&loginDialog, "登录成功",
                                                          name.isEmpty() ? "欢迎回来！" : ("欢迎回来，" + name));
                                 loginDialog.accept();   // 关闭登录对话框，exec() 将返回 Accepted
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


    // 进入登录框（模态）
        if (loginDialog.exec() == QDialog::Accepted) {
            // 根据用户类型实例化相应主界面，这里先做“患者主界面”
            // 如果将来有 DoctorMainWindow，这里做个分支就行
            PatientMainWindow *mainWin = new PatientMainWindow(loggedInName);
            // 可选：监听主界面退出账号 → 回到登录
            QObject::connect(mainWin, &PatientMainWindow::logoutRequested,
                             [&](){
                                 mainWin->close();
                                 // 重置登录信息
                                 loggedInUserId = -1;
                                 loggedInName.clear();
                                 loggedInUserType.clear();
                                 // 重新弹出登录框（再次走一遍流程）
                                 loginDialog.show();
                                 loginDialog.raise();
                                 loginDialog.activateWindow();
                             });

            mainWin->show();
            return a.exec();   // 真正进入应用事件循环
        }

        // 用户取消/关闭登录框
    return 0;
}
