#include "Config/GlobalData.h"
#include "Form/quiwidget.h"
#include "Logic/AxisInit.h"

#include "Form/AxisMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/main.ico"));

    int font_id = QFontDatabase::addApplicationFont(GetSystemConfig().getMainwindow_font_path());
    QString mainwindow_font = QFontDatabase::applicationFontFamilies(font_id).at(0);
    a.setFont(QFont(mainwindow_font, 10));

    QUIWidget::setCode();
    QUIWidget::setTranslator(":/translate/qt_zh_CN.qm");
    QUIWidget::setTranslator(":/translate/widgets.qm");
    AxisInit::Instance()->start();

    QUIWidget qui;
    AxisMainWindow *axis_main_window = new AxisMainWindow;

    qui.setMainWidget(axis_main_window);

    qui.setTitle("Codename Axis Milestone 2");

    // 设置标题文本居中
    // qui.setAlignment(Qt::AlignCenter);

    // 设置窗体可拖动大小
    qui.setSizeGripEnabled(true);

    // 设置换肤下拉菜单可见
    // qui.setVisible(QUIWidget::BtnMenu, true);

    qui.setIconMain(QChar(0xf008), 11);
    // qui.setPixmap(QUIWidget::Lab_Ico, ":/main.ico");

    qui.show();

    return a.exec();
}
