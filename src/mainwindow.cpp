#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  BindMenuActions();

  // read configuration

  editor_config_ = new EditorConfig(GlobalStrs::CONFIG_FILE_NAME);

  ui->textEdit->setText(editor_config_->GetField(GlobalStrs::NPC_XLSX_FILE_KEY));
  // ui->textEdit->setText(QString("Hello"));
}

MainWindow::~MainWindow() {
  delete ui;
  delete editor_config_;
}

void MainWindow::ShowSettingWidget() {
  auto settings_ = new Settings(nullptr);
  // Add this to forbit clicking the main window
  settings_->setWindowModality(Qt::ApplicationModal);
  settings_->show();
}

void MainWindow::BindMenuActions() {
  connect(ui->actionShowSettings, &QAction::triggered, this, &MainWindow::ShowSettingWidget);
}
