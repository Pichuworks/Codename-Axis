#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef FILETRAVERSETHREAD_H
#define FILETRAVERSETHREAD_H

#include <QDir>
#include <QDebug>
#include <QThread>
#include <QDirIterator>
#include <QList>
#include <QMetaType>
#include <QMap>

#include "include/exiv2.hpp"
#include "utils/StringUtils.h"

class FileTraverseThread : public QThread
{
    Q_OBJECT

public:
    explicit FileTraverseThread(QString folder_path);
    void DoFileTraverse();

protected:
    void run();

signals:
    void isDone(QList<QString>, QList<QString>);

private:
    struct exifModeStruct {
        QMap<QString, int> exif_detail;
    };

    QList<QString> exif_mode;
    QString selected_photo_folder_path;
    QList<QString> file_list;
    QMap<QString, exifModeStruct> exif_data;
    /*
    QMap<QString, int> manufacturer_stat;
    QMap<QString, int> camera_stat;
    QMap<QString, int> lens_stat;
    QMap<QString, int> phyical_focal_length_stat;
    QMap<QString, int> phyical_aperture_stat;
    QMap<QString, int> shutter_speed_stat;
    QMap<QString, int> iso_speed_stat;
    QMap<QString, int> equiv_focal_length_stat;
    QMap<QString, int> equiv_aperture_stat;
    */
    // todo: datetime stat
};

#endif // FILETRAVERSETHREAD_H
