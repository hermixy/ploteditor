#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *) : ui(new Ui::Settings) {
  ui->setupUi(this);
  setFixedSize(width(), height());

  settings_data_ = new SettingsData();

  color_hex_checker_ =
      new QRegularExpression("^#[0-9A-Fa-f]{6}$", QRegularExpression::NoPatternOption);

  BindActions();

  LoadSettings();

  SetQLineTextPalette(ui->textColor1Eg, settings_data_->GetColor1());
  SetQLineTextPalette(ui->textColor2Eg, settings_data_->GetColor2());
  SetQLineTextPalette(ui->textColor3Eg, settings_data_->GetColor3());
  SetQLineTextPalette(ui->textColor4Eg, settings_data_->GetColor4());
  SetQLineTextPalette(ui->textColor5Eg, settings_data_->GetColor5());
}

Settings::~Settings() {
  delete ui;
  delete color_hex_checker_;
  delete settings_data_;
}

void Settings::BindActions() {
  connect(ui->btnFindNpc, &QPushButton::clicked, this, &Settings::FindNpcFilePath);
  connect(ui->btnFindPlot, &QPushButton::clicked, this, &Settings::FindPlotFilePath);
  connect(ui->btnFindScene, &QPushButton::clicked, this, &Settings::FindSceneFilePath);
  connect(ui->btnFindMission, &QPushButton::clicked, this, &Settings::FindMissionFilePath);

  connect(ui->textColor1, SIGNAL(textChanged(const QString &)), this,
          SLOT(OnColor1Changed(const QString &)));
  connect(ui->textColor2, SIGNAL(textChanged(const QString &)), this,
          SLOT(OnColor2Changed(const QString &)));
  connect(ui->textColor3, SIGNAL(textChanged(const QString &)), this,
          SLOT(OnColor3Changed(const QString &)));
  connect(ui->textColor4, SIGNAL(textChanged(const QString &)), this,
          SLOT(OnColor4Changed(const QString &)));
  connect(ui->textColor5, SIGNAL(textChanged(const QString &)), this,
          SLOT(OnColor5Changed(const QString &)));
}

void Settings::SetQLineTextPalette(QLineEdit *le, const QString &colorStr) {
  QColor textColor(colorStr);

  QPalette palette;
  palette.setColor(QPalette::Text, textColor);

  le->setPalette(palette);
}

void Settings::LoadSettings() {
  npc_file_path_ = settings_data_->GetNpcXlsxPath();
  scene_file_path_ = settings_data_->GetScenePlotXlsxPath();
  plot_file_path_ = settings_data_->GetPlotXlsxPath();
  mission_file_path_ = settings_data_->GetMissionXlsxPath();

  ui->textNpcPath->setText(npc_file_path_);
  ui->textScenePath->setText(scene_file_path_);
  ui->textPlotPath->setText(plot_file_path_);
  ui->textMissionPath->setText(mission_file_path_);

  color1_name_ = settings_data_->GetColor1();
  color2_name_ = settings_data_->GetColor2();
  color3_name_ = settings_data_->GetColor3();
  color4_name_ = settings_data_->GetColor4();
  color5_name_ = settings_data_->GetColor5();

  ui->textColor1->setText(color1_name_);
  ui->textColor2->setText(color2_name_);
  ui->textColor3->setText(color3_name_);
  ui->textColor4->setText(color4_name_);
  ui->textColor5->setText(color5_name_);
}

QString Settings::GetNpcFilePath() {
  return settings_data_->GetNpcXlsxPath();
}

QString Settings::GetSceneFilePath() {
  return settings_data_->GetScenePlotXlsxPath();
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

void Settings::OnColor1Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color1_name_ = new_color;
    ui->textColor1->setText(new_color);

    SetQLineTextPalette(ui->textColor1Eg, new_color);

    settings_data_->SetColor1(new_color);
  }
}

void Settings::OnColor2Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color2_name_ = new_color;
    ui->textColor2->setText(new_color);

    SetQLineTextPalette(ui->textColor2Eg, new_color);

    settings_data_->SetColor2(new_color);
  }
}

void Settings::OnColor3Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color3_name_ = new_color;
    ui->textColor3->setText(new_color);

    SetQLineTextPalette(ui->textColor3Eg, new_color);

    settings_data_->SetColor3(new_color);
  }
}

void Settings::OnColor4Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color4_name_ = new_color;
    ui->textColor4->setText(new_color);

    SetQLineTextPalette(ui->textColor4Eg, new_color);

    settings_data_->SetColor4(new_color);
  }
}

void Settings::OnColor5Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color5_name_ = new_color;
    ui->textColor5->setText(new_color);

    SetQLineTextPalette(ui->textColor5Eg, new_color);

    settings_data_->SetColor5(new_color);
  }
}
