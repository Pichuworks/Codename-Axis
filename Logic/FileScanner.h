#ifndef FILESCANNER_H
#define FILESCANNER_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#pragma comment(lib, "Shell32.lib")
#endif

#include <iostream>
#include <QDir>
#include <QDebug>
#include <QThread>
#include <QDirIterator>
#include <QList>
#include <QMetaType>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QQueue>
#include <QReadWriteLock>
#include <QTextCodec>
#include <QRunnable>
#include <QThreadPool>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

#include "Lib/include/exiv2.hpp"
#include "Utils/StringUtils.h"
#include "Config/GlobalData.h"
#include "Utils/StringExpr.h"

#define FUCK_THREADS 16

class CurrentScanThread : public QThread {
    Q_OBJECT

public:
    void run();
protected:
    void Start();
private:
    bool status_saved;
signals:
    void ScanLogAppend(QString);
    void ScanLogClear();
    void Done();
private slots:
    void Saved();
    void ScanLogAppendForward(QString);
    void ScanLogClearForward();
};

class ScanThread : public QThread {
    Q_OBJECT

public:
    void run();
protected:
    void Scanner();
signals:
    void ScanLogAppend(QString);
    void ScanLogClear();
};

class AnalyseThread : public QThread {
    Q_OBJECT

public:
    void run();
protected:
    void Analyser();
    QString DoAnalyse(QString filepath);
signals:
    void ScanLogAppend(QString);
    void ScanLogClear();
};

class DatabaseSaveThread : public QThread {
    Q_OBJECT

public:
    void run();
protected:
    void Save();
signals:
    void ScanLogAppend(QString);
    void ScanLogClear();
    void Finish();
};

#endif // FILESCANNER_H
