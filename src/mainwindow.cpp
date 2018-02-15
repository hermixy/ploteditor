#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowTitle(tr("Plot Editor Window"));

  settings_data_ = new SettingsData();

  if (CheckAllConfigFiles()) {
    xlsx_sql_ = new XlsxSQL(settings_data_->GetPlotXlsxPath(),
                            settings_data_->GetNpcXlsxPath(),
                            settings_data_->GetSceneXlsxPath(),
                            settings_data_->GetMissionXlsxPath());
  } else {
    xlsx_sql_ = nullptr;
  }

  mission_model_ = new QSqlTableModel();
  plot_model_ = new QSqlTableModel();

  BindMenuActions();

  SetMissionTab();
  SetPlotTab();
}

MainWindow::~MainWindow() {
  delete ui;
  delete settings_data_;

  if (plot_model_ != nullptr) {
    delete plot_model_;
  }

  if (xlsx_sql_ != nullptr) {
    //    xlsx_sql_->DropPlotTable();
    delete xlsx_sql_;
  }
}

void MainWindow::OnBtnSearchMissionClicked() {
  this->SetSearchMissionTab(ui->missionSearchbox->text());
}

void MainWindow::OnBtnSearchPlotClicked() {
  this->SetSearchPlotTab(ui->plotSearchbox->text());
}

bool MainWindow::CheckAllConfigFiles() {
  QString warning("");

  QString npc_path = settings_data_->GetNpcXlsxPath();
  if (0 == npc_path.length()) {
    warning += GlobalStrs::WARNING_NO_NPC_FILE;
  }

  QString scene_path = settings_data_->GetSceneXlsxPath();
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

void MainWindow::SetPlotTab() {
  this->SetSearchPlotTab(QString());
}

void MainWindow::SetMissionTab() {
  // set combo box and search box
  QStringList search_conditions;
  search_conditions.push_back(tr("任务Sn"));
  search_conditions.push_back(tr("任务链"));

  ui->searchCond->addItems(search_conditions);

  this->SetSearchMissionTab(QString());
}

void MainWindow::SetSearchPlotTab(const QString &cond) {
  plot_model_->setTable("Plot");
  plot_model_->setEditStrategy(QSqlTableModel::OnFieldChange);
  plot_model_->setSort(5, Qt::AscendingOrder);

  if (!(cond.isNull() || cond.isEmpty())) {
    plot_model_->setFilter(QString("sn LIKE '%%1%'").arg(cond));
  }

  plot_model_->select();

  ui->plotView->setModel(plot_model_);
  ui->plotView->resizeRowsToContents();
  ui->plotView->setColumnWidth(3, 500);
  ui->plotView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->plotView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::SetSearchMissionTab(const QString &cond) {
  // set table
  mission_model_->setTable("Mission");
  mission_model_->setEditStrategy(QSqlTableModel::OnFieldChange);
  mission_model_->setSort(5, Qt::AscendingOrder);

  if (!(cond.isNull() || cond.isEmpty())) {
    if (ui->searchCond->currentIndex() == 0) {
      mission_model_->setFilter(QString("sn LIKE '%%1%'").arg(cond));
    } else if (ui->searchCond->currentIndex() == 1) {
      mission_model_->setFilter(QString("line = '%1'").arg(cond));
    }
  }

  mission_model_->select();

  ui->missionView->setModel(mission_model_);
  ui->missionView->hideColumn(10);
  ui->missionView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->missionView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->missionView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::ShowSettingWidget() {
  auto settings_ = new Settings(this);
  settings_->setAttribute(Qt::WA_DeleteOnClose);
  settings_->setWindowModality(Qt::WindowModal);
  settings_->show();
}

void MainWindow::BindMenuActions() {
  connect(ui->actionShowSettings, &QAction::triggered, this, &MainWindow::ShowSettingWidget);
  connect(ui->plotView,
          SIGNAL(doubleClicked(const QModelIndex &)),
          this,
          SLOT(OnPlotRowDoubleClicked(const QModelIndex &)));

  connect(ui->btnSearchMission, SIGNAL(released()), this, SLOT(OnBtnSearchMissionClicked()));
  connect(ui->btnSearchPlot, SIGNAL(released()), this, SLOT(OnBtnSearchPlotClicked()));
}

void MainWindow::OnPlotRowDoubleClicked(const QModelIndex &idx) {
  int row = idx.row();
  const QModelIndex first_index = plot_model_->index(row, 0);
  if (first_index.isValid()) {
    QString plot_sn = first_index.data(Qt::DisplayRole).toString();

    PlotViewer *plotviewer = new PlotViewer(plot_sn, this);
    plotviewer->setAttribute(Qt::WA_DeleteOnClose);
    plotviewer->setWindowModality(Qt::WindowModal);
    plotviewer->show();
  }
}
