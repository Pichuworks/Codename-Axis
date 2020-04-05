#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "SystemConfig.h"
#include <QMutex>

static SystemConfig global_system_config;
SystemConfig& GetSystemConfig();

void InitGlobalVar();

void InitScanParameter();

class ExivRaw {
private:
    QString task_id;
    QString file_name;
    QString file_path;
    QString title;
    QString manufacturer;
    QString camera_model;
    QString lens_model;
    QString shooting_datetime;
    QString phyical_focus_length;
    QString equivalent_focus_length;
    QString iso;
    QString aperture;
    QString shutter_speed;
    QString shutter_counter;
    QString exposure_compensation;
    QString flash_status;
    QString white_balance;
    QString shooting_mode;
    QString metering_mode;
    QString comment;
public:
    ExivRaw() {

    }

    ExivRaw(QString task_id, QString file_name, QString file_path, QString title, QString manufacturer, QString camera_model, QString lens_model, QString shooting_datetime,\
            QString phyical_focus_length, QString equivalent_focus_length, QString iso, QString aperture, QString shutter_speed, QString shutter_counter,\
            QString exposure_compensation, QString flash_status, QString white_balance, QString shooting_mode, QString metering_mode, QString comment) {
        this->task_id = task_id;
        this->file_name = file_name;
        this->file_name = file_path;
        this->title = title;
        this->manufacturer = manufacturer;
        this->camera_model = camera_model;
        this->lens_model = lens_model;
        this->shooting_datetime = shooting_datetime;
        this->phyical_focus_length = phyical_focus_length;
        this->equivalent_focus_length = equivalent_focus_length;
        this->iso = iso;
        this->aperture = aperture;
        this->shutter_speed = shutter_speed;
        this->shutter_counter = shutter_counter;
        this->exposure_compensation = exposure_compensation;
        this->flash_status = flash_status;
        this->white_balance = white_balance;
        this->shooting_mode = shooting_mode;
        this->metering_mode = metering_mode;
        this->comment = comment;
    }

    ~ExivRaw() {

    }

    void setTask_id(QString str);
    void setFile_name(QString str);
    void setFile_path(QString str);
    void setTitle(QString str);
    void setManufacturer(QString str);
    void setCamera_model(QString str);
    void setLens_model(QString str);
    void setShooting_datetime(QString str);
    void setPhyical_focus_length(QString str);
    void setEquivalent_focus_length(QString str);
    void setIso(QString str);
    void setAperture(QString str);
    void setShutter_speed(QString str);
    void setShutter_counter(QString str);
    void setExposure_compensation(QString str);
    void setFlash_status(QString str);
    void setWhite_balance(QString str);
    void setShooting_mode(QString str);
    void setMetering_mode(QString str);
    void setComment(QString str);

    QString getTask_id();
    QString getFile_name();
    QString getFile_path();
    QString getTitle();
    QString getManufacturer();
    QString getCamera_model();
    QString getLens_model();
    QString getShooting_datetime();
    QString getPhyical_focus_length();
    QString getEquivalent_focus_length();
    QString getIso();
    QString getAperture();
    QString getShutter_speed();
    QString getShutter_counter();
    QString getExposure_compensation();
    QString getFlash_status();
    QString getWhite_balance();
    QString getShooting_mode();
    QString getMetering_mode();
    QString getComment();
};


#endif // GLOBALDATA_H
