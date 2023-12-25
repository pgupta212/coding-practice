QT += testlib
QT += gui
QT       += sql

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testdbmanager.cpp

INCLUDEPATH += "../TaskManagement"

macx: LIBS += -L$$PWD/../TaskManagement/build/ -lTaskManagement

INCLUDEPATH += $$PWD/../TaskManagement/build
DEPENDPATH += $$PWD/../TaskManagement/build

macx: PRE_TARGETDEPS += $$PWD/../TaskManagement/build/libTaskManagement.a
