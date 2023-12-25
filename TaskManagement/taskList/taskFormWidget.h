#pragma once
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QDialog>
#include "task.h"

class TaskFormWidget : public QDialog
{
    Q_OBJECT
public:
    explicit TaskFormWidget(Task *_task, QWidget *parent = nullptr);
    Task getSubmittedTask();

signals:

private:
    QLineEdit *nameLineEdit;
    QDateEdit *dueDateEdit;
    QTextEdit *descriptionTextEdit;
    QComboBox *priorityComboBox;
    QLineEdit *assigneeLineEdit;

private slots:
    void submitForm();

private:
    Task *task = nullptr;

};

