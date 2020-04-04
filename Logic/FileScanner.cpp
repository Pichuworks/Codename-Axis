#include "FileScanner.h"

extern QMutex folder_mutex;
extern QQueue<QString> folder_queue;
extern QMutex file_mutex;
extern QQueue<QString> file_queue;
extern QMutex analyse_lock;
extern QList<QString> analyse_result;
extern QMutex scan_counter_mutex;
extern int scan_counter;
extern QMutex analyse_counter_mutex;
extern int analyse_counter;
extern QList<QString> exif_mode;
extern QList<ExivRaw> current_exif_raw_data;

void ScanThread::run() {
    if(folder_queue.isEmpty())
        return;
    Scanner();
}

void ScanThread::Scanner() {
    QMutexLocker lockerFolder(&folder_mutex);
    QString now_folder_path = folder_queue.dequeue();
    lockerFolder.unlock();
    QDir dir(now_folder_path);
    if(!dir.exists()) {
        return;
    }

    QStringList filters;
    filters << QString("jpg")
            << QString("jpeg")
            << QString("png")
            << QString("nef")
            << QString("cr2")
            << QString("cr3")
            << QString("raf")
            << QString("arw")
            << QString("tif");

    QFileInfoList list =dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo i, list) {
        QString filepath = i.absoluteFilePath();
        if(filters.indexOf(i.suffix().toLower(), Qt::CaseInsensitive) != -1 && !i.isDir()) {
            QMutexLocker lockerFile(&file_mutex);
            file_queue.enqueue(filepath);
            lockerFile.unlock();
        }
        else if(i.isDir()) {
            lockerFolder.relock();
            folder_queue.enqueue(filepath);
            lockerFolder.unlock();
        }
    }

    QMutexLocker lockerCounter(&scan_counter_mutex);
    scan_counter++;
    lockerCounter.unlock();
    return;
}


QString AnalyseThread::DoAnalyse(QString filepath) {
    QString exif_disp = "";
    QString str_log;

    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(UTF8toGBK(filepath));
        if(image.get() == 0) {
            // do nothing?
        }
        image->readMetadata();
        Exiv2::ExifData ed = image->exifData();
        if (ed.empty()){
        }
        else {
            foreach(QString index, exif_mode) {
                QString value = ed[index.toStdString()].toString().c_str();
                exif_disp += (index + ": " + value + "\n");
            }
            if(QString::compare(exif_disp.trimmed(), "") != 0) {
                str_log = filepath + ":\n" + exif_disp + "\n";
            }
        }
    }
    catch(...) {
        str_log = filepath + ": LOAD ERROR";
        qDebug() << "[ERROR] error with loading " + QString(filepath.toStdString().c_str());
    }
    return str_log;
}

void AnalyseThread::Analyser() {
    QMutexLocker lockerFolder(&file_mutex);
    QString now_filepath = file_queue.dequeue();
    lockerFolder.unlock();

    QString result = DoAnalyse(now_filepath);

    QMutexLocker lockerFile(&analyse_lock);
    analyse_result.append(result);
    emit ScanLogAppend(result);
    lockerFile.unlock();

    QMutexLocker lockerCounter(&analyse_counter_mutex);
    analyse_counter++;
    lockerCounter.unlock();
    return;
}

void AnalyseThread::run() {
    if(file_queue.isEmpty())
        return;
    Analyser();
    return;
}
