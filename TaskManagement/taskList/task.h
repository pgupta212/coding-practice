#pragma once

#include <QDateTime>
#include <QUuid>

namespace {
    static constexpr char LOW[] = "Low";
    static constexpr char MEDIUM[] = "Medium";
    static constexpr char HIGH[] = "High";
    static constexpr char PENDING[] = "Pending";
    static constexpr char INPROGRESS[] = "Inprogress";
    static constexpr char COMPLETED[] = "Completed";
}

struct Task
{
public:
    Task() = default;

    enum Priority {
        Low,
        Medium,
        High
    };

    enum Status {
        Pending,
        InProgress,
        Completed,
    };

    QString name;
    int task_id = -1;
    Priority priority = Priority::Low;
    QDate due_at = QDate::currentDate();
    QDateTime created_at = QDateTime();
    QDateTime completed_at = QDateTime();
    Status status = Pending;
    QString description;
    QString assignee;

    static QString enumToStringStatus(Task::Status status) {
        switch (status) {
            case Status::Pending: return PENDING;
            case Status::InProgress: return INPROGRESS;
            case Status::Completed: return COMPLETED;
        }

        qDebug() << "Invalid input status: " << status;
        return "";
    }

    static Task::Status stringToEnumStatus(const QString & str) {
        if(str == PENDING) return Task::Status::Pending;
        if(str == INPROGRESS) return Task::Status::InProgress;
        if(str == COMPLETED) return Task::Status::Completed;

         qDebug() << "Invalid input str: " << str;

         return Task::Pending;
    }

    static QString enumToStringPriority(Priority priority) {
        switch (priority) {
            case Priority::Low: return LOW;
            case Priority::Medium: return MEDIUM;
            case Priority::High: return HIGH;
        }

        qDebug() << "Invalid input priority: " << priority;
        return "";
    }

    static Task::Priority stringToEnumPriority(const QString & str) {
        if(str == LOW) return Task::Low;
        if(str == MEDIUM) return Task::Medium;
        if(str == HIGH) return Task::High;

        qDebug() << "Invalid input str: " << str;

        return Task::Low;
    }

    static QString dateInStr(const QDate & time)
    {
        return time.toString("ddd MMMM d yy");
    }

    static QString dateInStr(const QDateTime & time)
    {
        return time.toString("ddd MMMM d yy h:m:s ap");
    }

    bool isTaskPastDue() const {
        QDate todaysDate = QDate::currentDate();
        QDate dueDate = this->due_at;

        if(todaysDate > dueDate && this->status != Task::Completed)
            return true;
        return false;
    }
};
Q_DECLARE_METATYPE(Task::Priority);
Q_DECLARE_METATYPE(Task::Status);


