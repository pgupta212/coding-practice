#include "mainScreen.h"
#include "taskList/taskListView.h"
#include <QDir>
#include "taskDB/taskdbmanager.h"
#include "taskList/taskFormWidget.h"
#include "taskList/taskList.h"

#include <QHBoxLayout>
#include <QPushButton>

MainScreen::MainScreen(QWidget * parent) :
    QWidget(parent)
{
    QPushButton * createBtn = new QPushButton("Create issue", this);
    createBtn->setFixedSize(QSize(100, 40));
    connect(createBtn, &QPushButton::clicked, this, &MainScreen::slt_createBtnClicked);

    taskListView = new TaskListView(this);
    taskListView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(taskListView, 8);
    layout->addWidget(createBtn, 1);

    setLayout(layout);
}

void MainScreen::init()
{
    // Create and set up the taskListView
    // create DB
    QString dbPath = QDir::homePath() + "/Documents/tasks.db";
    taskDbManager  = std::make_shared<TaskDbManager>(dbPath);
    taskDbManager->init();

    // create task List, which holds actual data
    taskList = new TaskList();
    taskList->createTasksLists(taskDbManager->getAllTask());
    // update table with actual data
    taskListView->update(taskList);
}

void MainScreen::slt_createBtnClicked()
{
    Task *newTask = new Task();

    TaskFormWidget taskForm(newTask);
    taskForm.setModal(true);
    int accepted = taskForm.exec();

    // if dialog is accepted then update view
    if(accepted == QDialog::Accepted)
     {
        bool ok = taskDbManager->addTask(*newTask);
        if(ok)
        {
            // update Model
            // update local taskList;
            taskList->addTask(newTask);
            taskListView->update(taskList);
        }
     }
}
