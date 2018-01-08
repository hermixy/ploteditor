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

 private:
  bool CheckAllConfigFiles();
  void ReloadSettings();

  void FillPlotTab();
  void FillNpcTab();

  void CreateActions();
  void BindMenuActions();

  QString settings_filename_;

  XlsxSQL *xlsx_sql_;
  SettingsData *settings_data_;

  QSqlTableModel *plot_model_;

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
