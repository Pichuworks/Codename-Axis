#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>
#include <QMessageBox>
#include <QThread>
#include <QList>
#include <QMetaType>

#include "FileTraverseThread.h"
#include "version.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Variables
    QString selected_photo_folder_path = "";
    QFileSystemModel *path_model = new QFileSystemModel(this);
    QList<QString> file_list;

    // Functions
    void InitMainWindow();
    void InitFolderTree(QFileSystemModel *model);
    void DoSelectPhotoFolder(QFileSystemModel *model, const QModelIndex &index);
    void SetStatusBar(QString string);

    // Threads
    FileTraverseThread* thread;

signals:
    void StartAnalyseFolderThread();

public slots:
    void SelectPhotoFolder(const QModelIndex &index);
    void AnalyseSelectedPhotoFolder();
    void GetAnalyseFolderResult(QList<QString> file_list, QString str_log);
    void About();
    void StopThread();
};

#endif // MAINWINDOW_H
