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

extern QSqlDatabase global_sqlite_database;
extern QString current_scan_task_id;
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

            foreach(QString index, exif_mode_table) {
                QString value = ed[index.toStdString()].toString().c_str();
                if(QString::compare(value.trimmed(), "") != 0) {
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

                }
            }

            if(fuck_blank) {
                str_log = filepath + ":\n" + exif_disp + "\n";
                QSqlQuery query(global_sqlite_database);
                QString sql = "insert into EXIF_RAW";
                sql.append("(task_id, file_name, file_path, title, manufacturer, camera_model, lens_model, shooting_datetime, ");
                sql.append("phyical_focus_length, equivalent_focus_length, iso, aperture, shutter_speed, shutter_counter, ");
                sql.append("exposure_compensation, flash_status, white_balance, shooting_mode, metering_mode, comment) values");
                sql.append("('"); sql.append(current_scan_task_id); sql.append("', ");
                sql.append("'"); sql.append(filepath.right(filepath.length()-filepath.lastIndexOf("/")-1)); sql.append("', ");
                sql.append("'"); sql.append(filepath); sql.append("', ");
                sql.append("'"); sql.append(filepath.right(filepath.length()-filepath.lastIndexOf("/")-1)); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getManufacturer()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getCamera_model()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getLens_model()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getShooting_datetime()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getPhyical_focus_length()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getEquivalent_focus_length()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getIso()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getAperture()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getShutter_speed()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getShutter_counter()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getExposure_compensation()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getFlash_status()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getWhite_balance()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getShooting_mode()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getMetering_mode()); sql.append("', ");
                sql.append("'"); sql.append(temp_exiv_raw.getComment()); sql.append("')");
                //qDebug() << sql;
                if(!query.exec(sql)) {
                    qDebug() << "the fucking db cannot writing fucking data";
                }
                else {
                    QMutexLocker lockerCounter(&analyse_counter_mutex);
                    analyse_counter++;
                    lockerCounter.unlock();
                }
                // current_exif_raw_data.append(temp_exiv_raw);
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
