#include "taskFormWidget.h"
#include "task.h"
#include <QPushButton>
#include <QDialogButtonBox>
#include "task.h"
#include <QMessageBox>

TaskFormWidget::TaskFormWidget(Task *_task, QWidget *parent) : QDialog(parent)
    , task(_task)
{
    // Create widgets
    nameLineEdit = new QLineEdit(this);
    dueDateEdit = new QDateEdit(this);
    dueDateEdit->setDate(QDate::currentDate().addDays(7));
    descriptionTextEdit = new QTextEdit(this);

    // Create combo boxes for task priority and assignee
    priorityComboBox = new QComboBox(this);
    priorityComboBox->addItem(LOW);
    priorityComboBox->addItem(MEDIUM);
    priorityComboBox->addItem(HIGH);
    priorityComboBox->setCurrentText(MEDIUM);

    assigneeLineEdit = new QLineEdit(this);

    // Create form layout
    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("&Name:"), nameLineEdit);
    formLayout->addRow(tr("&Due Date:"), dueDateEdit);
    formLayout->addRow(tr("&Task Priority:"), priorityComboBox);
    formLayout->addRow(tr("&Assignee:"), assigneeLineEdit);
    formLayout->addRow(tr("&Description:"), descriptionTextEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Save
                                        | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &TaskFormWidget::submitForm);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    formLayout->addRow(tr(""), buttonBox);

    // Set the main layout for the widget
    setLayout(formLayout);
}

void TaskFormWidget::submitForm()
{
    if(!task) return;

    // "VALUES ($name, $created_at, $priority, $due_at, $status, $description, $assignee);"
    task->name = nameLineEdit->text();
    task->priority = Task::stringToEnumPriority(priorityComboBox->currentText());
    task->due_at = dueDateEdit->date();
    task->assignee = assigneeLineEdit->text();
    task->description = descriptionTextEdit->toPlainText();
    task->created_at = QDateTime::currentDateTime();
    task->status = Task::Pending;

    // Perform validation
    // in real world application, add validator in lineedit and show red border if validation fails.

    if(task->name.isEmpty() || task->assignee.isEmpty() || task->due_at < QDate::currentDate() || task->description.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid Form entry.");
        msgBox.setInformativeText("Please input correct information.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    QDialog::accept();
}
