#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  settings_data_ = new SettingsData();

  //  xlsx_sql_ = new XlsxSQL(settings_data_->GetPlotXlsxPath(), settings_data_->GetNpcXlsxPath(),
  //                          settings_data_->GetScenePlotXlsxPath());

  CheckAllConfigFiles();

  BindMenuActions();
}

MainWindow::~MainWindow() {
  delete ui;

  delete settings_data_;
  //  delete xlsx_sql_;
}

bool MainWindow::CheckAllConfigFiles() {
  QString warning("");

  QString npc_path = settings_data_->GetNpcXlsxPath();
  if (0 == npc_path.length()) {
    warning += GlobalStrs::WARNING_NO_NPC_FILE;
  }

  QString scene_path = settings_data_->GetScenePlotXlsxPath();
  if (0 == scene_path.length()) {
    warning += GlobalStrs::WARNING_NO_SCENE_FILE;
  }

  QString plot_path = settings_data_->GetPlotXlsxPath();
  if (0 == plot_path.length()) {
    warning += GlobalStrs::WARNING_NO_PLOT_FILE;
  }

  if (0 != warning.length()) {
    ui->warningGroup->setVisible(true);
    ui->labelWarning->setText(warning);

    return false;
  } else {
    ui->warningGroup->setVisible(false);
    return true;
  }
}

void MainWindow::ReloadSettings() {}

void MainWindow::ShowSettingWidget() {
  auto settings_ = new Settings(nullptr);

  settings_->setWindowModality(Qt::WindowModal);
  settings_->show();
}

void MainWindow::BindMenuActions() {
  connect(ui->actionShowSettings, &QAction::triggered, this, &MainWindow::ShowSettingWidget);
}
