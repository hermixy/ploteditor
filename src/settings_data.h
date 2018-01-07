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

  void SetColor1(const QString &);
  void SetColor2(const QString &);
  void SetColor3(const QString &);
  void SetColor4(const QString &);
  void SetColor5(const QString &);

  QString GetNpcXlsxPath();
  QString GetPlotXlsxPath();
  QString GetScenePlotXlsxPath();
  QString GetMissionXlsxPath();

  QString GetColor1();
  QString GetColor2();
  QString GetColor3();
  QString GetColor4();
  QString GetColor5();

 private:
  QSettings *qsettings_;
  QRegularExpression *color_hex_checker_;
};

#endif  // SETTINGS_DATA_H
