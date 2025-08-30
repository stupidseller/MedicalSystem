#include "appointment_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
AppointmentDialog::AppointmentDialog(const QString &doctorName, const QString &doctorTitle, const QString &department, const QString &time, const QString &fee, QWidget *parent)
        : QDialog(parent),
          m_doctorName(doctorName),
          m_doctorTitle(doctorTitle),
          m_department(department),
          m_time(time),
          m_fee(fee),
          descriptionEdit(nullptr)
{
    setObjectName("AppointmentDialog");
    setModal(true); // 设置为模态对话框
    setWindowTitle("预约挂号");
    initUI();
    initStyleSheets();
}

AppointmentDialog::~AppointmentDialog() {}

void AppointmentDialog::initUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);

    // 顶部标题
    QLabel *titleLabel = new QLabel("预约挂号");
    titleLabel->setObjectName("dialogTitle");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    // 信息表单
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(15);
    formLayout->addRow("医生:", new QLabel(m_doctorName));
    formLayout->addRow("职称:", new QLabel(m_doctorTitle));
    formLayout->addRow("科室:", new QLabel(m_department));
    formLayout->addRow("时间:", new QLabel(m_time));
    formLayout->addRow("费用:", new QLabel(m_fee));
    mainLayout->addLayout(formLayout);

    // 病情描述
    descriptionEdit = new QTextEdit();
    descriptionEdit->setPlaceholderText("请简要描述您的症状或需要咨询的问题");
    formLayout->addRow("病情描述 (可选):", descriptionEdit);

    // 底部按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *cancelButton = new QPushButton("取消");
    cancelButton->setObjectName("cancelButton");
    connect(cancelButton, &QPushButton::clicked, this, &AppointmentDialog::reject);

    QPushButton *confirmButton = new QPushButton("确认挂号");
    confirmButton->setObjectName("saveButton"); // 复用样式
    connect(confirmButton, &QPushButton::clicked, this, &AppointmentDialog::onConfirmBooking);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

QString AppointmentDialog::getDiseaseDescription() const {
    return descriptionEdit ? descriptionEdit->toPlainText() : QString();
}

void AppointmentDialog::onConfirmBooking() {
    // 调用伪代码后端函数
    if (submitAppointmentRequest()) {
        accept(); // 如果提交成功，则关闭对话框并返回 QDialog::Accepted
    }
}

// --- 后端交互函数 (伪代码实现) ---
bool AppointmentDialog::submitAppointmentRequest() {
    //
    // 后端交互函数：提交一个新的挂号预约
    // API端点建议: POST /api/patient/appointments
    // 请求体 (JSON):
    // {
    //   "doctorName": "王医生",
    //   "department": "心血管内科",
    //   "appointmentTime": "08-31 上午",
    //   "diseaseDescription": "用户输入的病情描述..."
    // }
    //

    // --- 前端伪代码 ---
    // 1. 收集信息
    QString desc = getDiseaseDescription();

    // 2. 模拟网络请求
    qDebug() << "正在提交预约请求...";
    qDebug() << "医生: " << m_doctorName;
    qDebug() << "时间: " << m_time;
    qDebug() << "病情: " << desc;

    // 3. 模拟成功响应
    QMessageBox::information(this, "成功", "您已成功预约挂号！");
    return true; // 返回 true 表示成功
}

void AppointmentDialog::initStyleSheets() {
    this->setStyleSheet(R"(
        #AppointmentDialog { background-color: white; border-radius: 12px; }
        #dialogTitle { font-size: 20px; font-weight: bold; color: #1A202C; }
        QLabel { font-size: 14px; color: #4A5568; }
        QTextEdit {
            border: 1px solid #CBD5E0;
            border-radius: 6px;
            padding: 8px;
            min-height: 80px;
        }
        #cancelButton, #saveButton {
            padding: 10px 24px;
            font-size: 15px;
            border-radius: 8px;
        }
        #cancelButton { background-color: #F7FAFC; color: #4A5568; border: 1px solid #E2E8F0; }
        #cancelButton:hover { background-color: #EDF2F7; }
        #saveButton { background-color: #3182CE; color: white; border: none; font-weight: bold; }
        #saveButton:hover { background-color: #2B6CB0; }
    )");
}