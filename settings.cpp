#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) : ui(new Ui::Settings) {
  ui->setupUi(this);
}

void Settings::findNpcFilePath() {}

void Settings::findPlotFilePath() {}

void Settings::findSceneFilePath() {}

Settings::~Settings() { delete ui; }
