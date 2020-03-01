#include "FileTraverseThread.h"

FileTraverseThread::FileTraverseThread(QString folder_path) {
    this->selected_photo_folder_path = folder_path;
    qRegisterMetaType<QList<QString> > ("QList<QString>");
    // init
    exif_mode << "Exif.Image.Make"
              << "Exif.Image.Model"
              << "Exif.Photo.LensModel"
              << "Exif.Photo.FocalLength"
              << "Exif.Photo.FNumber"
              << "Exif.Photo.ExposureTime"
              << "Exif.Photo.ISOSpeedRatings";
}

void FileTraverseThread::run() {
    DoFileTraverse();
}

void FileTraverseThread::DoFileTraverse() {
    QList<QString> get_files;
    QDir dir(selected_photo_folder_path);
    QList<QString> file_detail_list;

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

    // 设置过滤参数，QDir::NoDotAndDotDot表示不会去遍历上层目录
    QDirIterator dir_iterator(selected_photo_folder_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(dir_iterator.hasNext()) {
        dir_iterator.next();
        QFileInfo file_info = dir_iterator.fileInfo();
        QString filepath = file_info.absoluteFilePath();
        if(filters.indexOf(file_info.suffix().toLower(), Qt::CaseInsensitive) != -1 && !file_info.isDir()){
            QString exif_disp = "";
            try {
                Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(FuckExivPath(filepath));
                if(image.get() == 0) {
                    qDebug() << "error w/ " + filepath;
                }
                image->readMetadata();
                Exiv2::ExifData ed = image->exifData();
                if (ed.empty()){
                    qDebug() << "no exif w/" + filepath;
                }
                else {
                    foreach(QString index, exif_mode) {
                        QString value = ed[index.toStdString()].toString().c_str();
                        exif_disp += (value + " ");
                        if(!exif_data[index].exif_detail.contains(value)) {
                            exif_data[index].exif_detail[index] = 1;
                        }
                        else{
                            exif_data[index].exif_detail[index]++;
                        }
                    }
                    if(QString::compare(exif_disp.trimmed(), "") != 0) {
                        get_files.append(filepath);
                        qDebug() << exif_disp;
                        QString str_log = filepath + "\n" + exif_disp + "\n";
                        file_detail_list.append(str_log);
                    }
                }
            }
            catch(...) {
                continue;
            }
        }
    }
    file_list = get_files;
    emit isDone(file_list, file_detail_list);
}
