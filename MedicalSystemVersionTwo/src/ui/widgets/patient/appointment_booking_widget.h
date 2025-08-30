#ifndef APPOINTMENT_BOOKING_WIDGET_H
#define APPOINTMENT_BOOKING_WIDGET_H

#include <QWidget>

// 前置声明
class QVBoxLayout;

class AppointmentBookingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AppointmentBookingWidget(QWidget *parent = nullptr);
    ~AppointmentBookingWidget();

signals:
    void backRequested(); // 返回仪表盘的信号

private slots:
    void onSearchClicked(); // 点击“搜索医生”
    void onBookNowClicked(const QString &doctorName, const QString &timeSlot); // 点击“立即预约”

private:
    // --- 后端交互 (伪代码) ---
    void loadAvailableDoctors();

    // --- UI 构建函数 ---
    void initUI();
    void initStyleSheets();
    QWidget* createHeader();
    QWidget* createFilterPanel();
    QWidget* createDoctorListPanel();

    QWidget* createDoctorEntryWidget(const struct DoctorInfo &doctor);
    QWidget* createSlotWidget(const struct AppointmentSlot &slot);

    // 布局，用于动态添加医生信息
    QVBoxLayout *doctorListLayout;
};

#endif // APPOINTMENT_BOOKING_WIDGET_H