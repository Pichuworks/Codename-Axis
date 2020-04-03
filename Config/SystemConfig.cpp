#include "SystemConfig.h"

SystemConfig::SystemConfig()
{
    InitSystemConfig();
}

SystemConfig::~SystemConfig()
{

}

bool SystemConfig::InitSystemConfig() {
    bool ret = true;

    InitSystemSettings();
    InitProjectInfo();

    return ret;
}

bool SystemConfig::InitSystemSettings() {
    bool ret = true;

    setMainwindow_font_path(":/font/wqy-microhei.ttc");

    return ret;
}


bool SystemConfig::InitProjectInfo() {
    bool ret = true;

    setProjectName("Codename Axis");
    setProjectCodename("Codename Axis");
    setProjectKey("CodenameAxis");
    setProjectDescribe("基于 Exiv2 的相片数据与统计管理器。");
    setProjectVersion(DEV_VERSION);
    setProjectBuild(BUILD_COUNTER);
    setProjectRevision(COMMIT_INFO);
    setProjectComplieTime(QString(COMMIT_DATE) + " " + QString(COMMIT_TIME));
    setProjectDistSystemComplier(DEV_ENV);
    setProjectCopyright("枫光摄影兴趣小组 开发者网络");
    setProjectLink("https://github.com/Pichuworks/Codename-Axis");

    return ret;
}

QString SystemConfig::getProjectName() const
{
    return ProjectName;
}

void SystemConfig::setProjectName(const QString &value)
{
    ProjectName = value;
}

QString SystemConfig::getProjectKey() const
{
    return ProjectKey;
}

void SystemConfig::setProjectKey(const QString &value)
{
    ProjectKey = value;
}

QString SystemConfig::getProjectCodename() const
{
    return ProjectCodename;
}

void SystemConfig::setProjectCodename(const QString &value)
{
    ProjectCodename = value;
}

QString SystemConfig::getProjectDescribe() const
{
    return ProjectDescribe;
}

void SystemConfig::setProjectDescribe(const QString &value)
{
    ProjectDescribe = value;
}

QString SystemConfig::getProjectVersion() const
{
    return ProjectVersion;
}

void SystemConfig::setProjectVersion(const QString &value)
{
    ProjectVersion = value;
}

QString SystemConfig::getProjectBuild() const
{
    return ProjectBuild;
}

void SystemConfig::setProjectBuild(const QString &value)
{
    ProjectBuild = value;
}

QString SystemConfig::getProjectRevision() const
{
    return ProjectRevision;
}

void SystemConfig::setProjectRevision(const QString &value)
{
    ProjectRevision = value;
}

QString SystemConfig::getProjectCopyright() const
{
    return ProjectCopyright;
}

void SystemConfig::setProjectCopyright(const QString &value)
{
    ProjectCopyright = value;
}

QString SystemConfig::getProjectDistSystemComplier() const
{
    return ProjectDistSystemComplier;
}

void SystemConfig::setProjectDistSystemComplier(const QString &value)
{
    ProjectDistSystemComplier = value;
}

QString SystemConfig::getProjectLink() const
{
    return ProjectLink;
}

void SystemConfig::setProjectLink(const QString &value)
{
    ProjectLink = value;
}

QString SystemConfig::getProjectComplieTime() const
{
    return ProjectComplieTime;
}

void SystemConfig::setProjectComplieTime(const QString &value)
{
    ProjectComplieTime = value;
}

QString SystemConfig::getMainwindow_font_path() const
{
    return mainwindow_font_path;
}

void SystemConfig::setMainwindow_font_path(const QString &value)
{
    mainwindow_font_path = value;
}
