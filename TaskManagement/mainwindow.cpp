#include "mainwindow.h"
#include "mainScreen.h"

#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Task Management System"));

    // create Main Screen
    MainScreen * ms = new MainScreen(this);
    setCentralWidget(ms);

    ms->init();
}

MainWindow::~MainWindow()
{
    //delete ui;
}

