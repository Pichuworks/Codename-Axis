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
extern QList<QString> exif_mode_table;
extern QList<ExivRaw> current_exif_raw_data;

void CurrentScanThread::run() {
    qDebug() << "current scan start!";
    status_saved = false;
    Start();
}

void CurrentScanThread::Start() {
    QString logstr;
    logstr = "扫描开始时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    emit ScanLogAppend(logstr);

    ScanThread scanner[FUCK_THREADS];
    AnalyseThread analyser[FUCK_THREADS];

    while(!folder_queue.isEmpty() || !file_queue.isEmpty()) {
        for(int i = 0; i < FUCK_THREADS; i++) {
            connect(&scanner[i], SIGNAL(ScanLogAppend(QString)), this, SLOT(ScanLogAppendForward(QString)));
            connect(&scanner[i], SIGNAL(ScanLogClear()), this, SLOT(ScanLogClearForward()));
            connect(&analyser[i], SIGNAL(ScanLogAppend(QString)), this, SLOT(ScanLogAppendForward(QString)));
            connect(&analyser[i], SIGNAL(ScanLogClear()), this, SLOT(ScanLogClearForward()));

            scanner[i].run();
            analyser[i].run();
        }
        logstr = "扫描队列现有文件夹 " + QString::number(folder_queue.count()) + " 份，相片 " + QString::number(file_queue.count()) + " 张。";
        emit ScanLogAppend(logstr);
    }

    logstr = "数据库写入开始时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    emit ScanLogAppend(logstr);

    DatabaseSaveThread saver;
    connect(&saver, SIGNAL(Finish()), this, SLOT(Saved()));
    saver.run();

    while(!status_saved) { }

    logstr = "数据库写入结束时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "\n扫描结束！";
    emit ScanLogAppend(logstr);

    emit Done();
}

void CurrentScanThread::Saved() {
    status_saved = true;
}

void CurrentScanThread::ScanLogAppendForward(QString str) {
    emit ScanLogAppend(str);
}

void CurrentScanThread::ScanLogClearForward() {
    emit ScanLogClear();
}

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

extern QString current_scan_task_id;
extern QMutex current_exif_raw_data_mutex;
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
            bool fuck_blank = false;
            ExivRaw temp_exiv_raw;
            temp_exiv_raw.setTask_id(current_scan_task_id);
            QString file_title = filepath.right(filepath.length()-filepath.lastIndexOf("/")-1);
            temp_exiv_raw.setFile_name(file_title);
            temp_exiv_raw.setFile_path(filepath);
            temp_exiv_raw.setTitle(file_title);
            foreach(QString index, exif_mode_table) {
                QString value = ed[index.toStdString()].toString().c_str();
                value = value.trimmed();
                if(QString::compare(value, "") != 0) {
                    fuck_blank = true;
                    exif_disp += (index + ": " + value + "\n");

                    // 虽然 Qt 有反射机制 但是我还是先 if else 能 work 再说
                    if(QString::compare(index, "Exif.Image.Make") == 0) {
                        temp_exiv_raw.setManufacturer(value);
                    }
                    else if(QString::compare(index, "Exif.Image.Model") == 0) {
                        temp_exiv_raw.setCamera_model(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.LensModel") == 0) {
                        temp_exiv_raw.setLens_model(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.FocalLength") == 0) {
                        temp_exiv_raw.setPhyical_focus_length(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.FNumber") == 0) {
                        temp_exiv_raw.setAperture(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.ExposureTime") == 0) {
                        temp_exiv_raw.setShutter_speed(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.ISOSpeedRatings") == 0) {
                        temp_exiv_raw.setIso(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.ExposureBiasValue") == 0) {
                        temp_exiv_raw.setExposure_compensation(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.FocalLengthIn35mmFilm") == 0) {
                        temp_exiv_raw.setEquivalent_focus_length(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.DateTimeOriginal") == 0) {
                        temp_exiv_raw.setShooting_datetime(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.DateTimeOriginal") == 0) {
                        temp_exiv_raw.setShooting_datetime(value);
                    }
                    // 20200405 update
                    else if(QString::compare(index, "Exif.Photo.WhiteBalance") == 0) {
                        temp_exiv_raw.setWhite_balance(value);
                    }
                    else if(QString::compare(index, "Exif.Photo.MeteringMode") == 0) {
                        temp_exiv_raw.setMetering_mode(value);
                    }

                }
            }

            if(fuck_blank) {
                str_log = filepath + ":\n" + exif_disp + "\n";
                // QMutexLocker lockerCounter(&analyse_counter_mutex);
                // analyse_counter++;
                // lockerCounter.unlock();
                QMutexLocker lockerExif(&current_exif_raw_data_mutex);
                current_exif_raw_data.append(temp_exiv_raw);
                lockerExif.unlock();
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
    // emit ScanLogAppend(result);
    lockerFile.unlock();

    return;
}

void AnalyseThread::run() {
    if(file_queue.isEmpty())
        return;
    Analyser();
    return;
}

void DatabaseSaveThread::run() {
    Save();
    emit Finish();
    return;
}

extern QSqlDatabase global_sqlite_database;
void DatabaseSaveThread::Save() {
    QSqlQuery query(global_sqlite_database);
    QString sql = "INSERT INTO EXIF_RAW";
    sql.append("(task_id, file_name, file_path, title, manufacturer, camera_model, lens_model, shooting_datetime, ");
    sql.append("phyical_focus_length, equivalent_focus_length, iso, aperture, shutter_speed, shutter_counter, ");
    sql.append("exposure_compensation, flash_status, white_balance, shooting_mode, metering_mode, comment) VALUES");
    sql.append("(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");  // 仿佛挂满了奥秘 小SQLite你是不是有很多问号
    query.prepare(sql);

    // 先写 $(EXIF_RAW表的字段-id) 个 if-else, 反射再说
    qDebug() << "current exif raw data counter = " << QString::number(current_exif_raw_data.count());
    for(int i = 0; i < 20; i++) {
        QVariantList fuck_variant_item;
        foreach(ExivRaw raw, current_exif_raw_data) {
            switch(i) {
                case 0:
                    fuck_variant_item << raw.getTask_id();
                    break;
                case 1:
                    fuck_variant_item << raw.getFile_name();
                    break;
                case 2:
                    fuck_variant_item << raw.getFile_path();
                    break;
                case 3:
                    fuck_variant_item << raw.getTitle();
                    break;
                case 4:
                    fuck_variant_item << raw.getManufacturer();
                    break;
                case 5:
                    fuck_variant_item << raw.getCamera_model();
                    break;
                case 6:
                    fuck_variant_item << raw.getLens_model();
                    break;
                case 7:
                    fuck_variant_item << raw.getShooting_datetime();
                    break;
                case 8:
                    fuck_variant_item << raw.getPhyical_focus_length();
                    break;
                case 9:
                    fuck_variant_item << raw.getEquivalent_focus_length();
                    break;
                case 10:
                    fuck_variant_item << raw.getIso();
                    break;
                case 11:
                    fuck_variant_item << raw.getAperture();
                    break;
                case 12:
                    fuck_variant_item << raw.getShutter_speed();
                    break;
                case 13:
                    fuck_variant_item << raw.getShutter_counter();
                    break;
                case 14:
                    fuck_variant_item << raw.getExposure_compensation();
                    break;
                case 15:
                    fuck_variant_item << raw.getFlash_status();
                    break;
                case 16:
                    fuck_variant_item << raw.getWhite_balance();
                    break;
                case 17:
                    fuck_variant_item << raw.getShooting_mode();
                    break;
                case 18:
                    fuck_variant_item << raw.getMetering_mode();
                    break;
                case 19:
                    fuck_variant_item << raw.getComment();
                    break;
                default:
                    continue;
            }
        }
        query.addBindValue(fuck_variant_item);
    }
    if (!query.execBatch())
        qDebug() << "Error: the fucking database: " << query.lastError();
    else{
        qDebug() << "save data to database succeed.";
    }
    return;
}
