#include "taskList.h"

TaskList::TaskList(QObject *parent) : QObject(parent) {}

TaskList::~TaskList()
{
    // Assume taskList and taskMap are populated
    // Free memory for objects in taskList
    for (Task *task : taskList) {
        delete task;
    }

    // Clear the taskList vector
    taskList.clear();

    // Clear the taskMap
    taskMap.clear();

}

int TaskList::getCount() const{
    return taskList.size();
}

void TaskList::addTask(Task *task) {
    // Check if the task with the same ID already exists
    if (taskMap.find(task->task_id) == taskMap.end()) {
        size_t index = taskList.size();
        taskList.push_back(new Task(*task));
        taskMap[task->task_id] = index;
    }
}

void TaskList::deleteTask(int id) {
    auto it = taskMap.find(id);
    if (it != taskMap.end()) {
        size_t index = it->second;
        delete taskList[index];
        taskMap.erase(it);

        // Erase the task from the vector while maintaining order
        if (index < taskList.size() - 1) {
            taskList[index] = taskList.back();
            taskMap[taskList.back()->task_id] = index;
        }
        taskList.pop_back();
    }
}

void TaskList::updateTask(const Task *task) {
    auto it = taskMap.find(task->task_id);
    if (it != taskMap.end()) {
        size_t index = it->second;
        *(taskList[index]) = *task;
    }
}

Task *TaskList::getTask(int id) {
    auto it = taskMap.find(id);
    return (it != taskMap.end()) ? taskList[it->second] : nullptr;
}

std::vector<Task *> TaskList::getTaskList() const {
    return taskList;
}


void TaskList::createTasksLists(std::vector<Task*> tasks) {
    foreach (Task* task, tasks) {
        qDebug() << "Task name: " << task->name;
        addTask(task);
    }
}

int TaskList::getAllDoneTasksCount() const {
    int count = 0;
    for (int i = 0; i < getCount(); ++i) {
      std::vector<Task *> taskList = getTaskList();
      if(taskList.at(i)->status == Task::Status::Completed) {
          count++;
      }
    }
    return count;
}

int TaskList::getCount(Task::Status status) const
{
    int count =0;
    foreach (Task* task, taskList) {
        if(task->status == status) count++;
    }

    return count;
}
