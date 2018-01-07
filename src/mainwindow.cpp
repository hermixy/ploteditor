#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plotviewer/ploteditdialog.h"
#include "progressbar.h"
#include "settings.h"

#include "plotviewer/plotviewer.h"

#include "utils.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowTitle(tr("Plot Editor Window"));

  settings_data_ = new SettingsData();

  if (CheckAllConfigFiles()) {
    xlsx_sql_ = new XlsxSQL(settings_data_->GetPlotXlsxPath(), settings_data_->GetNpcXlsxPath(),
                            settings_data_->GetScenePlotXlsxPath());
  } else {
    xlsx_sql_ = nullptr;
  }

  BindMenuActions();

  //  ui->tabWidget->hide();

  //  FillNpcTab();
  //  FillPlotTab();
}

MainWindow::~MainWindow() {
  delete ui;
  delete settings_data_;

  if (xlsx_sql_ != nullptr)
    delete xlsx_sql_;
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

  QString mission_path = settings_data_->GetMissionXlsxPath();
  if (0 == mission_path.length()) {
    warning + GlobalStrs::WARNING_NO_MISSION_FILE;
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

void MainWindow::FillPlotTab() {
  QSqlQuery query(xlsx_sql_->GetDataBase());

  query.prepare("SELECT * FROM 'Plot'");
  if (!query.exec()) {
    PrintMsg(query.lastError().text());
  }

  query.first();
  while (query.next()) {
    QTreeWidgetItem *item = new QTreeWidgetItem();

    item->setText(0, query.value(0).toString());
    item->setText(1, query.value(1).toString());
    item->setText(2, query.value(2).toString());
    item->setText(3, query.value(3).toString());
    item->setText(4, query.value(4).toString());

    ui->treePlot->insertTopLevelItem(ui->treePlot->topLevelItemCount(), item);
  }
}

void MainWindow::FillNpcTab() {
  for (int i = 1; i < 10; i++) {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, QString::number(i * 1));
    item->setText(1, QString::number(i * 2));
    item->setText(2, QString::number(i * 3));
    item->setText(3, QString::number(i * 4));

    ui->treeNpc->insertTopLevelItem(0, item);
  }
}

void MainWindow::ShowSettingWidget() {
  //  auto settings_ = new Settings(nullptr);

  //  settings_->setWindowModality(Qt::WindowModal);
  //  settings_->show();

  //  auto plotedit = new PlotEditDialog(nullptr);
  //  plotedit->setWindowModality(Qt::WindowModal);
  //  plotedit->show();

  auto plotviewer = new PlotViewer(this);
  plotviewer->setWindowModality(Qt::WindowModal);
  plotviewer->show();
}

void MainWindow::BindMenuActions() {
  connect(ui->actionShowSettings, &QAction::triggered, this, &MainWindow::ShowSettingWidget);
}
