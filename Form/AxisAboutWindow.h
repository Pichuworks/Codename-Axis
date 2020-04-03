#ifndef AXISABOUTWINDOW_H
#define AXISABOUTWINDOW_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDialog>
#include <QFile>
#include <QTextStream>

#include "quiwidget.h"
#include "Config/GlobalData.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AxisAboutWindow; }
QT_END_NAMESPACE

class AxisAboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AxisAboutWindow(QWidget *parent = nullptr);
    ~AxisAboutWindow();

private:
    Ui::AxisAboutWindow *ui;

    bool max;
    QRect location;

    bool InitAxisAboutWindow();
    bool FillAxisAboutText();

private slots:
    void on_btnMenu_Close_clicked();
};
#endif // AXISABOUTWINDOW_H
