#include "FileTraverseThread.h"

FileTraverseThread::FileTraverseThread(QString folder_path) {
    this->selected_photo_folder_path = folder_path;
}

void FileTraverseThread::run() {
    DoFileTraverse();
}

void FileTraverseThread::DoFileTraverse() {
    QStringList get_files;
    QDir dir(selected_photo_folder_path);
    if(!dir.exists()) {
        return;
    }
    // 设置过滤参数，QDir::NoDotAndDotDot表示不会去遍历上层目录
    QDirIterator dir_iterator(selected_photo_folder_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(dir_iterator.hasNext()) {
        dir_iterator.next();
        QFileInfo file_info = dir_iterator.fileInfo();
        QString files = file_info.absoluteFilePath();
        qDebug() << "[get file] " << tr(file_info.absoluteFilePath().toStdString().c_str());
        get_files.append(files);
    }
    file_list = get_files;
    qDebug() << "FileTraverseThread get files: ";
    qDebug() << file_list;
    qDebug() << "";
    emit isDone(file_list);
}
