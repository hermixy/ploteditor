#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pch.h"

#include "xlsx_sql.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void ShowSettingWidget();
  void OnPlotRowDoubleClicked(const QModelIndex &);

  void OnBtnSearchPlotClicked();
  void OnBtnSearchMissionClicked();

 private:
  bool CheckAllConfigFiles();
  void ReloadSettings();

  void SetPlotTab();
  void SetMissionTab();

  void CreateActions();
  void BindMenuActions();

 private:
  void SetSearchPlotTab(const QString &);
  void SetSearchMissionTab(const QString &);

 private:
  QString settings_filename_;

  XlsxSQL *xlsx_sql_;
  SettingsData *settings_data_;

  QSqlTableModel *plot_model_;
  QSqlTableModel *mission_model_;

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
