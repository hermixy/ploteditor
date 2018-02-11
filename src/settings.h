#ifndef SETTINGS_H
#define SETTINGS_H

#include "pch.h"
#include "settings_data.h"

namespace Ui {
class Settings;
}  // namespace Ui

class Settings : public QDialog {
  Q_OBJECT

 public:
  explicit Settings(QWidget *parent = 0);
  ~Settings();

 public:
  QString GetNpcFilePath();
  QString GetSceneFilePath();
  QString GetPlotFilePath();
  QString GetMissionFilePath();

 private:
  // bind the buttons' actions
  void BindActions();

  void LoadSettings();

 private slots:
  // ui panel browser the npc file path.
  void FindNpcFilePath();

  // ui panel browser the plot file path.
  void FindPlotFilePath();

  // ui panel browser the scene file path.
  void FindSceneFilePath();

  // ui panel browser the mission file path.
  void FindMissionFilePath();

  void OnNpcFilePathChanged(const QString &);
  void OnPlotFilePathChanged(const QString &);
  void OnSceneFilePathChanged(const QString &);
  void OnMissionFilePathChanged(const QString &);

 private:
  QString npc_file_path_;
  QString plot_file_path_;
  QString scene_file_path_;
  QString mission_file_path_;

 private:
  Ui::Settings *ui;

  SettingsData *settings_data_;
};

#endif  // SETTINGS_H
