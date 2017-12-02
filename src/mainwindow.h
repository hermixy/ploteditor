#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settings.h"

#include <QMainWindow>

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

  Ui::MainWindow *ui;

  Settings *settings_;
};

#endif  // MAINWINDOW_H
