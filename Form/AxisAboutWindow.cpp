#include "AxisAboutWindow.h"
#include "ui_AxisAboutWindow.h"


AxisAboutWindow::AxisAboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisAboutWindow)
{
    ui->setupUi(this);
    InitAxisAboutWindow();
}

AxisAboutWindow::~AxisAboutWindow()
{
    delete ui;
}

bool AxisAboutWindow::InitAxisAboutWindow()
{
    bool ret = true;

    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xF00d));
    FillAxisAboutText();

    connect(ui->btnOK, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Close_clicked()));

    return ret;
}

bool AxisAboutWindow::FillAxisAboutText()
{
    bool ret = true;


    QString strProjName         = GetSystemConfig().getProjectName();
    QString strWindowTitle      = ui->lblAboutLabel->text() + strProjName;
    QString strProjDesc         = GetSystemConfig().getProjectDescribe();
    QString strProjVer          = GetSystemConfig().getProjectVersion() + " / Build " + GetSystemConfig().getProjectBuild() + ", from resivion " + GetSystemConfig().getProjectRevision() + " on " + GetSystemConfig().getProjectComplieTime();
    QString strProjCompiler     = GetSystemConfig().getProjectDistSystemComplier();
    QString strProjCopyright    = GetSystemConfig().getProjectCopyright();
    QString strProjLink         = "<a style='color: #00BFFF;' href=\"" + GetSystemConfig().getProjectLink() + "\">Fork me from GitHub!";


    this->setWindowTitle(strWindowTitle);
    this->ui->lblAboutWindow->setText(strProjName);
    this->ui->lblProjectName->setText(strProjName);
    this->ui->lblProjectDesc->setText(strProjDesc);
    this->ui->lblVersion->setText(strProjVer);
    this->ui->lblSystemCompiler->setText(strProjCompiler);
    this->ui->lblCopyright->setText(strProjCopyright);
    this->ui->lblForkMe->setOpenExternalLinks(true);
    this->ui->lblForkMe->setText(strProjLink);

    return ret;
}

void AxisAboutWindow::on_btnMenu_Close_clicked()
{
    close();
}
