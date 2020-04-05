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
extern QList<ExivRaw> current_exif_raw_data;
extern QString current_scan_task_id;
void InitGlobalVar()
{
    // 感觉很简陋但是先这么着吧
    folder_queue = QQueue<QString>();
    file_queue = QQueue<QString>();
    analyse_result = QQueue<QString>();
    scan_counter = 0;
    analyse_counter = 0;
    current_exif_raw_data = QList<ExivRaw>();
    current_scan_task_id = "";
}

extern QList<QString> exif_mode_table;
void InitScanParameter() {
    exif_mode_table << "Exif.Image.Make"
              << "Exif.Image.Model"
              << "Exif.Photo.LensModel"
              << "Exif.Photo.FocalLength"
              << "Exif.Photo.FNumber"
              << "Exif.Photo.ExposureTime"
              << "Exif.Photo.ISOSpeedRatings"
              << "Exif.Photo.ExposureBiasValue"
              << "Exif.Photo.FocalLengthIn35mmFilm"
              << "Exif.Photo.DateTimeOriginal"
                 // 20200405 update
              << "Exif.Photo.WhiteBalance"
              << "Exif.Photo.MeteringMode";
}

void ExivRaw::setTask_id(QString str) {
    task_id = str;
}

void ExivRaw::setFile_name(QString str) {
    file_name = str;
}

void ExivRaw::setFile_path(QString str) {
    file_path = str;
}

void ExivRaw::setTitle(QString str) {
    title = str;
}

void ExivRaw::setManufacturer(QString str) {
    manufacturer = str;
}

void ExivRaw::setCamera_model(QString str) {
    camera_model = str;
}

void ExivRaw::setLens_model(QString str) {
    lens_model = str;
}

void ExivRaw::setShooting_datetime(QString str) {
    shooting_datetime = str;
}

void ExivRaw::setPhyical_focus_length(QString str) {
    phyical_focus_length = str;
}

void ExivRaw::setEquivalent_focus_length(QString str) {
    equivalent_focus_length = str;
}

void ExivRaw::setIso(QString str) {
    iso = str;
}

void ExivRaw::setAperture(QString str) {
    aperture = str;
}

void ExivRaw::setShutter_speed(QString str) {
    shutter_speed = str;
}

void ExivRaw::setShutter_counter(QString str) {
    shutter_counter = str;
}

void ExivRaw::setExposure_compensation(QString str) {
    exposure_compensation = str;
}

void ExivRaw::setFlash_status(QString str) {
    flash_status = str;
}

void ExivRaw::setWhite_balance(QString str) {
    white_balance = str;
}

void ExivRaw::setShooting_mode(QString str) {
    shooting_mode = str;
}

void ExivRaw::setMetering_mode(QString str) {
    metering_mode = str;
}

void ExivRaw::setComment(QString str) {
    comment = str;
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
