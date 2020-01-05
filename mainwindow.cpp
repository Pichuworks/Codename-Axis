#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("初始化……");

    InitMainWindow();
    InitFolderTree(path_model);

    connect(ui->folderTree, SIGNAL(clicked(QModelIndex)), this, SLOT(SelectPhotoFolder(QModelIndex)));
    connect(ui->btnAnalysePhotoFolder, SIGNAL(clicked(bool)), this, SLOT(AnalyseSelectedPhotoFolder()));


    connect(ui->actionHelpAbout, SIGNAL(triggered()), this, SLOT(About()));
    ui->statusBar->showMessage("就绪");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::InitMainWindow() {
    setWindowTitle("Codename Axis, Milestone 1");
    ui->labelPhotoFolder->setText(selected_photo_folder_path);
}

void MainWindow::InitFolderTree(QFileSystemModel *model) {

    model->setRootPath("");
    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    ui->folderTree->setModel(model);
    ui->folderTree->setColumnHidden(1, true);
    ui->folderTree->setColumnHidden(2, true);
    ui->folderTree->setColumnHidden(3, true);
    ui->folderTree->show();
}

void MainWindow::SelectPhotoFolder(const QModelIndex &index) {
    DoSelectPhotoFolder(path_model, index);
}

void MainWindow::DoSelectPhotoFolder(QFileSystemModel *model, const QModelIndex &index) {
    if(model != NULL) {
        selected_photo_folder_path = model->filePath(index);
        ui->labelPhotoFolder->setText(selected_photo_folder_path);
    }
}

void MainWindow::AnalyseSelectedPhotoFolder() {

}


void MainWindow::About() {
    QMessageBox::about(NULL, "关于", "Codename Axis, EXIF数据统计管理器。\n\nMilestone 1, Start at Jan. 5th, '19.");
}
