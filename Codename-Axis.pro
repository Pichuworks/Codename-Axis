#-------------------------------------------------
#
# Project created by QtCreator 2020-04-03T22:48:12
#
#-------------------------------------------------

QT       += core gui network sql

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
    Form/AxisDebugLogWindow.cpp \
    Logic/FileScanner.cpp \
    Logic/DatabaseManager.cpp \
    Utils/StringUtils.cpp \
    Utils/StringExpr.cpp

HEADERS  += Form/AxisMainWindow.h \
    Form/head.h \
    Form/quiwidget.h \
    Logic/AxisInit.h \
    Form/AxisAboutWindow.h \
    Config/GlobalData.h \
    Config/SystemConfig.h \
    Form/AxisDebugLogWindow.h \
    Config/Version.h \
    Logic/FileScanner.h \
    Logic/DatabaseManager.h \
    Utils/StringUtils.h \
    Utils/StringExpr.h

FORMS    += Form/AxisMainWindow.ui \
    Form/AxisAboutWindow.ui \
    Form/AxisDebugLogWindow.ui

RESOURCES += \
    Skin/main.qrc \
    Skin/qss.qrc

INCLUDEPATH += ./Lib/include

LIBS += -lD:/Code/Qt/ThreadPoolFileScanner/lib/exiv2 \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/exiv2-xmp \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/expat \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/gmock \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/gmock_main \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/gtest \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/gtest_main \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/iconv_x86 \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/zlib \
        -lD:/Code/Qt/ThreadPoolFileScanner/lib/psapi

win32 {
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
    QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01

    DEFINES += _ATL_XP_TARGETING
    QMAKE_CFLAGS += /D_USING_V140_SDK71_
    QMAKE_CXXFLAGS += /D_USING_V140_SDK71
    LIBS *= -L"%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Lib"
    INCLUDEPATH += "%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Include"
    QMAKE_TARGET_OS = xp
}
