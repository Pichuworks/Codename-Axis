#include "FileTraverseThread.h"

FileTraverseThread::FileTraverseThread(QString folder_path) {
    this->selected_photo_folder_path = folder_path;
    qRegisterMetaType<QList<QString> > ("QList<QString>");
}

void FileTraverseThread::run() {
    DoFileTraverse();
}

void FileTraverseThread::DoFileTraverse() {
    QList<QString> get_files;
    QDir dir(selected_photo_folder_path);
    if(!dir.exists()) {
        return;
    }

    QStringList filters;
    filters << QString("*.jpg") << QString("*.png") << QString("*.nef") << QString("*.raf") << QString("*.arw") << QString("*.tif");

    // 设置过滤参数，QDir::NoDotAndDotDot表示不会去遍历上层目录
    QDirIterator dir_iterator(selected_photo_folder_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(dir_iterator.hasNext()) {
        dir_iterator.next();
        QFileInfo file_info = dir_iterator.fileInfo();
        QString files = file_info.absoluteFilePath();
        if(filters.indexOf(file_info.suffix()) != -1 || file_info.isDir())
            get_files.append(files);
    }
    file_list = get_files;
    qDebug() << "FileTraverseThread get files counter: ";
    qDebug() << file_list.count();
    qDebug() << "";
    emit isDone(file_list);
}
