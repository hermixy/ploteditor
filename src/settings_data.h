#ifndef SETTINGS_DATA_H
#define SETTINGS_DATA_H

#include "pch.h"

class SettingsData {
 public:
  SettingsData();

 private:
  QSettings *qsettings_;
  QRegularExpression *color_hex_checker_;
};

#endif  // SETTINGS_DATA_H
