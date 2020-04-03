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
    qss.append("QTabWidget::pane{border:-1px;top:-2px;left:1px;}"); // 消除 tab 边框
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
        connect(btn, SIGNAL(clicked()), this, SLOT(ResultViewBtnClick()));
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
    connect(ui->actionAboutCodenameAxis, SIGNAL(triggered(bool)), this, SLOT(AboutMenuItemClick()));
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

void AxisMainWindow::ResultViewBtnClick()
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

void AxisMainWindow::AboutMenuItemClick() {
    AxisAboutWindow axisAboutWindow;
    axisAboutWindow.exec();
}
