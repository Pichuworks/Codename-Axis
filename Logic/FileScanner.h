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

#include "Lib/include/exiv2.hpp"
#include "Utils/StringUtils.h"
#include "Config/GlobalData.h"

#define FUCK_THREADS 16

class ScanThread : public QThread {
public:
    void run();
protected:
    void Scanner();
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
};

#endif // FILESCANNER_H
