#include "PlotViewer.h"
#include "ui_plotviewer.h"

#include "plotviewer/plot_viewer_item.h"

PlotViewer::PlotViewer(QWidget *parent) : QDialog(parent), ui(new Ui::PlotViewer) {
  ui->setupUi(this);

  setWindowTitle(tr("Plot Chain"));

  ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
  ui->listWidget->setDragEnabled(true);
  ui->listWidget->installEventFilter(this);
  ui->listWidget->viewport()->setAcceptDrops(true);
  ui->listWidget->setDropIndicatorShown(true);
  ui->listWidget->setSortingEnabled(false);

  for (int i = 0; i < 10; i++) {
    QString strA = QString("A%1").arg(i);
    QString strB = QString("B%1").arg(i);
    QString strC = QString("C%1").arg(i);
    QString strD = QString("D%1").arg(i);
    QString strE = QString("E%1").arg(i);

    auto viewer_item = new PlotViewerItem(nullptr, strA, strB, strC, strD, strE);
    auto list_item = new QListWidgetItem();
    list_item->setSizeHint(QSize(0, 50));

    ui->listWidget->addItem(list_item);
    ui->listWidget->setItemWidget(list_item, viewer_item);
  }
}

PlotViewer::~PlotViewer() {
  delete ui;
}

void PlotViewer::AddItem(PlotItem *item) {
  QListWidgetItem *listWidgetItem = new QListWidgetItem();
}

QString PlotViewer::UpdatePlotChain() {
  plot_chain_.clear();

  for (int i = 0; i < ui->listWidget->count(); i++) {
    QListWidgetItem *ptr_widget_item = ui->listWidget->item(i);
    PlotViewerItem *ptr_plot_item =
        static_cast<PlotViewerItem *>(ui->listWidget->itemWidget(ptr_widget_item));

    QString str_node;
    if (i < ui->listWidget->count() - 1) {
      str_node = QString("%1 -> ").arg(ptr_plot_item->GetSn());

      QListWidgetItem *ptr_next_widget_item = ui->listWidget->item(i + 1);
      PlotViewerItem *ptr_next_plot_item =
          static_cast<PlotViewerItem *>(ui->listWidget->itemWidget(ptr_next_widget_item));

      ptr_plot_item->SetNextSn(ptr_next_plot_item->GetSn());

    } else {
      str_node = ptr_plot_item->GetSn();

      ptr_plot_item->SetNextSn("");
    }

    plot_chain_.append(str_node);
  }

  return plot_chain_;
}

bool PlotViewer::eventFilter(QObject *obj, QEvent *event) {
  plot_chain_ = UpdatePlotChain();
  ui->labelChain->setText(plot_chain_);

  return QObject::eventFilter(obj, event);
}
