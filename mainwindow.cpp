
#include <QMenuBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

MainWindow::ShowSettingWidget() {}

MainWindow::BindMenuActions() {
  ui->menu_Settings->addAction(show_settings_act_);
}
