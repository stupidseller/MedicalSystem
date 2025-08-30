#include "patient_main_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QTimer>
#include <QSvgWidget>
#include <QLocale>
#include <QMouseEvent>
#include <QApplication>
#include <QAction>
#include <QEvent>
#include <QPoint>


const char* userIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-user"><path d="M20 21v-2a4 4 0 0 0-4-4H8a4 4 0 0 0-4 4v2"></path><circle cx="12" cy="7" r="4"></circle></svg>)";
const char* clipboardIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-clipboard"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg>)";
const char* userMdIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-user-check"><path d="M16 21v-2a4 4 0 0 0-4-4H5a4 4 0 0 0-4 4v2"></path><circle cx="8.5" cy="7" r="4"></circle><polyline points="17 11 19 13 23 9"></polyline></svg>)";
const char* historyIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-clock"><circle cx="12" cy="12" r="10"></circle><polyline points="12 6 12 12 16 14"></polyline></svg>)";
const char* calendarIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-calendar"><rect x="3" y="4" width="18" height="18" rx="2" ry="2"></rect><line x1="16" y1="2" x2="16" y2="6"></line><line x1="8" y1="2" x2="8" y2="6"></line><line x1="3" y1="10" x2="21" y2="10"></line></svg>)";
const char* stethoscopeIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M5 3.34a1 1 0 0 1 1.33-1.33L18.67 14a1 1 0 0 1-1.33 1.33L5 3.34zM12 18a6 6 0 1 1 0-12 6 6 0 0 1 0 12zM12 22a4 4 0 1 0 0-8 4 4 0 0 0 0 8z"/></svg>)";
const char* prescriptionIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-file-text"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"></path><polyline points="14 2 14 8 20 8"></polyline><line x1="16" y1="13" x2="8" y2="13"></line><line x1="16" y1="17" x2="8" y2="17"></line><polyline points="10 9 9 9 8 9"></polyline></svg>)";
const char* messageIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-message-circle"><path d="M21 11.5a8.38 8.38 0 0 1-.9 3.8 8.5 8.5 0 0 1-7.6 4.7 8.38 8.38 0 0 1-3.8-.9L3 21l1.9-5.7a8.38 8.38 0 0 1-.9-3.8 8.5 8.5 0 0 1 4.7-7.6 8.38 8.38 0 0 1 3.8-.9h.5a8.48 8.48 0 0 1 8 8v.5z"></path></svg>)";
const char* heartIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-heart"><path d="M20.84 4.61a5.5 5.5 0 0 0-7.78 0L12 5.67l-1.06-1.06a5.5 5.5 0 0 0-7.78 7.78l1.06 1.06L12 21.23l7.78-7.78 1.06-1.06a5.5 5.5 0 0 0 0-7.78z"></path></svg>)";
const char* pillsIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="10"/><path d="M12 2a10 10 0 0 0-4.47 18.53m8.94-18.53A10 10 0 0 1 22 12"/><path d="M2 12a10 10 0 0 1 5.53-8.94"/></svg>)";
const char* cardIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-credit-card"><rect x="1" y="4" width="22" height="16" rx="2" ry="2"></rect><line x1="1" y1="10" x2="23" y2="10"></line></svg>)";
const char* hospitalIcon = R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M3 9V7a2 2 0 0 1 2-2h14a2 2 0 0 1 2 2v2"/><path d="M3 9h18v10a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V9z"/><path d="M8 13h1v4H8zM12 13h1v4h-1zM16 13h1v4h-1z"/></svg>)";


PatientMainWindow::PatientMainWindow(const QString &userName, QWidget *parent)
        : QMainWindow(parent)
{
    initUI();
    initStyleSheets();

    // 查找 userNameLabel 并设置文本
    userNameLabel = findChild<QLabel*>("userNameLabel");
    if (userNameLabel) {
        userNameLabel->setText(userName);
        // 允许 QLabel 接收鼠标事件
        userNameLabel->setMouseTracking(true);
        userNameLabel->installEventFilter(this); // 安装事件过滤器来捕获鼠标进入/离开事件
    }

    dateTimeLabel = findChild<QLabel*>("dateTimeLabel");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PatientMainWindow::updateDateTime);
    timer->start(1000);
    updateDateTime();

    setWindowTitle("智慧医院自助服务平台");

    // 创建用户菜单
    userMenu = new QMenu(this);
    userMenu->addSeparator();
    QAction *logoutAction = userMenu->addAction("退出账号");
    connect(logoutAction, &QAction::triggered, this, &PatientMainWindow::onLogoutTriggered);
}

PatientMainWindow::~PatientMainWindow() {}

bool PatientMainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == userNameLabel) {
        if (event->type() == QEvent::Enter) {
            // 鼠标进入，显示菜单
            showUserMenu();
            return true;
        } else if (event->type() == QEvent::Leave) {
            // 鼠标离开，延迟隐藏菜单，以防用户正要移动到菜单上
            QTimer::singleShot(150, this, [this](){
                // 只有当鼠标指针既不在用户名上，也不在菜单上时，才隐藏菜单
                if (userNameLabel && !userNameLabel->geometry().contains(userNameLabel->mapFromGlobal(QCursor::pos())) &&
                    userMenu && !userMenu->geometry().contains(QCursor::pos())) {
                    userMenu->hide();
                }
            });
            return true;
        }
    }
    // 对于其他对象的其他事件，交还给基类处理
    return QMainWindow::eventFilter(obj, event);
}

void PatientMainWindow::initUI() {
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralDashboardWidget");

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(40, 30, 40, 30);
    mainLayout->setSpacing(25);

    mainLayout->addWidget(createHeaderWidget("")); // 初始用户名设为空，由构造函数填充
    mainLayout->addWidget(createAdvicePanel());
    mainLayout->addWidget(createGridWidget());
    mainLayout->addStretch();
    mainLayout->addWidget(createFooterWidget());

    setCentralWidget(centralWidget);
}

QWidget* PatientMainWindow::createHeaderWidget(const QString &userName) {
    QWidget *headerWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(headerWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *titleLabel = new QLabel("智慧医院自助服务平台");
    titleLabel->setObjectName("headerTitleLabel");

    QLabel *dtLabel = new QLabel();
    dtLabel->setObjectName("dateTimeLabel");
    dtLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QLabel *userLabel = new QLabel(userName);
    userLabel->setObjectName("userNameLabel");
    userLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    layout->addWidget(titleLabel);
    layout->addStretch();
    layout->addWidget(dtLabel);
    layout->addSpacing(20);
    layout->addWidget(userLabel);

    return headerWidget;
}

QWidget* PatientMainWindow::createAdvicePanel() {
    QWidget *panel = new QWidget();
    panel->setObjectName("advicePanel");

    QHBoxLayout *layout = new QHBoxLayout(panel);
    layout->setSpacing(15);

    QLabel *title = new QLabel("医生建议");
    title->setObjectName("adviceTitle");

    QLabel *text = new QLabel("根据您的健康状况，建议您定期监测血压，保持低盐饮食，每周至少进行3次有氧运动。请按时服用处方药物，如有任何不适请及时与医生沟通。");
    text->setObjectName("adviceText");
    text->setWordWrap(true);

    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->addWidget(title);
    textLayout->addWidget(text);

    layout->addLayout(textLayout);

    return panel;
}

QWidget* PatientMainWindow::createGridWidget() {
    QWidget *gridContainer = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(gridContainer);
    gridLayout->setSpacing(25);

    gridLayout->addWidget(createDashboardButton(userIcon, "个人信息", "查看和编辑个人资料", "btnPersonalInfo"), 0, 0);
    gridLayout->addWidget(createDashboardButton(clipboardIcon, "挂号服务", "预约和在线挂号", "btnAppointments"), 0, 1);
    gridLayout->addWidget(createDashboardButton(userMdIcon, "医生信息", "查看医生资料和专业", "btnDoctorInfo"), 0, 2);
    gridLayout->addWidget(createDashboardButton(historyIcon, "我的病历", "查看历史就诊记录", "btnMedicalHistory"), 0, 3);
    gridLayout->addWidget(createDashboardButton(calendarIcon, "预约就诊", "预约医生和门诊时间", "btnFollowUp"), 1, 0);
    gridLayout->addWidget(createDashboardButton(stethoscopeIcon, "查看医嘱", "查看医生嘱咐和建议", "btnDoctorsOrders"), 1, 1);
    gridLayout->addWidget(createDashboardButton(prescriptionIcon, "电子处方", "查看医生开具的处方", "btnEPrescription"), 1, 2);
    gridLayout->addWidget(createDashboardButton(messageIcon, "医患沟通", "与医生在线交流", "btnCommunication"), 1, 3);
    gridLayout->addWidget(createDashboardButton(heartIcon, "健康评估", "进行健康状况评估", "btnHealthAssessment"), 2, 0);
    gridLayout->addWidget(createDashboardButton(pillsIcon, "药品搜索", "查询药品详情和使用方法", "btnMedSearch"), 2, 1);
    gridLayout->addWidget(createDashboardButton(cardIcon, "线上支付", "缴纳医疗费用", "btnOnlinePayment"), 2, 2);
    gridLayout->addWidget(createDashboardButton(hospitalIcon, "住院信息", "查看住院详细情况", "btnHospitalization"), 2, 3);

    return gridContainer;
}

QWidget* PatientMainWindow::createDashboardButton(const QString &svgIconData, const QString &title, const QString &subtitle, const QString &objectName) {
    QPushButton *button = new QPushButton();
    button->setObjectName(objectName);
    button->setMinimumSize(220, 120);

    QVBoxLayout *layout = new QVBoxLayout(button);
    layout->setContentsMargins(20, 15, 20, 15);
    layout->setSpacing(5);

    QSvgWidget *icon = new QSvgWidget();
    icon->load(QByteArray(svgIconData.toUtf8()));
    icon->setFixedSize(36, 36);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setObjectName("buttonTitle");

    QLabel *subtitleLabel = new QLabel(subtitle);
    subtitleLabel->setObjectName("buttonSubtitle");

    layout->addWidget(icon, 0, Qt::AlignLeft);
    layout->addStretch();
    layout->addWidget(titleLabel, 0, Qt::AlignLeft);
    layout->addWidget(subtitleLabel, 0, Qt::AlignLeft);

    return button;
}

QWidget* PatientMainWindow::createFooterWidget() {
    QWidget *footerWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(footerWidget);
    QLabel *footerLabel = new QLabel("智慧医疗自助服务平台");
    footerLabel->setObjectName("footerLabel");
    footerLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(footerLabel);
    return footerWidget;
}

void PatientMainWindow::updateDateTime() {
    if (dateTimeLabel) {
        QLocale locale(QLocale::Chinese, QLocale::China);
        QString dateTimeString = locale.toString(QDateTime::currentDateTime(), "yyyy.MM.dd HH:mm:ss dddd");
        dateTimeLabel->setText(dateTimeString);
    }
}

void PatientMainWindow::showUserMenu() {
    if (userNameLabel && userMenu) {
        QPoint pos = userNameLabel->mapToGlobal(QPoint(userNameLabel->width() - userMenu->sizeHint().width(), userNameLabel->height()));
        userMenu->popup(pos);
    }
}

void PatientMainWindow::onLogoutTriggered() {
    userMenu->hide();
    emit logoutRequested();
    close();
}

void PatientMainWindow::initStyleSheets() {
    QString qss = R"(
        #centralDashboardWidget {
            background-color: #F7FAFC;
            font-family: "Microsoft YaHei", sans-serif;
        }
        #headerTitleLabel {
            font-size: 24px;
            font-weight: bold;
            color: #2D3748;
        }
        #dateTimeLabel {
            font-size: 16px;
            color: #4A5568;
        }
        #userNameLabel {
            font-size: 16px;
            color: #2B6CB0;
            font-weight: bold;
            padding: 5px;
        }
        #userNameLabel:hover {
            color: #3182CE;
            background-color: #EBF8FF;
            border-radius: 5px;
        }
        QMenu {
            background-color: white;
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            padding: 5px;
        }
        QMenu::item {
            padding: 8px 25px 8px 15px;
            background-color: transparent;
            color: #2D3748;
            font-size: 14px;
        }
        QMenu::item:selected {
            background-color: #EBF8FF;
            border-radius: 5px;
        }
        QMenu::separator {
            height: 1px;
            background-color: #E2E8F0;
            margin: 5px 0px;
        }
        #advicePanel {
            background-color: #EBF8FF;
            border-radius: 8px;
            padding: 20px;
        }
        #adviceTitle {
            font-size: 16px;
            font-weight: bold;
            color: #2B6CB0;
        }
        #adviceText {
            font-size: 14px;
            color: #2C5282;
        }
        QPushButton {
            border-radius: 12px;
            border: 1px solid transparent;
            text-align: left;
            color: white;
        }
        QPushButton:hover {
            border: 1px solid rgba(255, 255, 255, 0.7);
        }
        #buttonTitle {
            font-size: 18px;
            font-weight: bold;
            background: none;
        }
        #buttonSubtitle {
            font-size: 13px;
            color: rgba(255, 255, 255, 0.8);
            background: none;
        }
        #btnPersonalInfo { background-color: #4299E1; }
        #btnAppointments { background-color: #48BB78; }
        #btnDoctorInfo { background-color: #9F7AEA; }
        #btnMedicalHistory { background-color: #ED8936; }
        #btnFollowUp { background-color: #F6E05E; color: #2D3748; }
        #btnFollowUp #buttonSubtitle, #btnFollowUp #buttonTitle { color: #2D3748; }
        #btnDoctorsOrders { background-color: #ECC94B; color: #2D3748; }
        #btnDoctorsOrders #buttonSubtitle, #btnDoctorsOrders #buttonTitle { color: #2D3748; }
        #btnEPrescription { background-color: #F56565; }
        #btnCommunication { background-color: #63B3ED; }
        #btnHealthAssessment { background-color: #ED64A6; }
        #btnMedSearch { background-color: #667EEA; }
        #btnOnlinePayment { background-color: #4FD1C5; }
        #btnHospitalization { background-color: #A0AEC0; }
        #footerLabel {
            font-size: 14px;
            color: #A0AEC0;
        }
    )";
    this->setStyleSheet(qss);
}