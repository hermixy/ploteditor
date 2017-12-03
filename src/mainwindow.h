#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pch.h"

#include "editorconfig.h"
#include "settings.h"

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

 private:
  void CreateActions();
  void BindMenuActions();

  EditorConfig *editor_config_;
  QString settings_filename_;

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
