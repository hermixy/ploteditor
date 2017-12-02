#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pch.h"

#include "editorconfig.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class Settings;

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

  Settings *settings_;
  EditorConfig *editor_config_;

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
