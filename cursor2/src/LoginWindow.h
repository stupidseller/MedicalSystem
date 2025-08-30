#pragma once

#include <QWidget>

class QTabWidget;
class QLineEdit;
class QComboBox;
class QPushButton;
class QLabel;
class QFrame;

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void onLogin();
    void onRegister();
    void onUserTypeChanged(int index);

private:
    void buildUi();
    void applyStyle();

    QTabWidget *tabWidget {nullptr};

    // 登录
    QLineEdit *leLoginUser {nullptr};
    QLineEdit *leLoginPwd {nullptr};
    QComboBox *cbLoginRole {nullptr};
    QPushButton *btnLogin {nullptr};

    // 注册（公共）
    QComboBox *cbRegUserType {nullptr}; // 0 患者 1 医生
    QLineEdit *leRegUsername {nullptr};
    QLineEdit *leRegEmail {nullptr};
    QLineEdit *leRegPwd {nullptr};
    QLineEdit *leRegPwd2 {nullptr};
    QPushButton *btnRegister {nullptr};

    // 注册（医生专属）
    QFrame *doctorExtra {nullptr};
    QLineEdit *leStaffId {nullptr};
    QComboBox *cbDepartment {nullptr};
};



