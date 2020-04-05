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

    // 切换到第一页显示
    ui->tabScanView->setCurrentIndex(0);

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
    connect(ui->btnScanViewSwitch, SIGNAL(clicked(bool)), this, SLOT(BtnScanViewSwitchClick()));

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

void AxisMainWindow::BtnScanViewSwitchClick() {
    if(ui->tabScanView->currentIndex() == 0) {
        ui->tabScanView->setCurrentIndex(1);
    }
    else if(ui->tabScanView->currentIndex() == 1) {
        ui->tabScanView->setCurrentIndex(0);
    }
}

void AxisMainWindow::ScanLogClear()
{
    ui->tbLScanLog->clear();
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
    ScanLogClear();
    ui->btnScan->setDisabled(true);

    ScanLogAppend("开始扫描目标路径下的相片……");

    current_scan_task_id = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
    QDateTime scan_datetime = QDateTime::currentDateTime();
    QString scan_datestr = scan_datetime.toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery query(global_sqlite_database);
    QString sql = "INSERT INTO EXIF_TASK(task_id, task_name, task_time_start) VALUES(?, ?, ?)";
    query.prepare(sql);
    query.addBindValue(current_scan_task_id);
    query.addBindValue("debug_task");
    query.addBindValue(scan_datestr);

    if(!query.exec()) {
        qDebug() << "fucking task error - start";
    }
    qDebug() << "start scan at " << scan_datestr;

    folder_queue.enqueue(target_folder_path);

    // 放到线程里
    // 当结束之后再分析
    CurrentScanThread current_scan;
    connect(&current_scan, SIGNAL(Done()), this, SLOT(CurrentScanFinish()));
    connect(&current_scan, SIGNAL(ScanLogAppend(QString)), this, SLOT(ScanLogAppend(QString)));
    connect(&current_scan, SIGNAL(ScanLogClear()), this, SLOT(ScanLogClear()));
    current_scan.run();
}

void AxisMainWindow::CurrentScanFinish() {
    QDateTime finish_datetime = QDateTime::currentDateTime();
    QString finish_date_str = finish_datetime.toString("yyyy-MM-dd hh:mm:ss");
    QString query_counter_str;

    QSqlQuery query(global_sqlite_database);
    QString sql = "SELECT Count(1) FROM EXIF_RAW WHERE task_id = ?";
    query.prepare(sql);
    query.addBindValue(current_scan_task_id);
    if(!query.exec()) {
        qDebug() << "fucking task error - finish - stage1";
    }
    while(query.next()) {
        query_counter_str = query.value(0).toString();
    }

    sql = "UPDATE EXIF_TASK SET task_photo_counter = ?, task_time_finish = ? WHERE task_id = ?";
    query.prepare(sql);
    query.addBindValue(query_counter_str);
    query.addBindValue(finish_date_str);
    query.addBindValue(current_scan_task_id);
    if(!query.exec()) {
        qDebug() << "fucking task error - finish - stage2";
    }

    qDebug() << "finish scan at " << finish_date_str;
    ui->btnScan->setEnabled(true);
    ui->tabScanView->setCurrentIndex(1);
    DoStatProcess();
}

bool AxisMainWindow::TableInsertBlank(QTableWidget *table)
{
    QList<QString> blank_list;
    for(int i = 0; i < table->columnCount(); i++) {
        blank_list.append("");
    }
    return TableInsert(table, blank_list);
}

// ResultTable: 1. model 2. count 3. percent
bool AxisMainWindow::TableInsert(QTableWidget* table, QList<QString> argv) {
    bool ret = true;
    if(table->columnCount() == argv.count()) {
        int rowcount = table->rowCount();
        table->insertRow(rowcount);
        for(int i = 0; i < argv.size(); i++) {
            table->setItem(rowcount, i, new QTableWidgetItem(argv[i]));
        }
    }
    else {
        ret = false;
    }
    return ret;
}

bool AxisMainWindow::TableResultInsert(QSqlQuery* query, double query_counter) {
    bool ret = true;
    QString item = query->value(0).toString();
    QString item_counter = query->value(1).toString();
    double calc_percent = query->value(1).toDouble() / query_counter * 100;
    QString item_percent = QString::number(calc_percent, '.', 2) + "%";

    TableInsert(ui->tableResultStat, QList<QString>() << item << item_counter << item_percent);
    return ret;
}

void AxisMainWindow::DoStatProcess() {
    // 先写一个 work 的，明天优化
    // 优化次数 1@20200405
    QString sqlstr;

    // TableResult init
    ui->tableResultStat->setColumnCount(3);
    ui->tableResultStat->verticalHeader()->setVisible(false);
    ui->tableResultStat->horizontalHeader()->setVisible(false);
    ui->tableResultStat->horizontalHeader()->setStretchLastSection(true);
    ui->tableResultStat->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableResultStat->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableResultStat->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query(global_sqlite_database);

    QString query_counter_str;
    QString task_time_start_str;
    QString task_time_finish_str;

    double query_counter;
    QDateTime task_time_start;
    QDateTime task_time_finish;

    sqlstr = "SELECT task_photo_counter, task_time_start, task_time_finish FROM EXIF_TASK WHERE task_id = ?";
    query.prepare(sqlstr);
    query.addBindValue(current_scan_task_id);
    if(!query.exec()) {
        qDebug() << "stat error - stage 1";
    }
    while(query.next()) {
        query_counter_str = query.value(0).toString();
        task_time_start_str = query.value(1).toString();
        task_time_finish_str = query.value(2).toString();
    }

    query_counter = query_counter_str.toDouble();
    task_time_start = QDateTime::fromString(task_time_start_str);
    task_time_finish = QDateTime::fromString(task_time_finish_str);
    uint offset_time_data = task_time_finish.toTime_t() - task_time_start.toTime_t();
    qDebug() << "task_time_start = " +  task_time_start_str;
    qDebug() << "task_time_finish = " +  task_time_finish_str;
    qDebug() << "raw task_time_start = " +  QString::number(task_time_finish.toTime_t());
    qDebug() << "raw task_time_finish = " +  QString::number(task_time_start.toTime_t());
    qDebug() << "raw offset time data = " +  QString::number(offset_time_data);
    QString offset_time_str, offset_hour, offset_minute, offset_second;
    offset_hour = (offset_time_data/3600) > 10 ? QString::number((offset_time_data/3600)) : "0" + QString::number((offset_time_data/3600));
    offset_time_data %= 3600;
    offset_minute = (offset_time_data/60) > 10 ? QString::number(offset_time_data/60) : "0" + QString::number(offset_time_data/60);
    offset_time_data %= 60;
    offset_second = offset_time_data > 10 ? QString::number(offset_time_data) : "0" + QString::number(offset_time_data);
    offset_time_str = offset_hour + ":" + offset_minute + ":" + offset_second;

    ui->lblResultStatus->setText(query_counter_str);
    ui->lblResultTimeConsumed->setText(offset_time_str);

    TableInsert(ui->tableResultStat, QList<QString>() << "制造商" << "" << "");

    sqlstr = "SELECT manufacturer, Count(*) AS counter FROM EXIF_RAW WHERE task_id = ? GROUP BY manufacturer ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.addBindValue(current_scan_task_id);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            TableResultInsert(&query, query_counter);
        }
    }

    TableInsertBlank(ui->tableResultStat);
    TableInsert(ui->tableResultStat, QList<QString>() << "相机型号" << "" << "");
    sqlstr = "SELECT camera_model, Count(*) AS counter FROM EXIF_RAW WHERE task_id = ? GROUP BY camera_model ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.addBindValue(current_scan_task_id);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
           TableResultInsert(&query, query_counter);
        }
    }

    TableInsertBlank(ui->tableResultStat);
    TableInsert(ui->tableResultStat, QList<QString>() << "镜头型号" << "" << "");
    sqlstr = "SELECT camera_model, Count(*) AS counter FROM EXIF_RAW WHERE task_id = ? GROUP BY lens_model ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.addBindValue(current_scan_task_id);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
           TableResultInsert(&query, query_counter);
        }
    }

    TableInsertBlank(ui->tableResultStat);
    TableInsert(ui->tableResultStat, QList<QString>() << "物理焦距" << "" << "");
    sqlstr = "SELECT phyical_focus_length, Count(*) AS counter FROM EXIF_RAW WHERE task_id = ? GROUP BY phyical_focus_length ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.addBindValue(current_scan_task_id);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            TableResultInsert(&query, query_counter);
        }
    }

    TableInsertBlank(ui->tableResultStat);
    TableInsert(ui->tableResultStat, QList<QString>() << "光圈" << "" << "");
    sqlstr = "SELECT aperture, Count(*) AS counter FROM EXIF_RAW WHERE task_id = ? GROUP BY aperture ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.addBindValue(current_scan_task_id);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            TableResultInsert(&query, query_counter);
        }
    }

    TableInsertBlank(ui->tableResultStat);
    TableInsert(ui->tableResultStat, QList<QString>() << "快门速度" << "" << "");
    sqlstr = "SELECT shutter_speed, Count(*) AS counter FROM EXIF_RAW WHERE task_id = ? GROUP BY shutter_speed ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.addBindValue(current_scan_task_id);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            TableResultInsert(&query, query_counter);
        }
    }

    TableInsertBlank(ui->tableResultStat);
    TableInsert(ui->tableResultStat, QList<QString>() << "感光度（ISO）" << "" << "");
    sqlstr = "SELECT iso, Count(*) AS counter FROM EXIF_RAW WHERE task_id = ? GROUP BY iso ORDER BY counter DESC";
    query.prepare(sqlstr);
    query.addBindValue(current_scan_task_id);
    query.exec();
    while(query.next()) {
        if(query.value(0).toString().trimmed() != "") {
            TableResultInsert(&query, query_counter);
        }
    }


}


