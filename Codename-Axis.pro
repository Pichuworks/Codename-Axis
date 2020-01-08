#-------------------------------------------------
#
# Project created by QtCreator 2020-01-05T19:52:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Codename-Axis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    FileTraverseThread.cpp

HEADERS  += mainwindow.h \
    FileTraverseThread.h \
    version.h

FORMS    += mainwindow.ui
