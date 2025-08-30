#include "doctor_info_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QComboBox>
#include <QLineEdit>
#include <QSpacerItem>

struct DoctorProfile {
    QString name;
    QString title;
    QString department;
    QString specialty;
    QString schedule;
    QString experience;
    QString education;
    QString achievements;
};

DoctorInfoWidget::DoctorInfoWidget(QWidget *parent)
        : QWidget(parent), doctorListLayout(nullptr)
{
    setObjectName("DoctorInfoWidget");
    initUI();
    initStyleSheets();
    loadDoctorList();
}

DoctorInfoWidget::~DoctorInfoWidget() {}

void DoctorInfoWidget::initUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 顶部全局标题栏
    QWidget* globalHeader = new QWidget();
    globalHeader->setObjectName("globalHeader");
    QHBoxLayout* globalHeaderLayout = new QHBoxLayout(globalHeader);
    globalHeaderLayout->setContentsMargins(40, 10, 40, 10);

    QPushButton *backButton = new QPushButton("返回首页");
    backButton->setObjectName("backButton");
    connect(backButton, &QPushButton::clicked, this, &DoctorInfoWidget::backRequested);

    QLabel *title = new QLabel("医生信息");
    title->setObjectName("pageTitle");

    globalHeaderLayout->addWidget(backButton);
    globalHeaderLayout->addSpacing(20);
    globalHeaderLayout->addWidget(title);
    globalHeaderLayout->addStretch();

    mainLayout->addWidget(globalHeader);

    // 内容区域
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setContentsMargins(40, 20, 40, 40);
    contentLayout->setSpacing(30);

    contentLayout->addWidget(createSearchPanel(), 1);
    contentLayout->addWidget(createDoctorListPanel(), 3);

    mainLayout->addLayout(contentLayout);
}

QWidget* DoctorInfoWidget::createSearchPanel() {
    QFrame* panel = new QFrame();
    panel->setObjectName("searchPanel");
    QVBoxLayout* layout = new QVBoxLayout(panel);
    layout->setContentsMargins(25, 25, 25, 25);
    layout->setSpacing(20);

    QLabel* title = new QLabel("搜索医生");
    title->setObjectName("searchTitle");

    QFormLayout* formLayout = new QFormLayout();
    formLayout->setSpacing(15);
    formLayout->setLabelAlignment(Qt::AlignLeft);

    // 科室选择
    departmentCombo = new QComboBox();
    departmentCombo->setObjectName("departmentCombo");
    departmentCombo->addItems({"全部科室", "内科", "外科", "妇产科", "儿科", "眼科", "耳鼻喉科", "皮肤科", "神经科", "骨科"});
    connect(departmentCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DoctorInfoWidget::onDepartmentChanged);

    // 医生姓名搜索
    searchEdit = new QLineEdit();
    searchEdit->setObjectName("searchEdit");
    searchEdit->setPlaceholderText("输入医生姓名");

    formLayout->addRow("科室", departmentCombo);
    formLayout->addRow("医生姓名", searchEdit);

    QPushButton* searchButton = new QPushButton("搜索医生");
    searchButton->setObjectName("searchButton");
    connect(searchButton, &QPushButton::clicked, this, &DoctorInfoWidget::onSearchClicked);

    layout->addWidget(title);
    layout->addLayout(formLayout);
    layout->addStretch();
    layout->addWidget(searchButton);

    return panel;
}

QWidget* DoctorInfoWidget::createDoctorListPanel() {
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setObjectName("doctorScrollArea");

    QWidget* container = new QWidget();
    doctorListLayout = new QVBoxLayout(container);
    doctorListLayout->setContentsMargins(10, 10, 10, 10);
    doctorListLayout->setSpacing(20);

    scrollArea->setWidget(container);
    return scrollArea;
}

QWidget* DoctorInfoWidget::createDoctorCard(const QString &name, const QString &title,
                                            const QString &department, const QString &specialty,
                                            const QString &schedule, const QString &experience) {
    QFrame *card = new QFrame();
    card->setObjectName("doctorCard");

    QHBoxLayout *mainLayout = new QHBoxLayout(card);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(25, 20, 25, 20);

    // 左侧医生头像
    QLabel *avatar = new QLabel();
    avatar->setObjectName("doctorAvatar");
    avatar->setFixedSize(80, 80);

    // 中间医生信息
    QVBoxLayout *infoLayout = new QVBoxLayout();
    infoLayout->setSpacing(12);

    // 第一行：姓名和职称
    QHBoxLayout *nameLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(name);
    nameLabel->setObjectName("doctorName");
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setObjectName("doctorTitle");
    QLabel *deptTag = new QLabel(department);
    deptTag->setObjectName("departmentTag");

    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(titleLabel);
    nameLayout->addStretch();
    nameLayout->addWidget(deptTag);

    // 第二行：专长
    QLabel *specialtyLabel = new QLabel(specialty);
    specialtyLabel->setObjectName("doctorSpecialty");
    specialtyLabel->setWordWrap(true);

    // 第三行：出诊时间
    QLabel *scheduleLabel = new QLabel("出诊时间：" + schedule);
    scheduleLabel->setObjectName("doctorSchedule");

    // 第四行：工作经验
    QLabel *experienceLabel = new QLabel("从业经验：" + experience);
    experienceLabel->setObjectName("doctorExperience");

    infoLayout->addLayout(nameLayout);
    infoLayout->addWidget(specialtyLabel);
    infoLayout->addWidget(scheduleLabel);
    infoLayout->addWidget(experienceLabel);

    // 右侧操作按钮
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    QPushButton *profileButton = new QPushButton("查看详情");
    profileButton->setObjectName("profileButton");
    connect(profileButton, &QPushButton::clicked, this, [this, name](){
        onViewDoctorProfile(name);
    });

    QPushButton *appointmentButton = new QPushButton("立即预约");
    appointmentButton->setObjectName("appointmentButton");

    buttonLayout->addWidget(profileButton);
    buttonLayout->addWidget(appointmentButton);
    buttonLayout->addStretch();

    mainLayout->addWidget(avatar);
    mainLayout->addLayout(infoLayout, 1);
    mainLayout->addLayout(buttonLayout);

    return card;
}

void DoctorInfoWidget::loadDoctorList() {
    if (!doctorListLayout) return;

    // 清空现有列表
    QLayoutItem* item;
    while ((item = doctorListLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // 模拟医生数据
    QList<DoctorProfile> doctors = {
            DoctorProfile{
                    "王建华", "主任医师", "心血管内科",
                    "擅长：高血压、冠心病、心力衰竭、心律失常的诊断与治疗，在心血管介入治疗方面有丰富经验",
                    "周一至周五上午", "25年",
                    "北京医科大学医学博士", "获得省级医学科技进步奖二等奖"
            },
            DoctorProfile{
                    "李明", "副主任医师", "消化内科",
                    "擅长：胃炎、胃溃疡、肝炎、胆囊炎、消化道出血的诊断与治疗，内镜诊疗技术精湛",
                    "周二至周六上午", "18年",
                    "中山医科大学临床医学硕士", "发表SCI论文15篇"
            },
            DoctorProfile{
                    "张丽", "主治医师", "妇产科",
                    "擅长：妇科炎症、月经不调、不孕不育、产前检查、自然分娩、剖宫产等妇产科疾病诊治",
                    "周一至周五下午", "12年",
                    "华西医科大学临床医学学士", "妇产科专业委员会委员"
            },
            DoctorProfile{
                    "陈强", "主治医师", "骨科",
                    "擅长：骨折、关节炎、颈椎病、腰椎间盘突出、运动损伤的诊断与治疗，微创手术经验丰富",
                    "周三至周日上午", "15年",
                    "第四军医大学骨科学硕士", "骨科微创技术培训导师"
            },
            DoctorProfile{
                    "刘芳", "副主任医师", "儿科",
                    "擅长：小儿感冒、发热、咳嗽、腹泻、过敏性疾病、儿童生长发育评估与指导",
                    "周一至周五全天", "20年",
                    "首都医科大学儿科学硕士", "儿科急救专业委员会委员"
            },
            DoctorProfile{
                    "赵勇", "主任医师", "神经外科",
                    "擅长：脑肿瘤、脑血管病、颅脑外伤、脊髓疾病的外科治疗，神经内镜手术技术娴熟",
                    "周二、周四、周六上午", "28年",
                    "北京协和医学院神经外科博士", "国际神经外科学会会员"
            }
    };

    // 根据搜索条件过滤
    QString selectedDept = departmentCombo->currentText();
    QString searchName = searchEdit->text().trimmed();

    for(const auto &doctor : doctors) {
        // 科室过滤
        if (selectedDept != "全部科室" && !doctor.department.contains(selectedDept)) {
            continue;
        }

        // 姓名过滤
        if (!searchName.isEmpty() && !doctor.name.contains(searchName, Qt::CaseInsensitive)) {
            continue;
        }

        doctorListLayout->addWidget(createDoctorCard(
                doctor.name, doctor.title, doctor.department,
                doctor.specialty, doctor.schedule, doctor.experience
        ));
    }

    doctorListLayout->addStretch();
}

void DoctorInfoWidget::onSearchClicked() {
    loadDoctorList();
}

void DoctorInfoWidget::onDepartmentChanged() {
    loadDoctorList();
}

void DoctorInfoWidget::onViewDoctorProfile(const QString &doctorName) {
    // 这里可以打开医生详情对话框或页面
    // 暂时显示简单提示
}

void DoctorInfoWidget::initStyleSheets() {
    this->setStyleSheet(R"(
        #DoctorInfoWidget, #doctorScrollArea {
            background-color: #F0F4F8;
        }

        #globalHeader {
            background-color: white;
            border-bottom: 1px solid #E2E8F0;
        }

        #pageTitle {
            font-size: 20px;
            font-weight: bold;
            color: #2D3748;
        }

        #backButton {
            font-size: 14px;
            color: #4A5568;
            border: none;
            background: transparent;
            padding: 8px 12px;
        }
        #backButton:hover {
            color: #2D3748;
            background-color: #F7FAFC;
            border-radius: 6px;
        }

        #searchPanel {
            background-color: white;
            border-radius: 12px;
            border: 1px solid #E2E8F0;
            max-width: 320px;
        }

        #searchTitle {
            font-size: 18px;
            font-weight: bold;
            color: #2D3748;
        }

        QFormLayout > QLabel {
            font-size: 14px;
            color: #4A5568;
            font-weight: 500;
        }

        #departmentCombo, #searchEdit {
            padding: 8px 12px;
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            background-color: white;
            font-size: 14px;
            min-height: 20px;
        }
        #departmentCombo:focus, #searchEdit:focus {
            border-color: #3182CE;
            outline: none;
        }

        #searchButton {
            background-color: #38A169;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 12px;
            font-weight: bold;
            font-size: 15px;
        }
        #searchButton:hover {
            background-color: #2F855A;
        }

        #doctorCard {
            background-color: white;
            border-radius: 12px;
            border: 1px solid #E2E8F0;
        }
        #doctorCard:hover {
            border-color: #CBD5E0;
            box-shadow: 0 4px 12px rgba(0,0,0,0.05);
        }

        #doctorAvatar {
            background-color: #3182CE;
            border-radius: 40px;
        }

        #doctorName {
            font-size: 20px;
            font-weight: bold;
            color: #1A202C;
        }

        #doctorTitle {
            font-size: 14px;
            color: #718096;
            margin-left: 12px;
        }

        #departmentTag {
            font-size: 12px;
            color: #3182CE;
            background-color: #EBF8FF;
            padding: 4px 10px;
            border-radius: 8px;
            font-weight: 500;
        }

        #doctorSpecialty {
            font-size: 14px;
            color: #4A5568;
            line-height: 1.4;
        }

        #doctorSchedule, #doctorExperience {
            font-size: 13px;
            color: #718096;
        }

        #profileButton {
            background-color: transparent;
            color: #3182CE;
            border: 1px solid #3182CE;
            border-radius: 8px;
            padding: 8px 16px;
            font-size: 14px;
            min-width: 80px;
        }
        #profileButton:hover {
            background-color: #EBF8FF;
        }

        #appointmentButton {
            background-color: #3182CE;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 8px 16px;
            font-size: 14px;
            min-width: 80px;
        }
        #appointmentButton:hover {
            background-color: #2B6CB0;
        }
    )");
}