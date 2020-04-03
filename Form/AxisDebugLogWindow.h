#ifndef AXISDEBUGLOGWINDOW_H
#define AXISDEBUGLOGWINDOW_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDialog>
#include "quiwidget.h"

namespace Ui {
class AxisDebugLogWindow;
}

class AxisDebugLogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AxisDebugLogWindow(QWidget *parent = nullptr);
    ~AxisDebugLogWindow();

private:
    Ui::AxisDebugLogWindow *ui;

    bool max;
    QRect location;

    bool InitAxisDebugLogWindow();

private slots:
    void on_btnMenu_Close_clicked();
};


#endif // AXISDEBUGLOGWINDOW_H
