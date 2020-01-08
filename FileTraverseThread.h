#ifndef FILETRAVERSETHREAD_H
#define FILETRAVERSETHREAD_H

#include <QDir>
#include <QDebug>
#include <QThread>
#include <QDirIterator>
#include <QList>
#include <QMetaType>

class FileTraverseThread : public QThread
{
    Q_OBJECT

public:
    explicit FileTraverseThread(QString folder_path);
    void DoFileTraverse();

protected:
    void run();

signals:
    void isDone(QList<QString>);

private:
    QString selected_photo_folder_path;
    QList<QString> file_list;
};

#endif // FILETRAVERSETHREAD_H
