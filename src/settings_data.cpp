#include "settings_data.h"

SettingsData::SettingsData() {
  qsettings_ = new QSettings(GetINIFilePath(), QSettings::IniFormat);
  color_hex_checker_ =
      new QRegularExpression("^#[0-9A-Fa-f]{6}$", QRegularExpression::NoPatternOption);
}

SettingsData::~SettingsData() {
  delete qsettings_;
  delete color_hex_checker_;
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

void SettingsData::SetColor1(const QString& color) {
  if (color_hex_checker_->match(color).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR1_KEY, color);
  }
}

void SettingsData::SetColor2(const QString& color) {
  if (color_hex_checker_->match(color).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR2_KEY, color);
  }
}

void SettingsData::SetColor3(const QString& color) {
  if (color_hex_checker_->match(color).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR3_KEY, color);
  }
}

void SettingsData::SetColor4(const QString& color) {
  if (color_hex_checker_->match(color).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR4_KEY, color);
  }
}

void SettingsData::SetColor5(const QString& color) {
  if (color_hex_checker_->match(color).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR5_KEY, color);
  }
}

QString SettingsData::GetNpcXlsxPath() {
  return qsettings_->value(GlobalStrs::NPC_XLSX_FILE_KEY, "").toString();
}

QString SettingsData::GetPlotXlsxPath() {
  return qsettings_->value(GlobalStrs::PLOT_XLSX_FILE_KEY, "").toString();
}

QString SettingsData::GetScenePlotXlsxPath() {
  return qsettings_->value(GlobalStrs::SCENE_XLSX_FILE_KEY, "").toString();
}

QString SettingsData::GetColor1() {
  return qsettings_->value(GlobalStrs::COLOR1_KEY, GlobalStrs::COLOR1).toString();
}

QString SettingsData::GetColor2() {
  return qsettings_->value(GlobalStrs::COLOR2_KEY, GlobalStrs::COLOR2).toString();
}

QString SettingsData::GetColor3() {
  return qsettings_->value(GlobalStrs::COLOR3_KEY, GlobalStrs::COLOR3).toString();
}

QString SettingsData::GetColor4() {
  return qsettings_->value(GlobalStrs::COLOR4_KEY, GlobalStrs::COLOR4).toString();
}

QString SettingsData::GetColor5() {
  return qsettings_->value(GlobalStrs::COLOR5_KEY, GlobalStrs::COLOR5).toString();
}
