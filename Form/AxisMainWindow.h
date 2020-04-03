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

#include "AxisAboutWindow.h"
#include "AxisDebugLogWindow.h"

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

    bool InitAxisMainWindow();
    bool InitRibbonWidget();
    bool InitSignalSlot();
    bool InitMenu();

    bool SetSkinStyle(const QString &str);
    bool SetSkinHotfix();
    bool SetDashboardTabHide();
    bool SetResultView();
    bool SetIconFont();

private slots:
    void RibbonBtnClick();
    void ResultViewBtnClick();
    void AboutMenuItemClick();

};

#endif // AXISMAINWINDOW_H
