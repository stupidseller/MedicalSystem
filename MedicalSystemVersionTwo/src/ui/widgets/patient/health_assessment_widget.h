#ifndef HEALTH_ASSESSMENT_WIDGET_H
#define HEALTH_ASSESSMENT_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QStackedWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMap>

struct Question {
    QString text;
    QStringList options;
    QList<int> scores;
};

struct HealthResult {
    QString scoreRange;
    QString summary;
    QString description;
    QStringList suggestions;
    QString backgroundColor;
    QString textColor;
};

class HealthAssessmentWidget : public QWidget
{
Q_OBJECT

public:
    explicit HealthAssessmentWidget(QWidget *parent = nullptr);
    ~HealthAssessmentWidget();

signals:
    void backRequested();

private slots:
    void onSubmitClicked();
    void onRetakeClicked();
    void onAnswerChanged();

private:
    void initUI();
    void initStyleSheets();
    void setupQuestions();
    void setupResults();
    void showQuestionnaire();
    void showResults(int totalScore);

    // UI创建函数
    QWidget* createQuestionnairePanel();
    QWidget* createResultPanel();
    QWidget* createQuestionWidget(int index, const Question &question);

    // 计算和评估
    int calculateTotalScore();
    HealthResult getHealthResult(int score);

private:
    QStackedWidget *mainStack;
    QWidget *questionnairePage;
    QWidget *resultPage;
    QVBoxLayout *questionLayout;
    QPushButton *submitButton;

    // 结果页面组件
    QLabel *scoreLabel;
    QLabel *summaryLabel;
    QLabel *descriptionLabel;
    QVBoxLayout *suggestionLayout;
    QFrame *resultFrame;

    QList<Question> questions;
    QMap<int, HealthResult> healthResults;
    QList<QButtonGroup*> buttonGroups;

    int currentScore;
};

#endif // HEALTH_ASSESSMENT_WIDGET_H