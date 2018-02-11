#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings) {
  ui->setupUi(this);
  setFixedSize(width(), height());

  settings_data_ = new SettingsData();

  BindActions();

  LoadSettings();
}

Settings::~Settings() {
  delete ui;
  delete settings_data_;
}

void Settings::BindActions() {
  connect(ui->btnFindNpc, &QPushButton::clicked, this, &Settings::FindNpcFilePath);
  connect(ui->btnFindPlot, &QPushButton::clicked, this, &Settings::FindPlotFilePath);
  connect(ui->btnFindScene, &QPushButton::clicked, this, &Settings::FindSceneFilePath);
  connect(ui->btnFindMission, &QPushButton::clicked, this, &Settings::FindMissionFilePath);
}

void Settings::LoadSettings() {
  npc_file_path_ = settings_data_->GetNpcXlsxPath();
  scene_file_path_ = settings_data_->GetSceneXlsxPath();
  plot_file_path_ = settings_data_->GetPlotXlsxPath();
  mission_file_path_ = settings_data_->GetMissionXlsxPath();

  ui->textNpcPath->setText(npc_file_path_);
  ui->textScenePath->setText(scene_file_path_);
  ui->textPlotPath->setText(plot_file_path_);
  ui->textMissionPath->setText(mission_file_path_);
}

QString Settings::GetNpcFilePath() {
  return settings_data_->GetNpcXlsxPath();
}

QString Settings::GetSceneFilePath() {
  return settings_data_->GetSceneXlsxPath();
}

QString Settings::GetPlotFilePath() {
  return settings_data_->GetPlotXlsxPath();
}

QString Settings::GetMissionFilePath() {
  return settings_data_->GetMissionXlsxPath();
}

void Settings::FindNpcFilePath() {
  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("Excel(*.xlsx)"));

  if (filename.isNull()) {
    return;
  } else {
    npc_file_path_ = filename;
    ui->textNpcPath->setText(npc_file_path_);
    settings_data_->SetNpcXlsxPath(npc_file_path_);
  }
}

void Settings::FindPlotFilePath() {
  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("Excel(*.xlsx)"));

  if (filename.isNull()) {
    return;
  } else {
    plot_file_path_ = filename;
    ui->textPlotPath->setText(plot_file_path_);
    settings_data_->SetPlotXlsxPath(plot_file_path_);
  }
}

void Settings::FindSceneFilePath() {
  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("Excel(*.xlsx)"));

  if (filename.isNull()) {
    return;
  } else {
    scene_file_path_ = filename;
    ui->textScenePath->setText(scene_file_path_);
    settings_data_->SetSceneXlsxPath(scene_file_path_);
  }
}

void Settings::FindMissionFilePath() {
  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("Excel(*.xlsx)"));

  if (filename.isNull()) {
    return;
  } else {
    mission_file_path_ = filename;
    ui->textMissionPath->setText(mission_file_path_);
    settings_data_->SetMissionXlsxPath(mission_file_path_);
  }
}

void Settings::OnNpcFilePathChanged(const QString &new_path) {
  if (IsFileExists(new_path)) {
    npc_file_path_ = new_path;
    ui->labelNpcFilePath->setText(new_path);
  }
}

void Settings::OnPlotFilePathChanged(const QString &new_path) {
  if (IsFileExists(new_path)) {
    plot_file_path_ = new_path;
    ui->labelPlotFilePath->setText(new_path);
  }
}

void Settings::OnSceneFilePathChanged(const QString &new_path) {
  if (IsFileExists(new_path)) {
    scene_file_path_ = new_path;
    ui->labelSceneFilePath->setText(new_path);
  }
}

void Settings::OnMissionFilePathChanged(const QString &new_path) {
  if (IsFileExists(new_path)) {
    mission_file_path_ = new_path;
    ui->labelMissionFilePath->setText(new_path);
  }
}
