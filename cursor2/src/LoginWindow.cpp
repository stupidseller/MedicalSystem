#include "LoginWindow.h"

#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFrame>

namespace {
static QWidget* buildLeftPanel(QWidget *parent) {
    auto *left = new QFrame(parent);
    left->setObjectName("LeftPanel");
    auto *lay = new QVBoxLayout(left);
    lay->setContentsMargins(32, 32, 32, 32);
    lay->addStretch();
    auto *title = new QLabel("智能医疗系统", left);
    title->setObjectName("Title");
    auto *subtitle = new QLabel("为您提供全面的医疗健康服务", left);
    subtitle->setObjectName("Subtitle");
    lay->addWidget(title, 0, Qt::AlignLeft);
    lay->addSpacing(8);
    lay->addWidget(subtitle, 0, Qt::AlignLeft);
    lay->addStretch();
    return left;
}
}

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    buildUi();
    applyStyle();
}

void LoginWindow::buildUi() {
    auto *root = new QHBoxLayout(this);
    root->setContentsMargins(24, 24, 24, 24);
    root->setSpacing(24);

    auto *left = buildLeftPanel(this);
    left->setMinimumWidth(360);
    root->addWidget(left);

    auto *right = new QFrame(this);
    right->setObjectName("RightCard");
    auto *rightLay = new QVBoxLayout(right);
    rightLay->setContentsMargins(24, 24, 24, 24);

    tabWidget = new QTabWidget(right);
    tabWidget->setObjectName("MainTabs");
    rightLay->addWidget(tabWidget);

    // 登录 Tab
    auto *loginPage = new QWidget(tabWidget);
    auto *g = new QGridLayout(loginPage);
    g->setHorizontalSpacing(12);
    g->setVerticalSpacing(16);
    int row = 0;
    g->addWidget(new QLabel("用户名/邮箱"), row, 0);
    leLoginUser = new QLineEdit; leLoginUser->setPlaceholderText("请输入用户名或邮箱");
    g->addWidget(leLoginUser, row++, 1);

    g->addWidget(new QLabel("密码"), row, 0);
    leLoginPwd = new QLineEdit; leLoginPwd->setEchoMode(QLineEdit::Password); leLoginPwd->setPlaceholderText("请输入密码");
    g->addWidget(leLoginPwd, row++, 1);

    g->addWidget(new QLabel("登录身份"), row, 0);
    cbLoginRole = new QComboBox; cbLoginRole->addItems({"患者","医生","管理员"});
    g->addWidget(cbLoginRole, row++, 1);

    btnLogin = new QPushButton("登录");
    g->addWidget(btnLogin, row, 0, 1, 2);
    g->setRowMinimumHeight(row++, 48);
    g->setColumnStretch(1, 1);

    tabWidget->addTab(loginPage, "登录");

    // 注册 Tab
    auto *registerPage = new QWidget(tabWidget);
    auto *rg = new QGridLayout(registerPage);
    rg->setHorizontalSpacing(12);
    rg->setVerticalSpacing(16);
    int r = 0;

    rg->addWidget(new QLabel("选择用户类型"), r, 0);
    cbRegUserType = new QComboBox; cbRegUserType->addItems({"患者","医生"});
    rg->addWidget(cbRegUserType, r++, 1);

    rg->addWidget(new QLabel("用户名"), r, 0);
    leRegUsername = new QLineEdit; leRegUsername->setPlaceholderText("请设置用户名");
    rg->addWidget(leRegUsername, r++, 1);

    rg->addWidget(new QLabel("邮箱"), r, 0);
    leRegEmail = new QLineEdit; leRegEmail->setPlaceholderText("请输入邮箱");
    rg->addWidget(leRegEmail, r++, 1);

    rg->addWidget(new QLabel("密码"), r, 0);
    leRegPwd = new QLineEdit; leRegPwd->setEchoMode(QLineEdit::Password); leRegPwd->setPlaceholderText("请设置密码（至少6位）");
    rg->addWidget(leRegPwd, r++, 1);

    rg->addWidget(new QLabel("确认密码"), r, 0);
    leRegPwd2 = new QLineEdit; leRegPwd2->setEchoMode(QLineEdit::Password); leRegPwd2->setPlaceholderText("请再次输入密码");
    rg->addWidget(leRegPwd2, r++, 1);

    // 医生额外信息
    doctorExtra = new QFrame(registerPage);
    auto *dg = new QGridLayout(doctorExtra);
    dg->setHorizontalSpacing(12);
    dg->setVerticalSpacing(16);
    int dr = 0;
    dg->addWidget(new QLabel("工号"), dr, 0);
    leStaffId = new QLineEdit; leStaffId->setPlaceholderText("请输入工号");
    dg->addWidget(leStaffId, dr++, 1);
    dg->addWidget(new QLabel("科室"), dr, 0);
    cbDepartment = new QComboBox; cbDepartment->addItems({"内科","外科","儿科","骨科","口腔科","影像科"});
    dg->addWidget(cbDepartment, dr++, 1);
    rg->addWidget(doctorExtra, r++, 0, 1, 2);

    btnRegister = new QPushButton("注册");
    rg->addWidget(btnRegister, r, 0, 1, 2);
    rg->setRowMinimumHeight(r, 48);
    rg->setColumnStretch(1, 1);

    tabWidget->addTab(registerPage, "注册");

    root->addWidget(right, 1);

    connect(btnLogin, &QPushButton::clicked, this, &LoginWindow::onLogin);
    connect(btnRegister, &QPushButton::clicked, this, &LoginWindow::onRegister);
    connect(cbRegUserType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LoginWindow::onUserTypeChanged);

    onUserTypeChanged(0);
}

void LoginWindow::applyStyle() {
    setStyleSheet(
        "#LeftPanel {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #2b9bd8, stop:1 #27445b);"
        "  border-radius: 16px;"
        "}"
        "#RightCard {"
        "  background: white;"
        "  border-radius: 16px;"
        "}"
        "#Title { color: white; font-size: 28px; font-weight: 700; }"
        "#Subtitle { color: rgba(255,255,255,0.9); font-size: 14px; }"
        "QTabBar::tab { padding: 10px 24px; }"
        "QPushButton { height: 40px; border-radius: 6px; background: qlineargradient(x1:0,y1:0,x2:1,y2:0, stop:0 #2da7f2, stop:1 #27445b); color: white; }"
        "QLineEdit, QComboBox { height: 36px; }"
    );
}

void LoginWindow::onLogin() {
    const QString user = leLoginUser->text().trimmed();
    const QString pwd = leLoginPwd->text();
    const QString role = cbLoginRole->currentText();
    if (user.isEmpty() || pwd.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入用户名和密码");
        return;
    }
    if (pwd.size() < 6) {
        QMessageBox::warning(this, "提示", "密码长度至少为 6 位");
        return;
    }
    QMessageBox::information(this, "登录成功", QString("欢迎 %1（%2）").arg(user, role));
}

void LoginWindow::onRegister() {
    const bool isDoctor = cbRegUserType->currentIndex() == 1;
    const QString username = leRegUsername->text().trimmed();
    const QString email = leRegEmail->text().trimmed();
    const QString pwd1 = leRegPwd->text();
    const QString pwd2 = leRegPwd2->text();

    if (username.isEmpty() || email.isEmpty() || pwd1.isEmpty() || pwd2.isEmpty()) {
        QMessageBox::warning(this, "提示", "请完整填写信息");
        return;
    }
    if (pwd1.size() < 6) {
        QMessageBox::warning(this, "提示", "密码长度至少为 6 位");
        return;
    }
    if (pwd1 != pwd2) {
        QMessageBox::warning(this, "提示", "两次输入的密码不一致");
        return;
    }

    if (isDoctor) {
        if (leStaffId->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "提示", "请输入工号");
            return;
        }
    }

    QString extra;
    if (isDoctor) {
        extra = QString(" 工号:%1 科室:%2").arg(leStaffId->text().trimmed(), cbDepartment->currentText());
    }
    QMessageBox::information(this, "注册成功", QString("用户 %1（%2）注册成功！%3")
                             .arg(username, isDoctor ? "医生" : "患者", extra));
}

void LoginWindow::onUserTypeChanged(int index) {
    const bool isDoctor = (index == 1);
    doctorExtra->setVisible(isDoctor);
}



