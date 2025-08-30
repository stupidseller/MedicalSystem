#ifndef APPOINTMENT_DIALOG_H
#define APPOINTMENT_DIALOG_H

#include <QDialog>
#include <QString>

// 前置声明
class QTextEdit;

class AppointmentDialog : public QDialog
{
Q_OBJECT

public:
    // 构造函数接收必要的预约信息
    explicit AppointmentDialog(const QString &doctorName, const QString &doctorTitle, const QString &department, const QString &time, const QString &fee, QWidget *parent = nullptr);
    ~AppointmentDialog();

    // 获取用户输入的病情描述
    QString getDiseaseDescription() const;

private slots:
    void onConfirmBooking();

private:
    void initUI();
    void initStyleSheets();

    // --- 后端交互 (伪代码) ---
    bool submitAppointmentRequest();

    // 存储传入的信息
    QString m_doctorName;
    QString m_doctorTitle;
    QString m_department;
    QString m_time;
    QString m_fee;

    // UI 控件
    QTextEdit *descriptionEdit;
};

#endif // APPOINTMENT_DIALOG_H