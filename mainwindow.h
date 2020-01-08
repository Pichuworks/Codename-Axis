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
    QStringList file_list;

    // Functions
    void InitMainWindow();
    void InitFolderTree(QFileSystemModel *model);
    void DoSelectPhotoFolder(QFileSystemModel *model, const QModelIndex &index);

    // Threads
    FileTraverseThread* thread;

signals:
    void StartAnalyseFolderThread();

public slots:
    void SelectPhotoFolder(const QModelIndex &index);
    void AnalyseSelectedPhotoFolder();
    void GetAnalyseFolderResult(QStringList file_list);
    void About();
    void StopThread();
};

#endif // MAINWINDOW_H
