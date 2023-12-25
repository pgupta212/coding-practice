#include "taskdbmanager.h"
#include <QDebug>
#include "query.h"
#include "../taskList/task.h"
#include <QDate>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>

TaskDbManager::TaskDbManager(const QString & path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    qDebug() <<"databasePath: " << path;

    if (!db.open()) {
        qDebug() << "Error: connection with database fail";
    }
    else {
        qDebug() << "Database: connection ok";
    }
}

TaskDbManager::~TaskDbManager()
{
    if(db.isOpen()) {
        qDebug() << ("Close connection");
        db.close();
    }
}

bool TaskDbManager::init()
{
    if (!db.isOpen())
        return false;

    bool ok = initSchema();
    if(!ok) {
       qDebug() << "Error: failed to initialize schema.";
       return false;
    }

    prepareAllStatement();
    return true;
}

void TaskDbManager::bindValue(PreparedStatement & preparedStmt, const Task & task)
{
    for(int ind = 0; ind < preparedStmt.fields.size(); ind++) {
        auto col = preparedStmt.fields.at(ind);
        switch (col) {
        case ColumnName::Task_id:
            preparedStmt.stmt.bindValue(ind, task.task_id);
            break;
        case ColumnName::Name:
            preparedStmt.stmt.bindValue(ind, task.name);
            break;
        case ColumnName::CreatedAt:
            preparedStmt.stmt.bindValue(ind, Task::dateInStr(task.created_at));
            break;
        case ColumnName::Priority:
            preparedStmt.stmt.bindValue(ind, Task::enumToStringPriority(task.priority));
            break;
        case ColumnName::DueDate:
            preparedStmt.stmt.bindValue(ind, Task::dateInStr(task.due_at));
            break;
        case ColumnName::Status:
            preparedStmt.stmt.bindValue(ind, Task::enumToStringStatus(task.status));
            break;
        case ColumnName::Description:
            preparedStmt.stmt.bindValue(ind, task.description);
            break;
        case ColumnName::Assignee:
            preparedStmt.stmt.bindValue(ind, task.assignee);
            break;
        case ColumnName::CompletedAt:
            preparedStmt.stmt.bindValue(ind, Task::dateInStr(task.completed_at));
            break;
        default:
            break;
        }
    }
}

void TaskDbManager::prepareAllStatement()
{
    //"INSERT INTO Task (name, created_at, priority, due_at, status, description, assignee) "
    // "VALUES ($name, $created_at, $priority, $due_at, $status, $description, $assignee);"
    addStmt.stmt = QSqlQuery(db);
    addStmt.stmt.prepare(insertSQL);
    addStmt.fields = { Name, CreatedAt, Priority, DueDate, Status, Description, Assignee };

    //"UPDATE Task SET name=$name, priority=$priority, due_at=$due_at, status=$status, description=$description, assignee=$assignee WHERE task_id == $task_id";
    updateStmt.stmt = QSqlQuery(db);
    updateStmt.stmt.prepare(updateTaskSQL);
    updateStmt.fields = { Name, Priority, DueDate, Status, Description, Assignee, Task_id };

    //"DELETE FROM Task WHERE task_id == $task_id";
    deleteStmt.stmt = QSqlQuery(db);
    deleteStmt.stmt.prepare(deleteSQL);
    deleteStmt.fields = { Task_id };

    //"SELECT task_id, name, created_at, priority, due_at, completed_at, status, description, assignee FROM Task WHERE task_id==$task_id";
    getTaskStmt.stmt = QSqlQuery(db);
    getTaskStmt.stmt.prepare(getTaskSQL);
    getTaskStmt.fields = { Task_id };

    //"SELECT task_id, name, created_at, priority, due_at, completed_at, status, description, assignee FROM Task";
    getAllTaskStmt.stmt = QSqlQuery(db);
    getAllTaskStmt.stmt.prepare(getAllTaskSQL);
    getAllTaskStmt.fields = {};

}

bool TaskDbManager::initSchema()
{
    bool success = true;

    QSqlQuery query;
    bool ok = query.prepare(createTableAndIndexSQL);

    if(!ok) {
        qDebug() << "failed to prepare createTableAndIndexSQL";
        return false;
    }

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'task': one might already exist." ;
        qDebug() << "Error: " << query.lastError();
        success = false;
    }

    return success;
}

bool TaskDbManager::addTask(const Task & task)
{
    bindValue(addStmt, task);

    if(addStmt.stmt.exec())
       return true;

    qDebug() << "add Task failed: " << addStmt.stmt.lastError();

    return false;
}

bool TaskDbManager::removeTask(int task_id)
{
    Task task;
    task.task_id = task_id;

    bindValue(deleteStmt, task);

    if(deleteStmt.stmt.exec())
        return true;

    qDebug() << "remove Task failed: " << deleteStmt.stmt.lastError();

    return false;
}

std::vector<Task *> TaskDbManager::executeSelectStmt(QSqlQuery & query)
{
    std::vector<Task *> items;

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return items;
    }

    while (query.next()) {

        // Get list of fields obtained in the result of the query.
        std::vector<TaskDbManager::ColumnName> fields;
        QSqlRecord rec = query.record();
        qDebug() << "Number of columns: " << rec.count();

        // Get all fields from the output
        for (int i = 0; i < rec.count(); i++) {
            QString columnName = rec.fieldName(i);
            ColumnName fieldEnum = stringToEnum_colName(columnName);
            if(fieldEnum == ColumnName::Invalid) {
                qDebug () << "One of the index is invalid for the columns.";
                return items;
            }

            fields.emplace_back(fieldEnum);
        }

        Task *task = new Task();

        for(int ind = 0; ind < fields.size(); ind++) {
            ColumnName field = fields.at(ind);
            switch(field) {
                case ColumnName::Task_id:
                        task->task_id = query.value(ind).toInt();
                    break;
                case ColumnName::Name:
                        task->name = query.value(ind).toString();
                    break;
                case ColumnName::Priority:
                        task->priority = Task::stringToEnumPriority(query.value(ind).toString());
                    break;
                case ColumnName::DueDate:
                        task->due_at = query.value(ind).toDate();
                    break;
                case ColumnName::CreatedAt:
                        task->created_at = query.value(ind).toDateTime();
                    break;
                case ColumnName::CompletedAt:
                        task->completed_at = query.value(ind).toDateTime();
                    break;
                case ColumnName::Status:
                        task->status = Task::stringToEnumStatus(query.value(ind).toString());
                    break;
                case ColumnName::Description:
                        task->description = query.value(ind).toString();
                    break;
                case ColumnName::Assignee:
                        task->assignee = query.value(ind).toString();
                    break;
                case ColumnName::Invalid:
                        qDebug() << "Invalid columnName in select query";
                    break;
            }
        }

        items.push_back(task);
    }
    return items;
}

std::vector<Task *> TaskDbManager::getTask(int task_id)
{
    Task task;
    task.task_id = task_id;

    bindValue(getTaskStmt, task);
    return executeSelectStmt(getTaskStmt.stmt);
}

std::vector<Task *> TaskDbManager::getAllTask()
{
    return executeSelectStmt(getAllTaskStmt.stmt);
}

bool TaskDbManager::updateTask(const Task & newTask)
{
    bindValue(updateStmt, newTask);
    if(updateStmt.stmt.exec())
        return true;

    qDebug() << "update Task failed: " << updateStmt.stmt.lastError();

    return false;
}

TaskDbManager::ColumnName TaskDbManager::stringToEnum_colName(const QString & colName)
{
    if(colName == TASK_ID) return Task_id;
    if(colName == NAME) return Name;
    if(colName == PRIORITY) return Priority;
    if(colName == DUE_AT) return DueDate;
    if(colName == CREATED_AT) return CreatedAt;
    if(colName == COMPLETED_AT) return CompletedAt;
    if(colName == STATUS) return Status;
    if(colName == DESCRIPTION) return Description;
    if(colName == ASSIGNEE) return Assignee;

    qDebug() << "Invalid String for stringToEnum Conversion: " << colName;

    return Invalid;
}
