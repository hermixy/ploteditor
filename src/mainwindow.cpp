#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  BindMenuActions();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::ShowSettingWidget() {
  auto settings_ = new Settings(nullptr);

  settings_->setWindowModality(Qt::WindowModal);
  settings_->show();
}

void MainWindow::BindMenuActions() {
  connect(ui->actionShowSettings, &QAction::triggered, this, &MainWindow::ShowSettingWidget);
}
