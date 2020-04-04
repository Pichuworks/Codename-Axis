#include "AxisMainWindow.h"
#include "ui_AxisMainWindow.h"

AxisMainWindow::AxisMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AxisMainWindow)
{
    ui->setupUi(this);
    InitAxisMainWindow();
}

AxisMainWindow::~AxisMainWindow()
{
    delete ui;
}


bool AxisMainWindow::InitAxisMainWindow() {
    bool ret = true;

    ret = SetSkinStyle(":/qss/flatblack.css");
    ret = SetDashboardTabHide();
    ret = SetSkinHotfix();
    ret = InitRibbonWidget();
    ret = InitSignalSlot();
    ret = InitMenu();
    ret = SetIconFont();
    ret = SetResultView();

    return ret;
}

bool AxisMainWindow::SetSkinHotfix() {
    bool ret = true;
    QStringList qss;
    qss.append("QTabWidget::pane{border:-1px;top:-2px;left:1px;}");
    this->setStyleSheet(qss.join(""));
    return ret;
}

bool AxisMainWindow::InitRibbonWidget() {
    bool ret = true;

    //添加自定义属性,用于切换ico用
    ui->btnPhotoStat->setProperty("ico_name", "speedtest");
    ui->btnPhotoStat->setProperty("tab_index", TAB_STAT);
    ui->btnEquipmentMgr->setProperty("ico_name", "infoextend");
    ui->btnEquipmentMgr->setProperty("tab_index", TAB_EQUIP);
    ui->btnAppearanceMgr->setProperty("ico_name", "wifitest");
    ui->btnAppearanceMgr->setProperty("tab_index", TAB_APPEAR);
    ui->btnContactSheet->setProperty("ico_name", "websitetest");
    ui->btnContactSheet->setProperty("tab_index", TAB_SHEET);
    ui->btnSettings->setProperty("ico_name", "troublecheck");
    ui->btnSettings->setProperty("tab_index", TAB_SETTING);

    ui->btnDebugLog->setProperty("ico_name", "troublecheck");
    ui->btnDebugLog->setProperty("tab_index", TAB_LOG);


    ui->widgetCentral->setProperty("form", "title");
    ui->widgetTop->setProperty("form", "title");
    ui->widgetRibbon->setProperty("nav", "top");

    // 设置顶部导航按钮
    int font_id = QFontDatabase::addApplicationFont(GetSystemConfig().getMainwindow_font_path());
    QString mainwindow_font = QFontDatabase::applicationFontFamilies(font_id).at(0);

    QList<QToolButton *> tbtns = ui->widgetRibbon->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        QSize icoSize(50, 50);
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(70);
        btn->setCheckable(true);
        btn->setFont(mainwindow_font);
        connect(btn, SIGNAL(clicked()), this, SLOT(RibbonBtnClick()));
    }

    prev_btn = ui->btnPhotoStat;
    ui->btnPhotoStat->setChecked(true);
    ui->btnPhotoStat->setIcon(QIcon(QString(":/ribbon-icon/%1_focus.png").arg(ui->btnPhotoStat->property("ico_name").toString())));
    ui->btnDebugLog->setCheckable(false);
    return ret;
}

bool AxisMainWindow::InitMenu() {
    bool ret = true;

    int font_id = QFontDatabase::addApplicationFont(GetSystemConfig().getMainwindow_font_path());
    QString mainwindow_font = QFontDatabase::applicationFontFamilies(font_id).at(0);
    ui->menuBar->setFont(QFont(mainwindow_font, 10));

    QList<QMenu *> menus = ui->menuBar->findChildren<QMenu *>();
    foreach (QMenu *menu, menus) {
        menu->setFont(mainwindow_font);
    }

    return ret;
}

bool AxisMainWindow::SetSkinStyle(const QString &str) {
    bool ret = true;
    QFile file(str);
    if (file.open(QFile::ReadOnly)) {
        QTextStream styleIn(&file);
        QString qss = styleIn.readAll();
        qApp->setStyleSheet(qss);
        QString PaletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(PaletteColor)));
        file.close();
    }
    else {
        ret = false;
    }
    return ret;
}

bool AxisMainWindow::SetDashboardTabHide() {
    bool ret = true;
    ui->tabDashboard->tabBar()->hide();
    ui->tabScanView->tabBar()->hide();
    ui->tabResultView->tabBar()->hide();
    return ret;
}

bool AxisMainWindow::SetResultView()
{
    bool ret = true;

    // 结果展示类型切换项
    ui->widgetResultViewSwitcher->setProperty("nav", "top");

    ui->btnTableView->setFont(icon_font);
    ui->btnTableView->setText(QChar(0xf03a));
    ui->btnTableView->setProperty("tab_index", RESULT_TABLE_VIEW);
    ui->btnChartView->setFont(icon_font);
    ui->btnChartView->setText(QChar(0xf080));
    ui->btnChartView->setProperty("tab_index", RESULT_CHART_VIEW);

    // 设置切换按钮
    QList<QToolButton *> tbtns = ui->widgetResultViewSwitcher->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(BtnResultViewClick()));
    }

    ui->btnTableView->setChecked(true);

    return ret;
}

bool AxisMainWindow::SetIconFont()
{
    bool ret = true;

    int fontId = QFontDatabase::addApplicationFont(":/font/fontawesome-webfont.ttf");
    QStringList fontName = QFontDatabase::applicationFontFamilies(fontId);

    if (fontName.count() > 0) {
        icon_font = QFont(fontName.at(0));
    } else {
        qDebug() << "load fontawesome-webfont.ttf error";
    }

    return ret;
}

bool AxisMainWindow::InitSignalSlot() {
    bool ret = true;
    connect(ui->actionAboutCodenameAxis, SIGNAL(triggered(bool)), this, SLOT(MenuItemAboutAxisClick()));

    connect(ui->btnBrowsePath, SIGNAL(clicked(bool)), this, SLOT(BtnBrowsePathClick()));
    connect(ui->btnScan, SIGNAL(clicked(bool)), this, SLOT(BtnScanClick()));
    connect(ui->btnExportResult, SIGNAL(clicked(bool)), this, SLOT(BtnExportResultClick()));
    return ret;
}

void AxisMainWindow::RibbonBtnClick() {
    QToolButton *b = (QToolButton *)sender();
    QString text = b->text();

    QList<QToolButton *> btns = ui->widgetRibbon->findChildren<QToolButton *>();
    foreach (QToolButton *btn, btns) {
        QString ico_name = btn->property("ico_name").toString();
        QString prev_ico_name = prev_btn->property("ico_name").toString();
        int tab_index = btn->property("tab_index").toInt();

        if (btn != b) {
            btn->setChecked(false);
            btn->setIcon(QIcon(QString(":/ribbon-icon/%1.png").arg(ico_name)));
        }
        else {
            if (tab_index != TAB_LOG) {
                btn->setChecked(true);
                btn->setIcon(QIcon(QString(":/ribbon-icon/%1_focus.png").arg(ico_name)));
                ui->tabDashboard->setCurrentIndex(tab_index);
                prev_btn = btn;
            }
            else if (tab_index == TAB_LOG) {
                tab_index = prev_btn->property("tab_index").toInt();
                prev_btn->setChecked(true);
                btn->setIcon(QIcon(QString(":/ribbon-icon/%1.png").arg(ico_name)));
                prev_btn->setIcon(QIcon(QString(":/ribbon-icon/%1_focus.png").arg(prev_ico_name)));
                ui->tabDashboard->setCurrentIndex(tab_index);

                AxisDebugLogWindow AxisDebugLogWindow;
                AxisDebugLogWindow.exec();
            }
        }
    }
}

void AxisMainWindow::BtnResultViewClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString text = b->text();

    QList<QToolButton *> btns = ui->widgetResultViewSwitcher->findChildren<QToolButton *>();
    foreach (QToolButton *btn, btns) {
        // int tab_index = btn->property("tab_index").toInt();

        if (btn != b) {
            btn->setChecked(false);
        }
        else {
            btn->setChecked(true);
        }
    }
}

void AxisMainWindow::MenuItemAboutAxisClick() {
    AxisAboutWindow axisAboutWindow;
    axisAboutWindow.exec();
}

void AxisMainWindow::BtnBrowsePathClick() {
    target_folder_path = QFileDialog::getExistingDirectory(this, "选择目标路径");
    if (target_folder_path.isEmpty()) {
        return;
    }
    else {
        target_folder_path += "/";
        ui->tbFolderPath->setText(target_folder_path);
    }
}

void AxisMainWindow::BtnScanClick() {
    DoScanProcess();
}

void AxisMainWindow::BtnExportResultClick()
{
    DoStatProcess();
}

void AxisMainWindow::ScanLogAppend(QString logstr)
{
    ui->tbLScanLog->append(logstr);
}


// Scan Process
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
extern QString current_scan_task_id;

extern QSqlDatabase global_sqlite_database;

void AxisMainWindow::DoScanProcess() {

    InitGlobalVar();

    ui->tabScanView->setCurrentIndex(0);
    ui->tbLScanLog->setText("");
    ui->btnScan->setDisabled(true);

    ScanLogAppend("开始扫描目标路径\n");

    current_scan_task_id = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
    QDateTime scan_datetime = QDateTime::currentDateTime();
    QString scan_datestr = scan_datetime.toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery query(global_sqlite_database);
    QString sql = "insert into EXIF_TASK(task_id, task_datetime, task_name) values";
    sql.append("('"); sql.append(current_scan_task_id); sql.append("', ");
    sql.append("'"); sql.append(scan_datestr); sql.append("', ");
    sql.append("'"); sql.append("debug_task"); sql.append("')");
    if(!query.exec(sql)) {
        qDebug() << "fucking task error";
    }


    exif_mode_table << "Exif.Image.Make"
              << "Exif.Image.Model"
              << "Exif.Photo.LensModel"
              << "Exif.Photo.FocalLength"
              << "Exif.Photo.FNumber"
              << "Exif.Photo.ExposureTime"
              << "Exif.Photo.ISOSpeedRatings"
              << "Exif.Photo.ExposureBiasValue"
              << "Exif.Photo.FocalLengthIn35mmFilm"
              << "Exif.Photo.DateTimeOriginal";

    folder_queue.enqueue(target_folder_path);

    ScanThread scanner[FUCK_THREADS];
    AnalyseThread analyser[FUCK_THREADS];

    while(!folder_queue.isEmpty() || !file_queue.isEmpty()) {
        for(int i = 0; i < FUCK_THREADS; i++) {
            connect(&analyser[i],SIGNAL(ScanLogAppend(QString)),this,SLOT(ScanLogAppend(QString)));
            scanner[i].run();
            analyser[i].run();
        }
    }

    ui->btnScan->setEnabled(true);
    ui->tabScanView->setCurrentIndex(1);
    DoStatProcess();

}

void AxisMainWindow::DoStatProcess() {
    // 先写一个 work 的，明天优化
    QMap<QString, QString> manufacturer_map;
    QMap<QString, QString> camera_model_map;
    QMap<QString, QString> phyical_focus_length_map;
    QMap<QString, QString> aperture_map;
    QMap<QString, QString> iso_map;
    QMap<QString, QString> shutter_speed_map;
    QString sqlstr;

    // disp
    ui->lblResultStatus->setText(QString::number(analyse_counter));
    ui->tableResultStat->setColumnCount(2);
    ui->tableResultStat->verticalHeader()->setVisible(false);
    ui->tableResultStat->horizontalHeader()->setVisible(false);
    ui->tableResultStat->horizontalHeader()->setStretchLastSection(true);
    ui->tableResultStat->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    QSqlQuery query(global_sqlite_database);

    sqlstr = "SELECT Count(1) FROM EXIF_RAW";
    query.prepare(sqlstr);
    query.exec();
    while(query.next()) {
        ui->lblResultStatus->setText(query.value(0).toString());
    }

    int rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem("制造商"));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    sqlstr = "SELECT manufacturer, Count(*) AS counter FROM EXIF_RAW GROUP BY manufacturer ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            rowcount = ui->tableResultStat->rowCount();
            ui->tableResultStat->insertRow(rowcount);
            ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(query.value(1).toString()));
            manufacturer_map[query.value(0).toString()] = query.value(1).toString();
        }
    }

    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(""));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem("相机型号"));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    sqlstr = "SELECT camera_model, Count(*) AS counter FROM EXIF_RAW GROUP BY camera_model ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            rowcount = ui->tableResultStat->rowCount();
            ui->tableResultStat->insertRow(rowcount);
            ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(query.value(1).toString()));
            camera_model_map[query.value(0).toString()] = query.value(1).toString();
        }
    }

    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(""));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem("物理焦距"));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    sqlstr = "SELECT phyical_focus_length, Count(*) AS counter FROM EXIF_RAW GROUP BY phyical_focus_length ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            rowcount = ui->tableResultStat->rowCount();
            ui->tableResultStat->insertRow(rowcount);
            ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(query.value(1).toString()));
            phyical_focus_length_map[query.value(0).toString()] = query.value(1).toString();
        }
    }

    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(""));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem("光圈"));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    sqlstr = "SELECT aperture, Count(*) AS counter FROM EXIF_RAW GROUP BY aperture ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            rowcount = ui->tableResultStat->rowCount();
            ui->tableResultStat->insertRow(rowcount);
            ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(query.value(1).toString()));
            aperture_map[query.value(0).toString()] = query.value(1).toString();
        }
    }

    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(""));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem("快门速度"));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    sqlstr = "SELECT shutter_speed, Count(*) AS counter FROM EXIF_RAW GROUP BY shutter_speed ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            rowcount = ui->tableResultStat->rowCount();
            ui->tableResultStat->insertRow(rowcount);
            ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(query.value(1).toString()));
            shutter_speed_map[query.value(0).toString()] = query.value(1).toString();
        }
    }

    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(""));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    rowcount = ui->tableResultStat->rowCount();
    ui->tableResultStat->insertRow(rowcount);
    ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem("ISO"));
    ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(""));
    sqlstr = "SELECT iso, Count(*) AS counter FROM EXIF_RAW GROUP BY iso ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            rowcount = ui->tableResultStat->rowCount();
            ui->tableResultStat->insertRow(rowcount);
            ui->tableResultStat->setItem(rowcount, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableResultStat->setItem(rowcount, 1, new QTableWidgetItem(query.value(1).toString()));
            iso_map[query.value(0).toString()] = query.value(1).toString();
        }
    }

    ui->tableResultStat->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableResultStat->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
