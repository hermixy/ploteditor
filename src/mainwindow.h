#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pch.h"

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

  QString settings_filename_;

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
