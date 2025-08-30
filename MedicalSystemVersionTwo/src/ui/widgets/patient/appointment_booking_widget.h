#ifndef APPOINTMENT_BOOKING_WIDGET_H
#define APPOINTMENT_BOOKING_WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

class QLabel;
class QCalendarWidget;
class QListWidget;
class QPushButton;
class QNetworkReply;
class QTextEdit;

class AppointmentBookingWidget : public QWidget
{
Q_OBJECT

public:
    explicit AppointmentBookingWidget(QWidget *parent = nullptr);

    // 公共接口，用于从外部加载医生信息到此界面
    void loadDoctorInfo(const QString &doctorId, const QString &doctorName, const QString &department, const QString &title);

private slots:
    void onDateSelected(const QDate &date);
    void onConfirmBookingClicked();
    void onBookingReply(QNetworkReply *reply);

private:
    void initLayout();
    void initStyleSheets();

    // UI 控件指针
    QLabel *doctorNameLabel;
    QLabel *doctorDetailsLabel;
    QCalendarWidget *calendarWidget;
    QListWidget *timeSlotsListWidget;
    QTextEdit *symptomsTextEdit;
    QPushButton *confirmBookingButton;

    // 网络
    QNetworkAccessManager *networkManager;

    // 临时存储的医生信息
    QString currentDoctorId;
};

#endif // APPOINTMENT_BOOKING_WIDGET_H