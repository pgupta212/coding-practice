#include "taskListView.h"

#include "taskListModel.h"
#include <QLayout>
#include "taskList/taskList.h"
#include "taskDB/taskdbmanager.h"
#include <QHeaderView>

TaskListView::TaskListView(QWidget *parent) : QWidget(parent)
{
    // Create and set up the title label
    totalIssuesLabel = new QLabel("Board (% issues)", this);
    totalIssuesLabel->setFont(QFont("Arial", 14, QFont::Bold));  // Set bold font

    inProgessIssues = new QLabel("(%1)", this);
    completedIssues = new QLabel("(%1)", this);
    pendingIssues = new QLabel("(%1)", this);

    view = new QTableView(this);
    view->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    view->setEditTriggers(QAbstractItemView::AllEditTriggers);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

    listModel = new TaskListModel(view);
    view->setModel(listModel);

    QHBoxLayout * statusLayout = new QHBoxLayout();
    statusLayout->addWidget(totalIssuesLabel);
    statusLayout->addWidget(pendingIssues);
    statusLayout->addWidget(inProgessIssues);
    statusLayout->addWidget(completedIssues);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(statusLayout);
    layout->addWidget(view);

    this->setLayout(layout);
}

void TaskListView::update(TaskList * taskList)
{
    listModel->setList(taskList);
    view->setModel(listModel);

    totalIssuesLabel->setText(QString("Board (%1 issues)").arg(taskList->getCount()));
    pendingIssues->setText(QString("Pending Issues: (%1)").arg(taskList->getCount(Task::Status::Pending)));
    inProgessIssues->setText(QString("InProgress Issues: (%1)").arg(taskList->getCount(Task::Status::InProgress)));
    completedIssues->setText(QString("Completed Issues: (%1)").arg(taskList->getCount(Task::Status::Completed)));

    QHeaderView *headerView = view->horizontalHeader();
    headerView->setStretchLastSection(true);
    headerView->setSectionResizeMode(QHeaderView::ResizeToContents);

    view->update();
}

