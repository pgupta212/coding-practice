#include "taskListModel.h"
#include "taskList.h"
#include "task.h"
#include <QFont>

TaskListModel::TaskListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

void TaskListModel::setList(TaskList *list)
{
   beginResetModel();
   taskList = list;
   endResetModel();
}

// Basic functionality:
int TaskListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !taskList)
           return 0;

    return taskList->getTaskList().size();
}

int TaskListModel::columnCount(const QModelIndex & /*parent*/) const
{
    return Columns::Count;
}

QVariant TaskListModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid() || !taskList)
        return false;

    const Task *item = taskList->getTaskList().at(index.row());
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
    {
        switch (col) {
        case Columns::Name:
            return item->name;
        case Columns::Priority:
            return Task::enumToStringPriority(item->priority);
        case Columns::Status:
            return Task::enumToStringStatus(item->status);
        case Columns::Assignee:
            return item->assignee;
        case Columns::DueDate:
            return Task::dateInStr(item->due_at);
        }

    }

    case Qt::FontRole: {
        QFont sansFont("Helvetica [Cronyx]", 12);
        return sansFont;
    }
        break;
    case Qt::ForegroundRole:{
        if(item->isTaskPastDue()  && col == Columns::DueDate)
            return QBrush(Qt::white);

        return QBrush(Qt::black);
    }
        break;
    case Qt::BackgroundRole:
    {
        if(item->isTaskPastDue() && col == Columns::DueDate)
            return QBrush(Qt::red);
    }

        break;
    case Qt::TextAlignmentRole:
            return int(Qt::AlignCenter);
        break;
    case Qt::CheckStateRole:
        if (item->isTaskPastDue()  && col == Columns::Name) // add a checkbox to cell(1,0)
            return Qt::Checked;

    }
    return QVariant();
}

QVariant TaskListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case Columns::Name:
            return QString("Name");
        case Columns::Priority:
            return QString("Priority");
        case Columns::Status:
            return QString("Status");
        case Columns::Assignee:
            return QString("Assignee");
        case Columns::DueDate:
            return QString("Due Date");
        }
    }
    else if (role == Qt::FontRole) {
        QFont sansFont("Helvetica [Cronyx]", 12);
        sansFont.setBold(true);
        return sansFont;
    }
    return QVariant();
}

// Editable:
bool TaskListModel::setData(const QModelIndex &index, const QVariant &value,
             int role)
{
    if (!taskList)
           return false;

        std::vector<Task *> items = taskList->getTaskList();
        Task * item = items[index.row()];

       taskList->getTaskList()[index.row()] = item;
       emit dataChanged(index, index, QVector<int>() << role);
       return true;
}

Qt::ItemFlags TaskListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
            return Qt::NoItemFlags;

        return Qt::ItemIsEditable;
}
