#include "GlobalData.h"

SystemConfig& GetSystemConfig() {
    return global_system_config;
}

extern QMutex folder_mutex;
extern QQueue<QString> folder_queue;
extern QMutex file_mutex;
extern QQueue<QString> file_queue;
extern QMutex analyse_lock;
extern QList<QString> analyse_result;
extern QMutex scan_counter_mutex;
extern int scan_counter;
extern QMutex analyse_counter_mutex;
extern int analyse_counter;
extern QList<QString> exif_mode;
extern QList<ExivRaw> current_exif_raw_data;

void InitGlobalVar()
{
    // 感觉很简陋但是先这么着吧
    folder_queue = QQueue<QString>();
    file_queue = QQueue<QString>();
    analyse_result = QQueue<QString>();
    scan_counter = 0;
    analyse_counter = 0;
    exif_mode = QList<QString>();
    current_exif_raw_data = QList<ExivRaw>();
}


QString ExivRaw::getFile_name()
{
return file_name;
}

QString ExivRaw::getFile_path()
{
return file_path;
}

QString ExivRaw::getTitle()
{
return title;
}

QString ExivRaw::getManufacturer()
{
return manufacturer;
}

QString ExivRaw::getCamera_model()
{
return camera_model;
}

QString ExivRaw::getLens_model()
{
return lens_model;
}

QString ExivRaw::getShooting_datetime()
{
return shooting_datetime;
}

QString ExivRaw::getPhyical_focus_length()
{
return phyical_focus_length;
}

QString ExivRaw::getEquivalent_focus_length()
{
return equivalent_focus_length;
}

QString ExivRaw::getIso()
{
return iso;
}

QString ExivRaw::getAperture()
{
return aperture;
}

QString ExivRaw::getShutter_speed()
{
return shutter_speed;
}

QString ExivRaw::getShutter_counter()
{
return shutter_counter;
}

QString ExivRaw::getExposure_compensation()
{
return exposure_compensation;
}

QString ExivRaw::getFlash_status()
{
return flash_status;
}

QString ExivRaw::getWhite_balance()
{
return white_balance;
}

QString ExivRaw::getShooting_mode()
{
return shooting_mode;
}

QString ExivRaw::getMetering_mode()
{
return metering_mode;
}

QString ExivRaw::getComment()
{
return comment;
}

QString ExivRaw::getTask_id()
{
return task_id;
}
