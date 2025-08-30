#include "appointment_booking_widget.h"
#include <QLabel>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QDate>
#include <QMessageBox>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFormLayout>

AppointmentBookingWidget::AppointmentBookingWidget(QWidget *parent)
        : QWidget(parent)
{
    initLayout();
    initStyleSheets();

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &AppointmentBookingWidget::onBookingReply);
}

void AppointmentBookingWidget::loadDoctorInfo(const QString &doctorId, const QString &doctorName, const QString &department, const QString &title)
{
    currentDoctorId = doctorId;
    doctorNameLabel->setText(doctorName);
    doctorDetailsLabel->setText(QString("%1 | %2").arg(department, title));

    // BACKEND NOTE: 后端工程师请注意
    // 在实际应用中，加载医生信息后，应该立即向后端请求该医生今天的可用时间段。
    // API (建议): GET /api/doctors/{doctorId}/available-slots?date={today}
    // 前端收到响应后，会调用 timeSlotsListWidget->addItem() 来填充下面的列表。

    // 此处为前端模拟数据
    timeSlotsListWidget->clear();
    timeSlotsListWidget->addItem("09:00 - 09:30 (余 2)");
    timeSlotsListWidget->addItem("10:00 - 10:30 (余 1)");
    timeSlotsListWidget->addItem("14:30 - 15:00 (余 3)");
    timeSlotsListWidget->setCurrentRow(0); // 默认选中第一项
}

void AppointmentBookingWidget::initLayout()
{
    setObjectName("AppointmentBookingWidget");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // 1. 医生信息面板
    QGroupBox *doctorInfoGroup = new QGroupBox("预约医生信息");
    doctorInfoGroup->setObjectName("groupBox");
    QHBoxLayout *doctorInfoLayout = new QHBoxLayout(doctorInfoGroup);
    QLabel *avatarLabel = new QLabel(); // 医生头像
    avatarLabel->setFixedSize(64, 64);
    avatarLabel->setObjectName("avatarLabel");
    doctorNameLabel = new QLabel("医生姓名");
    doctorNameLabel->setObjectName("doctorNameLabel");
    doctorDetailsLabel = new QLabel("科室 | 职称");
    QVBoxLayout *nameLayout = new QVBoxLayout();
    nameLayout->addWidget(doctorNameLabel);
    nameLayout->addWidget(doctorDetailsLabel);
    doctorInfoLayout->addWidget(avatarLabel);
    doctorInfoLayout->addLayout(nameLayout);
    doctorInfoLayout->addStretch();

    // 2. 预约日期和时间选择
    QHBoxLayout *bookingLayout = new QHBoxLayout();
    bookingLayout->setSpacing(20);

    // 2.1 日期选择
    QGroupBox *dateGroup = new QGroupBox("选择预约日期");
    dateGroup->setObjectName("groupBox");
    QVBoxLayout *dateLayout = new QVBoxLayout(dateGroup);
    calendarWidget = new QCalendarWidget();
    calendarWidget->setMinimumDate(QDate::currentDate()); // 只能预约今天及以后的日期
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, [this](){
        onDateSelected(calendarWidget->selectedDate());
    });
    dateLayout->addWidget(calendarWidget);

    // 2.2 时间段选择
    QGroupBox *timeGroup = new QGroupBox("选择预约时间段");
    timeGroup->setObjectName("groupBox");
    QVBoxLayout *timeLayout = new QVBoxLayout(timeGroup);
    timeSlotsListWidget = new QListWidget();
    timeLayout->addWidget(timeSlotsListWidget);

    bookingLayout->addWidget(dateGroup, 2); // 日历占据更大比例
    bookingLayout->addWidget(timeGroup, 1);

    // 3. 病情描述
    QGroupBox *symptomsGroup = new QGroupBox("病情描述 (可选)");
    symptomsGroup->setObjectName("groupBox");
    QVBoxLayout *symptomsLayout = new QVBoxLayout(symptomsGroup);
    symptomsTextEdit = new QTextEdit();
    symptomsTextEdit->setPlaceholderText("请简要描述您的病情、症状或需要咨询的问题...");
    symptomsLayout->addWidget(symptomsTextEdit);

    // 4. 确认按钮
    confirmBookingButton = new QPushButton("确认挂号");
    confirmBookingButton->setObjectName("primaryButton");
    connect(confirmBookingButton, &QPushButton::clicked, this, &AppointmentBookingWidget::onConfirmBookingClicked);

    mainLayout->addWidget(doctorInfoGroup);
    mainLayout->addLayout(bookingLayout);
    mainLayout->addWidget(symptomsGroup);
    mainLayout->addWidget(confirmBookingButton, 0, Qt::AlignHCenter);
}

void AppointmentBookingWidget::onDateSelected(const QDate &date)
{
    // BACKEND NOTE: 后端工程师请注意
    // 当用户切换日期时，前端需要根据新的日期重新请求可用时间段。
    // API (建议): GET /api/doctors/{doctorId}/available-slots?date={selectedDate}
    // 例如: GET /api/doctors/doc123/available-slots?date=2025-08-30

    // 前端模拟逻辑
    timeSlotsListWidget->clear();
    if (date > QDate::currentDate()) {
        timeSlotsListWidget->addItem("09:30 - 10:00 (余 5)");
        timeSlotsListWidget->addItem("11:00 - 11:30 (余 4)");
        timeSlotsListWidget->addItem("15:00 - 15:30 (余 6)");
        timeSlotsListWidget->addItem("16:00 - 16:30 (余 8)");
    } else { // 模拟今天的时间段
        loadDoctorInfo(currentDoctorId, doctorNameLabel->text(), "", "");
    }
}

void AppointmentBookingWidget::onConfirmBookingClicked()
{
    if (timeSlotsListWidget->currentItem() == nullptr) {
        QMessageBox::warning(this, "预约失败", "请选择一个预约时间段。");
        return;
    }

    // BACKEND NOTE: 后端工程师请注意
    // 这是最终发起预约的API调用。
    // API (建议): POST /api/appointments
    // 请求体 (JSON):
    // {
    //     "doctorId": "doc123",              // 当前医生ID
    //     "patientId": "patient789",          // 当前登录的患者ID (后端通过token获取)
    //     "appointmentDate": "2025-08-29",    // 用户选择的日期
    //     "timeSlot": "10:00 - 10:30",      // 用户选择的时间段
    //     "symptoms": "用户填写的病情描述..." // 可选的病情描述
    // }
    // 后端逻辑:
    // 1. 验证该时间段是否仍然可用（防止多人同时预约）。
    // 2. 创建一条新的预约记录，并与医生和患者关联。
    // 3. 将该时间段的余量减一。
    // 4. 返回成功或失败的响应。

    QJsonObject json;
    json["doctorId"] = currentDoctorId;
    json["appointmentDate"] = calendarWidget->selectedDate().toString(Qt::ISODate);
    json["timeSlot"] = timeSlotsListWidget->currentItem()->text();
    json["symptoms"] = symptomsTextEdit->toPlainText();

    QNetworkRequest request(QUrl("http://your-server.com/api/appointments"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkManager->post(request, QJsonDocument(json).toJson());
}

void AppointmentBookingWidget::onBookingReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "网络错误", "预约失败: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QJsonObject jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
    if (jsonObj["success"].toBool()) {
        QMessageBox::information(this, "预约成功", "您已成功预约！请按时就诊。");
        // 可以在这里发射一个信号，通知主窗口切换回其他页面
        // emit bookingSuccessful();
    } else {
        QString error = jsonObj["error"].toString("未知的错误，请稍后重试。");
        QMessageBox::warning(this, "预约失败", error);
    }
    reply->deleteLater();
}

void AppointmentBookingWidget::initStyleSheets()
{
    QString qss = R"(
        #AppointmentBookingWidget {
            background-color: #F7FAFC;
            font-family: 'Microsoft YaHei';
        }
        #groupBox {
            font-size: 16px;
            font-weight: bold;
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            margin-top: 1ex;
        }
        #groupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px 0 5px;
        }
        #avatarLabel {
            background-color: #E2E8F0;
            border-radius: 32px; /* 使其成为圆形 */
            /* 在实际项目中，使用 QPixmap 设置图片 */
        }
        #doctorNameLabel {
            font-size: 20px;
            font-weight: bold;
            color: #1A202C;
        }
        QCalendarWidget {
            font-size: 14px;
        }
        QListWidget {
            font-size: 14px;
            border: none;
        }
        QListWidget::item:selected {
            background-color: #EBF8FF;
            color: #2B6CB0;
            border-radius: 4px;
        }
        QTextEdit {
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            padding: 10px;
            font-size: 14px;
        }
        #primaryButton {
            background-color: #3182CE;
            color: white;
            border-radius: 8px;
            padding: 12px 60px; /* 增加横向 padding */
            font-size: 16px;
            font-weight: bold;
            border: none;
        }
        #primaryButton:hover {
            background-color: #2B6CB0;
        }
    )";
    this->setStyleSheet(qss);
}
