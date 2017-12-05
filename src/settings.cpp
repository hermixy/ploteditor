#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *) : ui(new Ui::Settings) {
  ui->setupUi(this);
  setFixedSize(width(), height());

  filename_ = GetINIFilePath();
  qsettings_ = new QSettings(filename_, QSettings::IniFormat);

  color_hex_checker_ =
      new QRegularExpression("^#[0-9A-F]{6}$", QRegularExpression::NoPatternOption);

  BindActions();
  LoadSettings(qsettings_);

  SetQLineTextPalette(ui->textColor1Eg, color1_name_);
  SetQLineTextPalette(ui->textColor2Eg, color2_name_);
  SetQLineTextPalette(ui->textColor3Eg, color3_name_);
  SetQLineTextPalette(ui->textColor4Eg, color4_name_);
  SetQLineTextPalette(ui->textColor5Eg, color5_name_);
}

Settings::~Settings() {
  delete ui;
  delete qsettings_;
  delete color_hex_checker_;
}

void Settings::BindActions() {
  connect(ui->btnSave, &QPushButton::clicked, this, &Settings::SaveSettings);

  connect(ui->btnFindNpc, &QPushButton::clicked, this, &Settings::FindNpcFilePath);
  connect(ui->btnFindPlot, &QPushButton::clicked, this, &Settings::FindPlotFilePath);
  connect(ui->btnFindScene, &QPushButton::clicked, this, &Settings::FindSceneFilePath);

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

void Settings::LoadSettings(const QSettings *qs) {
  npc_file_path_ = qs->value(GlobalStrs::NPC_XLSX_FILE_KEY, "").toString();
  scene_file_path_ = qs->value(GlobalStrs::PLOT_XLSX_FILE_KEY, "").toString();
  plot_file_path_ = qs->value(GlobalStrs::PLOT_XLSX_FILE_KEY, "").toString();

  ui->textNpcPath->setText(npc_file_path_);
  ui->textScenePath->setText(scene_file_path_);
  ui->textPlotPath->setText(plot_file_path_);

  color1_name_ = qs->value(GlobalStrs::COLOR1_KEY, GlobalStrs::COLOR1).toString();
  color2_name_ = qs->value(GlobalStrs::COLOR2_KEY, GlobalStrs::COLOR2).toString();
  color3_name_ = qs->value(GlobalStrs::COLOR3_KEY, GlobalStrs::COLOR3).toString();
  color4_name_ = qs->value(GlobalStrs::COLOR4_KEY, GlobalStrs::COLOR4).toString();
  color5_name_ = qs->value(GlobalStrs::COLOR5_KEY, GlobalStrs::COLOR5).toString();

  ui->textColor1->setText(color1_name_);
  ui->textColor2->setText(color2_name_);
  ui->textColor3->setText(color3_name_);
  ui->textColor4->setText(color4_name_);
  ui->textColor5->setText(color5_name_);
}

void Settings::SaveSettings() {
  qsettings_->setValue(GlobalStrs::NPC_XLSX_FILE_KEY, npc_file_path_);
  qsettings_->setValue(GlobalStrs::PLOT_XLSX_FILE_KEY, plot_file_path_);
  qsettings_->setValue(GlobalStrs::SCENE_XLSX_FILE_KEY, scene_file_path_);

  if (color_hex_checker_->match(color1_name_).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR1_KEY, color1_name_);
  }

  if (color_hex_checker_->match(color2_name_).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR2_KEY, color2_name_);
  }

  if (color_hex_checker_->match(color3_name_).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR3_KEY, color3_name_);
  }

  if (color_hex_checker_->match(color4_name_).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR4_KEY, color4_name_);
  }

  if (color_hex_checker_->match(color5_name_).hasMatch()) {
    qsettings_->setValue(GlobalStrs::COLOR5_KEY, color5_name_);
  }
}

QString Settings::GetNpcFilePath() {
  return qsettings_->value(GlobalStrs::NPC_XLSX_FILE_KEY, "").toString();
}

QString Settings::GetSceneFilePath() {
  return qsettings_->value(GlobalStrs::SCENE_XLSX_FILE_KEY, "").toString();
}

QString Settings::GetPlotFilePath() {
  return qsettings_->value(GlobalStrs::PLOT_XLSX_FILE_KEY, "").toString();
}

void Settings::FindNpcFilePath() {
  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("Excel(*.xlsx)"));

  if (filename.isNull()) {
    return;
  } else {
    npc_file_path_ = filename;
    ui->textNpcPath->setText(filename);
  }
}

void Settings::FindPlotFilePath() {
  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("Excel(*.xlsx)"));

  if (filename.isNull()) {
    return;
  } else {
    plot_file_path_ = filename;
    ui->textPlotPath->setText(filename);
  }
}

void Settings::FindSceneFilePath() {
  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("Excel(*.xlsx)"));

  if (filename.isNull()) {
    return;
  } else {
    scene_file_path_ = filename;
    ui->textScenePath->setText(filename);
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

void Settings::OnColor1Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color1_name_ = new_color;
    ui->textColor1->setText(new_color);

    SetQLineTextPalette(ui->textColor1Eg, new_color);
  }
}

void Settings::OnColor2Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color2_name_ = new_color;
    ui->textColor2->setText(new_color);

    SetQLineTextPalette(ui->textColor2Eg, new_color);
  }
}

void Settings::OnColor3Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color3_name_ = new_color;
    ui->textColor3->setText(new_color);

    SetQLineTextPalette(ui->textColor3Eg, new_color);
  }
}

void Settings::OnColor4Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color4_name_ = new_color;
    ui->textColor4->setText(new_color);

    SetQLineTextPalette(ui->textColor4Eg, new_color);
  }
}

void Settings::OnColor5Changed(const QString &new_color) {
  if (color_hex_checker_->match(new_color).hasMatch()) {
    color5_name_ = new_color;
    ui->textColor5->setText(new_color);

    SetQLineTextPalette(ui->textColor5Eg, new_color);
  }
}
