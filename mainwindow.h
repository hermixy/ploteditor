#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

  QAction *show_settings_act_;

  Ui::MainWindow *ui;

  Settings *settings;
};

#endif  // MAINWINDOW_H
