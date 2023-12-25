#pragma once

#include <QWidget>
#include <QTableView>
#include <QLabel>

class TaskManager;
class TaskListModel;
class TaskListDelegate;
class TaskList;
class TaskDbManager;

class TaskListView : public QWidget
{
    Q_OBJECT
public:
    explicit TaskListView(QWidget *parent = nullptr);
    void update(TaskList * taskList);

private:
    QTableView * view;
    TaskListModel * listModel;
    TaskListDelegate * listDelegate;

    QLabel * totalIssuesLabel;
    QLabel * inProgessIssues;
    QLabel * completedIssues;
    QLabel * pendingIssues;

    std::shared_ptr<TaskDbManager> dbManager;
};
