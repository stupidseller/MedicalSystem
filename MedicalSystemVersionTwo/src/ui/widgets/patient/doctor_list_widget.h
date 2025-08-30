#ifndef DOCTOR_LIST_WIDGET_H
#define DOCTOR_LIST_WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

class QLineEdit;
class QComboBox;
class QTableView;
class QStandardItemModel;
class QNetworkReply;

class DoctorListWidget : public QWidget
{
Q_OBJECT

public:
    explicit DoctorListWidget(QWidget *parent = nullptr);

    void loadDoctors(); // 公共接口，用于加载/刷新医生列表

signals:
    // 当用户选择一位医生时发射此信号，并传递医生ID
    void doctorSelected(const QString &doctorId, const QString &doctorName, const QString &department, const QString &title);

private slots:
    void onFilterTextChanged(const QString &text);
    void onDepartmentFilterChanged(int index);
    void onDoctorDoubleClicked(const QModelIndex &index);
    void onDoctorsReply(QNetworkReply *reply);

private:
    void initLayout();
    void initStyleSheets();
    void setupModel();
    void populateModelWithData(const QJsonArray &doctors);

    // UI 控件
    QLineEdit *searchLineEdit;
    QComboBox *departmentComboBox;
    QTableView *doctorsTableView;

    // 数据模型
    QStandardItemModel *doctorsModel;

    // 网络
    QNetworkAccessManager *networkManager;
};

#endif // DOCTOR_LIST_WIDGET_H