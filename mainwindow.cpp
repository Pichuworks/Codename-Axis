#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetStatusBar("初始化……");

    qRegisterMetaType<QList<QString> > ("QList<QString>");

    InitMainWindow();
    InitFolderTree(path_model);

    // Button
    connect(ui->folderTree, SIGNAL(clicked(QModelIndex)), this, SLOT(SelectPhotoFolder(QModelIndex)));
    connect(ui->btnAnalysePhotoFolder, SIGNAL(clicked(bool)), this, SLOT(AnalyseSelectedPhotoFolder()));

    // Menu
    connect(ui->actionHelpAbout, SIGNAL(triggered()), this, SLOT(About()));

    SetStatusBar("就绪");
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
    // Thread
    thread = new FileTraverseThread(selected_photo_folder_path);
    connect(thread, SIGNAL(isDone(QList<QString>, QString)), this, SLOT(GetAnalyseFolderResult(QList<QString>, QString)));
    connect(this, SIGNAL(destroyed()), this, SLOT(StopThread()));
    thread->start();
    ui->btnAnalysePhotoFolder->setDisabled(true);
    SetStatusBar("正在分析文件，请稍候……");
}

void MainWindow::GetAnalyseFolderResult(QList<QString> file_list, QString str_log) {
    this->file_list = file_list;
    // qDebug() << "MainWindow get result counter: ";
    // qDebug() << this->file_list.count();
    // qDebug() << "";
    QString status_msg;
    SetStatusBar(QString().sprintf("分析结束，共分析 %d 份文件。", file_list.count()));
    ui->textBrowserLog->setText(str_log);
    ui->btnAnalysePhotoFolder->setEnabled(true);
}

void MainWindow::StopThread() {
    thread->quit();
    thread->wait();
}

void MainWindow::SetStatusBar(QString string) {
    ui->statusBar->showMessage(string);
}

void MainWindow::About() {
    QString about_message;
    about_message.append("Codename Axis, EXIF数据统计管理器。\n\n");
    about_message.append("Milestone 1, Start at Jan. 5th, '19.\n\n");
    about_message.append(QString().sprintf("Commit on %s %s , ", BUILD_DATE, BUILD_TIME));
    about_message.append(QString().sprintf("revision %s/%s\n\n", BUILD_INFO, BUILD_BRANCH));
    about_message.append("Repo: https://github.com/Pichuworks/Codename-Axis");
    QMessageBox aboutMessageBox(QMessageBox::NoIcon, "关于", about_message);
    aboutMessageBox.setIconPixmap(QPixmap(":/image/favicon.png"));
    aboutMessageBox.exec();
}
