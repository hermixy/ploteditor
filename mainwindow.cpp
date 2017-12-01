
#include <QMenuBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), settings(new Settings) {
  ui->setupUi(this);

  setCentralWidget(settings);

  CreateActions();
}

MainWindow::~MainWindow() {
  delete ui;
  delete settings;
}

void MainWindow::ShowSettingWidget() {}

void MainWindow::CreateActions() {
  show_settings_act_ = ui->menu_Settings->addAction(
      tr("Open Settings"), this,
      show_settings_act_->setShortcut(QKeySequence::Open));
}

void MainWindow::BindMenuActions() {
  ui->menu_Settings->addAction(show_settings_act_);
}
