#include "pch.h"

SettingsData::SettingsData() {
  qsettings_ = new QSettings(GetINIFilePath(), QSettings::IniFormat);
}

SettingsData::~SettingsData() {
  delete qsettings_;
}

void SettingsData::SetNpcXlsxPath(const QString& path) {
  qsettings_->setValue(GlobalStrs::NPC_XLSX_FILE_KEY, path);
}

void SettingsData::SetPlotXlsxPath(const QString& path) {
  qsettings_->setValue(GlobalStrs::PLOT_XLSX_FILE_KEY, path);
}

void SettingsData::SetSceneXlsxPath(const QString& path) {
  qsettings_->setValue(GlobalStrs::SCENE_XLSX_FILE_KEY, path);
}

void SettingsData::SetMissionXlsxPath(const QString& path) {
  qsettings_->setValue(GlobalStrs::MISSION_XLSX_FILE_KEY, path);
}

QString SettingsData::GetNpcXlsxPath() {
  return qsettings_->value(GlobalStrs::NPC_XLSX_FILE_KEY, "").toString();
}

QString SettingsData::GetPlotXlsxPath() {
  return qsettings_->value(GlobalStrs::PLOT_XLSX_FILE_KEY, "").toString();
}

QString SettingsData::GetSceneXlsxPath() {
  return qsettings_->value(GlobalStrs::SCENE_XLSX_FILE_KEY, "").toString();
}

QString SettingsData::GetMissionXlsxPath() {
  return qsettings_->value(GlobalStrs::MISSION_XLSX_FILE_KEY, "").toString();
}
