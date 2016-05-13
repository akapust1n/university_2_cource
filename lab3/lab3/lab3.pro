#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T21:53:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DataRead.cpp \
    BigModelManager.cpp

HEADERS  += mainwindow.h \
    DataManager.h \
    DataRead.h \
    Conroller.h \
    BigModelManager.h \
    SceneManager.h \
    SceneObjects.h \
    my_exception.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++14
