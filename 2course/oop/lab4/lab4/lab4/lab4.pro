#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T14:29:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    doors.cpp \
    lift.cpp \
    Controller.cpp \
    Lift_panel.cpp

HEADERS  += mainwindow.h \
    doors.h \
    stats.h \
    lift.h \
    Controller.h \
    Lift_panel.h

FORMS    += mainwindow.ui
CONFIG +=c++14
