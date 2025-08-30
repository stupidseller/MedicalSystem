#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QNetworkAccessManager> // 包含网络头文件

// 前置声明
class QStackedWidget;
class QLineEdit;
class QPushButton;
class QComboBox;
class QNetworkReply;
class QLabel; // 添加 QLabel 的前置声明

class LoginDialog : public QDialog
{
Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void onLoginTabClicked();
    void onRegisterTabClicked();
    void onPatientTypeClicked();
    void onDoctorTypeClicked();
    void onLoginAttempt();
    void onRegisterAttempt();
    void onRegistrationReply(QNetworkReply *reply);

private:
    void initLayout();
    void initStyleSheets();
    QWidget* createLeftPanel();
    QWidget* createRightPanel();
    QWidget* createLoginWidget();
    QWidget* createRegisterWidget();

    // 控件指针
    QStackedWidget *mainStackedWidget;
    QPushButton *loginTabButton;
    QPushButton *registerTabButton;
    QLineEdit *loginUserLineEdit;
    QLineEdit *loginPasswordLineEdit;
    QComboBox *loginRoleComboBox;
    QPushButton *patientTypeButton;
    QPushButton *doctorTypeButton;
    QLineEdit *registerUserLineEdit;
    QLineEdit *registerEmailLineEdit;
    QLineEdit *registerPasswordLineEdit;
    QLineEdit *registerConfirmPasswordLineEdit;

    // 为科室选择添加的控件
    QLabel *departmentLabel;
    QComboBox *registerDepartmentComboBox;

    QNetworkAccessManager *networkManager;
    QString selectedUserType; // 用于跟踪注册类型 (patient/doctor)
};

#endif // LOGIN_DIALOG_H