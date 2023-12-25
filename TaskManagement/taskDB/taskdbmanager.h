#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>

class Task;

class TaskDbManager
{
public:
    TaskDbManager(const QString& path);
    ~TaskDbManager();

    bool init();
    bool addTask(const Task & task);
    bool removeTask(int task_id);
    bool updateTask(const Task & newTask);
    std::vector<Task*> getAllTask();
    std::vector<Task *> getTask(int task_id);

    enum ColumnName {
        Task_id,
        Name,
        Priority,
        DueDate,
        CreatedAt,
        CompletedAt,
        Status,
        Description,
        Assignee,
        Invalid
    };

    ColumnName stringToEnum_colName(const QString & colName);

    struct PreparedStatement {
         QSqlQuery stmt;
         std::vector<ColumnName> fields;
         QSql::ParamType type;
    };
    void bindValue(PreparedStatement & preparedStmt, const Task & task);
    std::vector<Task *> executeSelectStmt(QSqlQuery & query);

private:
    QSqlDatabase db;

    void prepareAllStatement();
    PreparedStatement addStmt;
    PreparedStatement updateStmt;
    PreparedStatement deleteStmt;
    PreparedStatement getTaskStmt;
    PreparedStatement getAllTaskStmt;

    bool initSchema();
};

