#ifndef AXISMAINWINDOW_H
#define AXISMAINWINDOW_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QToolButton>
#include <QFontDatabase>
#include <QDebug>
#include <QUuid>
#include <QDateTime>

#include "AxisAboutWindow.h"
#include "AxisDebugLogWindow.h"
#include "Logic/FileScanner.h"

namespace Ui {
class AxisMainWindow;
}

class AxisMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AxisMainWindow(QWidget *parent = 0);
    ~AxisMainWindow();

private:
    Ui::AxisMainWindow *ui;

    QFont icon_font;

    QToolButton *prev_btn;

    enum tab_enum {TAB_STAT, TAB_EQUIP, TAB_APPEAR, TAB_SHEET, TAB_SETTING, TAB_LOG};
    enum result_view_enum {RESULT_TABLE_VIEW, RESULT_CHART_VIEW};

    QString target_folder_path;

    bool InitAxisMainWindow();
    bool InitRibbonWidget();
    bool InitSignalSlot();
    bool InitMenu();

    bool SetSkinStyle(const QString &str);
    bool SetSkinHotfix();
    bool SetDashboardTabHide();
    bool SetResultView();
    bool SetIconFont();

    void DoScanProcess();
    void DoStatProcess();

private slots:
    void RibbonBtnClick();
    void BtnResultViewClick();
    void MenuItemAboutAxisClick();
    void BtnBrowsePathClick();
    void BtnScanClick();
    void BtnExportResultClick();

public slots:
    void ScanLogAppend(QString logstr);

};

#endif // AXISMAINWINDOW_H
