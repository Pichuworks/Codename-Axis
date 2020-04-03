#include "AxisDebugLogWindow.h"
#include "ui_AxisDebugLogWindow.h"

AxisDebugLogWindow::AxisDebugLogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisDebugLogWindow)
{
    ui->setupUi(this);
    InitAxisDebugLogWindow();
}

AxisDebugLogWindow::~AxisDebugLogWindow()
{
    delete ui;
}

bool AxisDebugLogWindow::InitAxisDebugLogWindow()
{
    bool ret = true;

    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xF00d));

    return ret;
}

void AxisDebugLogWindow::on_btnMenu_Close_clicked()
{
    close();
}
