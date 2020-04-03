#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QString>
#include <QFontDatabase>

class SystemConfig {

private:
    QString ProjectName;
    QString ProjectKey;
    QString ProjectCodename;
    QString ProjectDescribe;

    QString ProjectVersion;
    QString ProjectBuild;
    QString ProjectRevision;
    QString ProjectComplieTime;

    QString ProjectCopyright;

    QString ProjectDistSystemComplier;
    QString ProjectLink;

    QString mainwindow_font_path;

public:

    SystemConfig();
    ~SystemConfig();

    bool InitSystemConfig();

    bool InitSystemSettings();
    bool InitProjectInfo();

    QString getProjectName() const;
    void setProjectName(const QString &value);

    QString getProjectKey() const;
    void setProjectKey(const QString &value);

    QString getProjectCodename() const;
    void setProjectCodename(const QString &value);

    QString getProjectDescribe() const;
    void setProjectDescribe(const QString &value);

    QString getProjectVersion() const;
    void setProjectVersion(const QString &value);

    QString getProjectBuild() const;
    void setProjectBuild(const QString &value);

    QString getProjectRevision() const;
    void setProjectRevision(const QString &value);

    QString getProjectCopyright() const;
    void setProjectCopyright(const QString &value);

    QString getProjectDistSystemComplier() const;
    void setProjectDistSystemComplier(const QString &value);

    QString getProjectLink() const;
    void setProjectLink(const QString &value);

    QString getProjectComplieTime() const;
    void setProjectComplieTime(const QString &value);

    QString getMainwindow_font_path() const;
    void setMainwindow_font_path(const QString &value);

};


#endif // SYSTEMCONFIG_H
