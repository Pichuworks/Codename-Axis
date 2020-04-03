#-------------------------------------------------
#
# Project created by QtCreator 2020-04-03T22:48:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Codename-Axis
TEMPLATE = app
DESTDIR = bin

PRECOMPILED_HEADER  = Form/head.h

CONFIG += resources_big

SOURCES += main.cpp\
        Form/AxisMainWindow.cpp \
    Form/quiwidget.cpp \
    Logic/AxisInit.cpp \
    Form/AxisAboutWindow.cpp \
    Config/GlobalData.cpp \
    Config/SystemConfig.cpp \
    Form/AxisDebugLogWindow.cpp

HEADERS  += Form/AxisMainWindow.h \
    Form/head.h \
    Form/quiwidget.h \
    Logic/AxisInit.h \
    Form/AxisAboutWindow.h \
    Config/GlobalData.h \
    Config/SystemConfig.h \
    Form/AxisDebugLogWindow.h \
    Config/Version.h

FORMS    += Form/AxisMainWindow.ui \
    Form/AxisAboutWindow.ui \
    Form/AxisDebugLogWindow.ui

RESOURCES += \
    Skin/main.qrc \
    Skin/qss.qrc
