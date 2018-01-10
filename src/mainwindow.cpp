#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowTitle(tr("Plot Editor Window"));

  settings_data_ = new SettingsData();

  if (CheckAllConfigFiles()) {
    xlsx_sql_ = new XlsxSQL(settings_data_->GetPlotXlsxPath(),
                            settings_data_->GetNpcXlsxPath(),
                            settings_data_->GetScenePlotXlsxPath());
  } else {
    xlsx_sql_ = nullptr;
  }

  BindMenuActions();

  //  ui->tabWidget->hide();

  //  FillNpcTab();
  FillPlotTab();
}

MainWindow::~MainWindow() {
  delete ui;
  delete settings_data_;

  if (xlsx_sql_ != nullptr)
    delete xlsx_sql_;

  if (plot_model_ != nullptr)
    delete plot_model_;
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
  plot_model_ = new QSqlTableModel();
  plot_model_->setTable("Plot");
  plot_model_->setEditStrategy(QSqlTableModel::OnFieldChange);
  plot_model_->setSort(5, Qt::AscendingOrder);

  plot_model_->select();

  ui->tableView->setModel(plot_model_);
  ui->tableView->resizeRowsToContents();
  ui->tableView->setColumnWidth(3, 500);
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::FillNpcTab() {}

void MainWindow::ShowSettingWidget() {
  //  auto settings_ = new Settings(nullptr);

  //  settings_->setWindowModality(Qt::WindowModal);
  //  settings_->show();

  //  auto plotedit = new PlotEditDialog(nullptr);
  //  plotedit->setWindowModality(Qt::WindowModal);
  //  plotedit->show();

  //  auto plotviewer = new PlotViewer(this);
  //  plotviewer->setWindowModality(Qt::WindowModal);
  //  plotviewer->show();
}

void MainWindow::BindMenuActions() {
  connect(ui->actionShowSettings, &QAction::triggered, this, &MainWindow::ShowSettingWidget);
  connect(ui->tableView,
          SIGNAL(doubleClicked(const QModelIndex &)),
          this,
          SLOT(OnPlotRowDoubleClicked(const QModelIndex &)));
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
