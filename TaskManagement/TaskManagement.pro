QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console static // this is used to create the static lib
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = lib // used to create the static lib for the unit test fm

SOURCES += \
    main.cpp \
    mainScreen.cpp \
    mainwindow.cpp \
    taskDB/taskdbmanager.cpp \
    taskList/taskFormWidget.cpp \
    taskList/taskList.cpp \
    taskList/taskListModel.cpp \
    taskList/taskListView.cpp

HEADERS += \
    mainScreen.h \
    mainwindow.h \
    taskDB/query.h \
    taskDB/taskdbmanager.h \
    taskList/task.h \
    taskList/taskFormWidget.h \
    taskList/taskList.h \
    taskList/taskListModel.h \
    taskList/taskListView.h

#FORMS += \
#    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
