#pragma once

#include <QWidget>
#include <QDate>
#include <QUuid>
#include "task.h"

class TaskList : public QObject
{
    Q_OBJECT
public:
    explicit TaskList(QObject *parent = nullptr);
    ~TaskList();

    void addTask(Task * task);
    void deleteTask(int id);
    void updateTask(const Task * task);
    Task* getTask(int id);
    int getCount() const;
    int getCount(Task::Status status) const;

    std::vector<Task *> getTaskList() const;

    bool checkThisWeekDate(const QString &taskDate) const;
    int getAllDoneTasksCount() const;
    void createTasksLists(std::vector<Task*> tasks);

signals:

private:
    std::vector<Task *> taskList;
    std::unordered_map<int, int> taskMap;
};
