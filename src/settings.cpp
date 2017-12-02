#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *) : ui(new Ui::Settings) { ui->setupUi(this); }

Settings::~Settings() { delete ui; }

void Settings::findNpcFilePath() {}

void Settings::findPlotFilePath() {}

void Settings::findSceneFilePath() {}
