
#include "taskDB/taskdbmanager.h"
#include "taskList/task.h"
#include <QTest>

// add necessary includes here

class TestDbManager : public QObject
{
    Q_OBJECT

public:
    TestDbManager();
    ~TestDbManager();

private slots:
    void test_case1();

};

TestDbManager::TestDbManager()
{

}

TestDbManager::~TestDbManager()
{

}

void TestDbManager::test_case1()
{
    // Create and set up the taskListView
    QString dbPath = QDir::homePath() + "/Documents/tasks_test.db";
    std::unique_ptr taskDbManager  = std::make_unique<TaskDbManager>(dbPath);
    taskDbManager->init();

    // "VALUES ($name, $created_at, $priority, $due_at, $status, $description, $assignee);"
    Task task;
    task.name = "I am testing task db manager";
    task.priority = Task::Medium;
    task.due_at = QDate::currentDate();
    task.assignee = "Poonam Gupta";
    task.description = "Lorem Ipsum is simply dummy text of the printing and "
                       "typesetting industry. Lorem Ipsum has been the industry's "
                       "standard dummy text ever since the 1500s, when an unknown printer took a galley of "
                       "type and scrambled it to make a type specimen book. It has "
                       "survived not only five centuries, but also the leap into "
                       "electronic typesetting, "
                       "remaining essentially unchanged. It was popularised in the "
                       "1960s with the release of Letraset sheets containing Lorem Ipsum passages, "
                       "and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
    task.created_at = QDateTime::currentDateTime();
    task.status = Task::Pending;
    bool success = taskDbManager->addTask(task);

    QVERIFY(success);

    std::vector<Task *> tasks = taskDbManager->getAllTask();
    QVERIFY(tasks.size() > 0);
}

QTEST_APPLESS_MAIN(TestDbManager)

