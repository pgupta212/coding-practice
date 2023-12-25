#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QLabel>

class TaskListView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
};
