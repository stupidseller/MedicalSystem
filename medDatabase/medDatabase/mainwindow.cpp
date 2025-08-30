#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>
#include <QSqlError>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 数据库文件路径（确保正确）
    QString dbPath = "/mnt/hgfs/Ubuntu/medDatabase/medDatabase/hospital_management.db";

    // 检查文件是否存在
    if (!QFile::exists(dbPath)) {
        QMessageBox::critical(this, "文件不存在", "数据库文件未找到：" + dbPath);
        return;
    }

    // 初始化数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if( !db.open() ) {
        QMessageBox::critical(this, "Error", "打开数据库失败：" + db.lastError().text());
        return;
    }

    // 1. 先确认users表是否存在（保险起见）
    QSqlQuery checkTable;
    if (!checkTable.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='users';")) {
        QMessageBox::critical(this, "检查失败", "查询users表是否存在时出错：" + checkTable.lastError().text());
        return;
    }
    if (!checkTable.next()) {
        QMessageBox::critical(this, "表不存在", "数据库中没有users表！");
        return;
    }

    // 2. 查询users表（使用实际存在的字段，这里假设是user_id和phone，需根据实际表结构调整）
    QSqlQuery query;
    // 先在终端查询users表的字段：sqlite3 hospital_management.db "PRAGMA table_info(users);"
    // 根据实际字段修改查询语句，例如：SELECT user_id, phone, name FROM users
    if (!query.exec("SELECT user_id, phone FROM users")) {
        QMessageBox::critical(this, "SQL Error",
            "查询users表失败：" + query.lastError().text() + "\n查询语句：SELECT user_id, phone FROM users");
        return;
    }

    // 3. 设置表格表头（与查询的字段对应）
    QStandardItemModel *model = new QStandardItemModel(0, 2, this);
    model->setHorizontalHeaderItem(0, new QStandardItem("user_id"));  // 对应第一个字段
    model->setHorizontalHeaderItem(1, new QStandardItem("phone"));    // 对应第二个字段

    // 4. 填充表格数据
    int i = 0;
    while (query.next()) {
        model->setItem(i, 0, new QStandardItem(query.value(0).toString()));
        model->setItem(i, 1, new QStandardItem(query.value(1).toString()));
        i++;
    }

    // 如果没有数据，提示但不报错（可能表为空）
    if (i == 0) {
        QMessageBox::information(this, "提示", "users表中没有数据");
    }

    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
