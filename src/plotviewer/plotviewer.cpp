#include "plotviewer.h"
#include "ui_plotviewer.h"

#include "pch.h"

PlotViewer::PlotViewer(const QString &plot_sn, QWidget *parent)
    : QDialog(parent), ui(new Ui::PlotViewer) {
  ui->setupUi(this);

  setWindowTitle(tr("Plot Chain"));

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
  ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  XlsxSQL *xlsx_sql = XlsxSQL::Instance();

  if (nullptr != xlsx_sql) {
    xlsx_sql->AnalysePlots(plot_sn, plot_datas_);
    xlsx_sql->RearrangePlots(plot_datas_);
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
  ui->labelChain->setText(plot_chain_);

  return QObject::eventFilter(obj, event);
  //  }
}
