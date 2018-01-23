#ifndef SETTINGS_DATA_H
#define SETTINGS_DATA_H

#include <QRegularExpression>
#include <QSettings>
#include <QString>

class SettingsData {
 public:
  SettingsData();
  ~SettingsData();

 public:
  void SetNpcXlsxPath(const QString &);
  void SetPlotXlsxPath(const QString &);
  void SetSceneXlsxPath(const QString &);
  void SetMissionXlsxPath(const QString &);

  QString GetNpcXlsxPath();
  QString GetPlotXlsxPath();
  QString GetSceneXlsxPath();
  QString GetMissionXlsxPath();

 private:
  QSettings *qsettings_;
};

#endif  // SETTINGS_DATA_H
