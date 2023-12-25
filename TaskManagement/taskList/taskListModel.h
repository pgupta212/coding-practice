#pragma once

#include <QAbstractListModel>
#include "task.h"

class TaskList;

class TaskListModel : public QAbstractListModel
{
public:
    explicit TaskListModel(QObject *parent = nullptr);

     enum Columns {
            Name,
            Priority,
            Status,
            Assignee,
            DueDate,
            Count // keep always last
      };

        // Basic functionality:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        // Editable:
        bool setData(const QModelIndex &index, const QVariant &value,
                     int role = Qt::EditRole) override;

        Qt::ItemFlags flags(const QModelIndex& index) const override;

        void setList(TaskList *list);
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    private:
        TaskList *taskList;
};

