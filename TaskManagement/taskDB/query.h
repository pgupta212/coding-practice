#pragma once
namespace  {
    static constexpr char TASK_ID[] = "task_id";
    static constexpr char NAME[] = "name";
    static constexpr char PRIORITY[] = "priority";
    static constexpr char DUE_AT[] = "due_at";
    static constexpr char CREATED_AT[] = "created_at";
    static constexpr char COMPLETED_AT[] = "completed_at";
    static constexpr char STATUS[] = "status";
    static constexpr char DESCRIPTION[] = "description";
    static constexpr char ASSIGNEE[] = "assignee";

    static constexpr char createTableAndIndexSQL[] = R"(
        CREATE TABLE IF NOT EXISTS Task (
            task_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            name TEXT NOT NULL,
            created_at TEXT NOT NULL,
            priority TEXT NOT NULL,
            due_at TEXT NOT NULL,
            completed_at TEXT DEFAULT NULL,
            status TEXT DEFAULT 'Pending',
            description TEXT,
            assignee TEXT
        );
    )";

    static constexpr char indexSQL[] = "CREATE INDEX IF NOT EXISTS idx ON Task (task_id) WHERE completed_at IS NULL AND status = 'Pending'";

    static constexpr char insertSQL[] = R"(INSERT INTO Task (name, created_at, priority, due_at, status, description, assignee)
                                        VALUES (:name, :created_at, :priority, :due_at, :status, :description, :assignee))";


    static constexpr char deleteSQL[] = "DELETE FROM Task WHERE task_id == :task_id";


    static constexpr char getAllTaskSQL[] = "SELECT task_id, name, created_at, priority, due_at, completed_at, status, description, assignee FROM Task";
    //static constexpr char getAllTaskSQL[] = "SELECT * FROM Task";

    static constexpr char getTaskSQL[] = "SELECT task_id, name, created_at, priority, due_at, completed_at, status, description, assignee FROM Task WHERE task_id==:task_id";

    static constexpr char mostRecentlyAddedSQL[] = "task_id, name, created_at, priority, due_at, completed_at, status, description, assignee FROM Task ORDER BY task_id DESC LIMIT 1";

    static constexpr char updateTaskSQL[] = "UPDATE Task SET name=:name, priority=:priority, due_at=:due_at, status=:status, description=:description, assignee=:assignee WHERE task_id == :task_id";

}


//Task originalTask;
// originalTask.name = "TestTask";
// originalTask.task_id = 1;
// originalTask.priority = Task::Priority::Low;
// originalTask.due_at = QDateTime::currentDateTime().addDays(7);
// originalTask.created_at = QDateTime::currentDateTime();
// originalTask.completed_at = QDateTime::currentDateTime().addDays(2);
// originalTask.status = Task::Status::Completed;
// originalTask.description = "This is a test task";
// originalTask.assignee = "John Doe";


//taskDbManager->addTask(originalTask);
//qDebug() << "Size after add: " << taskDbManager->getAllTask().size();
