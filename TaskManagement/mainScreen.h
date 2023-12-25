#pragma once
#include <QWidget>

class TaskFormWidget;
class TaskDbManager;
class TaskListView;
class TaskList;

class MainScreen : public QWidget
{
public:
    MainScreen(QWidget * parent);
    void init();

private slots:
    void slt_createBtnClicked();

private:
    std::shared_ptr<TaskDbManager> taskDbManager;
    TaskListView * taskListView;
    TaskList * taskList;
};
