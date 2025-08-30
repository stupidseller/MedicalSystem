#ifndef DOCTOR_INFO_WIDGET_H
#define DOCTOR_INFO_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>

class DoctorInfoWidget : public QWidget
{
Q_OBJECT

public:
    explicit DoctorInfoWidget(QWidget *parent = nullptr);
    ~DoctorInfoWidget();

signals:
    void backRequested();

private slots:
    void onSearchClicked();
    void onDepartmentChanged();
    void onViewDoctorProfile(const QString &doctorName);

private:
    void initUI();
    void initStyleSheets();
    void loadDoctorList();

    // UI创建函数
    QWidget* createSearchPanel();
    QWidget* createDoctorListPanel();
    QWidget* createDoctorCard(const QString &name, const QString &title,
                              const QString &department, const QString &specialty,
                              const QString &schedule, const QString &experience);

private:
    QVBoxLayout *doctorListLayout;
    QComboBox *departmentCombo;
    QLineEdit *searchEdit;
    QScrollArea *scrollArea;
};

#endif // DOCTOR_INFO_WIDGET_H