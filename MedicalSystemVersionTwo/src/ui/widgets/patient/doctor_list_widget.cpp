#include "doctor_list_widget.h"
#include <QLineEdit>
#include <QComboBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

DoctorListWidget::DoctorListWidget(QWidget *parent)
        : QWidget(parent)
{
    initLayout();
    setupModel();
    initStyleSheets();

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &DoctorListWidget::onDoctorsReply);

    loadDoctors(); // 窗口创建时自动加载医生数据
}

void DoctorListWidget::loadDoctors()
{
    // BACKEND NOTE:  
    // 这是获取所有可预约医生列表的API。
    // API (建议): GET /api/doctors
    // 响应体 (JSON Array):
    // [
    //   { "id": "doc123", "name": "张志豪", "department": "心内科", "title": "主任医师", "fee": 50.0 },
    //   { "id": "doc456", "name": "艾利克斯", "department": "骨科", "title": "副主任医师", "fee": 30.0 },
    //   ...
    // ]
    QNetworkRequest request(QUrl("http://your-server.com/api/doctors"));
    networkManager->get(request);

    // 在等待后端响应时，可以显示一个加载提示（此处省略）
}

void DoctorListWidget::initLayout()
{
    setObjectName("DoctorListWidget");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // 筛选/搜索栏
    QHBoxLayout *filterLayout = new QHBoxLayout();
    searchLineEdit = new QLineEdit();
    searchLineEdit->setPlaceholderText("按医生姓名搜索...");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &DoctorListWidget::onFilterTextChanged);

    departmentComboBox = new QComboBox();
    departmentComboBox->addItem("所有科室"); // 默认项
    // 实际科室列表应从后端获取或在前端预定义
    departmentComboBox->addItem("心内科");
    departmentComboBox->addItem("骨科");
    departmentComboBox->addItem("神经科");
    departmentComboBox->addItem("儿科");
    connect(departmentComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DoctorListWidget::onDepartmentFilterChanged);

    filterLayout->addWidget(searchLineEdit, 2); // 搜索框占据更多空间
    filterLayout->addWidget(departmentComboBox, 1);

    // 医生列表表格
    doctorsTableView = new QTableView();
    doctorsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 只读
    doctorsTableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 选中整行
    doctorsTableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单选
    doctorsTableView->setShowGrid(false); // 不显示网格线
    doctorsTableView->verticalHeader()->hide(); // 隐藏行号
    doctorsTableView->horizontalHeader()->setStretchLastSection(true); // 最后一列自动拉伸
    connect(doctorsTableView, &QTableView::doubleClicked, this, &DoctorListWidget::onDoctorDoubleClicked);


    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(doctorsTableView);
}

void DoctorListWidget::setupModel()
{
    doctorsModel = new QStandardItemModel(0, 5, this); // 0行5列
    doctorsModel->setHorizontalHeaderLabels({"ID", "姓名", "科室", "职称", "挂号费(元)"});
    doctorsTableView->setModel(doctorsModel);
    doctorsTableView->setColumnHidden(0, true); // 隐藏ID列，但我们仍需要它来识别医生
}

void DoctorListWidget::populateModelWithData(const QJsonArray &doctors)
{
    doctorsModel->removeRows(0, doctorsModel->rowCount()); // 清空现有数据
    for (const QJsonValue &value : doctors) {
        QJsonObject doctor = value.toObject();
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(doctor["id"].toString());
        rowItems << new QStandardItem(doctor["name"].toString());
        rowItems << new QStandardItem(doctor["department"].toString());
        rowItems << new QStandardItem(doctor["title"].toString());
        rowItems << new QStandardItem(QString::number(doctor["fee"].toDouble()));
        doctorsModel->appendRow(rowItems);
    }
}

void DoctorListWidget::onFilterTextChanged(const QString &text)
{
    QString departmentFilter = departmentComboBox->currentText();
    for (int i = 0; i < doctorsModel->rowCount(); ++i) {
        bool nameMatch = doctorsModel->item(i, 1)->text().contains(text, Qt::CaseInsensitive);
        bool departmentMatch = (departmentFilter == "所有科室" || doctorsModel->item(i, 2)->text() == departmentFilter);
        doctorsTableView->setRowHidden(i, !(nameMatch && departmentMatch));
    }
}

void DoctorListWidget::onDepartmentFilterChanged(int index)
{
    onFilterTextChanged(searchLineEdit->text()); // 科室变化时，重新应用姓名过滤器
}

void DoctorListWidget::onDoctorDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    QString doctorId = doctorsModel->item(index.row(), 0)->text();
    QString doctorName = doctorsModel->item(index.row(), 1)->text();
    QString department = doctorsModel->item(index.row(), 2)->text();
    QString title = doctorsModel->item(index.row(), 3)->text();

    // 发射信号，通知主窗口用户已选择医生
    emit doctorSelected(doctorId, doctorName, department, title);
}

void DoctorListWidget::onDoctorsReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "网络错误", "无法获取医生列表: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QJsonArray doctorsArray = QJsonDocument::fromJson(reply->readAll()).array();
    populateModelWithData(doctorsArray);
    reply->deleteLater();
}

void DoctorListWidget::initStyleSheets()
{
    QString qss = R"(
        #DoctorListWidget {
            background-color: #F7FAFC;
            font-family: 'Microsoft YaHei';
        }
        QLineEdit, QComboBox {
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            padding: 10px;
            font-size: 14px;
            background-color: white;
        }
        QTableView {
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            background-color: white;
            font-size: 14px;
        }
        QTableView::item {
            padding: 10px;
        }
        QTableView::item:selected {
            background-color: #EBF8FF;
            color: #2B6CB0;
        }
        QHeaderView::section {
            background-color: #F7FAFC;
            padding: 10px;
            border: none;
            border-bottom: 1px solid #E2E8F0;
            font-size: 14px;
            font-weight: bold;
        }
    )";
    this->setStyleSheet(qss);
}