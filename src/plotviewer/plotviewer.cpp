#include "plotviewer.h"
#include "ui_plotviewer.h"

#include <QtDebug>
#include "xlsx_sql.h"

PlotViewer::PlotViewer(const QString &plot_sn, QWidget *parent)
    : QDialog(parent), ui(new Ui::PlotViewer) {
  ui->setupUi(this);

  edit_dialog_ = nullptr;

  setWindowTitle(tr("Plot Chain"));

  connect(ui->treeWidget,
          SIGNAL(doubleClicked(const QModelIndex &)),
          this,
          SLOT(OnItemDoubleClicked(const QModelIndex &)));

  connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected()));

  QStringList header_labels;
  header_labels.push_back(tr("Sn"));
  header_labels.push_back(tr("Order"));
  header_labels.push_back(tr("NpcSn"));
  header_labels.push_back(tr("Content"));
  header_labels.push_back(tr("Voice"));

  ui->treeWidget->setColumnCount(header_labels.count());
  ui->treeWidget->setHeaderLabels(header_labels);

  ui->treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
  ui->treeWidget->setDragEnabled(true);
  ui->treeWidget->installEventFilter(this);
  ui->treeWidget->viewport()->setAcceptDrops(true);
  ui->treeWidget->setDropIndicatorShown(false);
  ui->treeWidget->setSortingEnabled(false);
  ui->treeWidget->setColumnWidth(3, 500);
  //  ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  if (nullptr != XlsxSQL::Instance()) {
    XlsxSQL::Instance()->AnalysePlots(plot_sn, plot_datas_);
    XlsxSQL::Instance()->RearrangePlots(plot_datas_);
  }

  for (PlotRowData &plot_data : plot_datas_) {
    auto list_item = new QTreeWidgetItem();
    list_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled);

    list_item->setText(0, plot_data.sn);
    list_item->setText(1, plot_data.next_sn);
    list_item->setText(2, plot_data.npc_sn);
    list_item->setText(3, plot_data.content);
    list_item->setText(4, plot_data.voice);

    ui->treeWidget->addTopLevelItem(list_item);
  }

  if (ui->treeWidget->topLevelItemCount() > 0) {
    ui->treeWidget->topLevelItem(0)->setSelected(true);
  }
}

PlotViewer::~PlotViewer() {
  delete ui;
}

void PlotViewer::UpdatePlotChain() {
  plot_chain_.clear();

  for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
    QTreeWidgetItem *ptr_widget_item = ui->treeWidget->topLevelItem(i);

    QString str_node;
    if (i < ui->treeWidget->topLevelItemCount() - 1) {
      str_node = QString("%1 -> ").arg(ptr_widget_item->text(0));

      QTreeWidgetItem *ptr_next_widget_item = ui->treeWidget->topLevelItem(i + 1);
      ptr_widget_item->setText(1, ptr_next_widget_item->text(0));

    } else {
      str_node = ptr_widget_item->text(0);
      ptr_widget_item->setText(1, "");
    }

    plot_chain_.append(str_node);
  }
}

bool PlotViewer::eventFilter(QObject *obj, QEvent *event) {
  UpdatePlotChain();
  ui->textChain->setText(plot_chain_);

  return QObject::eventFilter(obj, event);
}

void PlotViewer::OnItemDoubleClicked(const QModelIndex &idx) {
  int row = idx.row();
  const QModelIndex first_index = ui->treeWidget->model()->index(row, 0);

  if (first_index.isValid()) {
    QString plot_sn = first_index.data(Qt::DisplayRole).toString();

    edit_dialog_ = new PlotEditDialog(plot_sn, this);
    edit_dialog_->setAttribute(Qt::WA_DeleteOnClose);
    edit_dialog_->setWindowModality(Qt::WindowModal);
    edit_dialog_->show();
  }
}

void PlotViewer::OnItemSelected() {
  QList<QTreeWidgetItem *> selections = ui->treeWidget->selectedItems();
  for (int i = 0; i < selections.size(); i++) {
    const QString npc_sn = selections[i]->text(2);

    QString scene_sn, scene_name, npc_name;
    if (npc_sn == "" || npc_sn == "0") {
      ui->labelInfo->setText(tr("玩家"));
    } else {
      XlsxSQL::Instance()->GetSceneOfNpc(npc_sn, npc_name, scene_sn, scene_name);
      ui->labelInfo->setText(QString("%1, [%2 - %3]").arg(npc_name, scene_sn, scene_name));
    }
  }
}
