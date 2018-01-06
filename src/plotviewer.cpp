#include "PlotViewer.h"
#include "ui_plotviewer.h"

#include "plot_viewer_item.h"

PlotViewer::PlotViewer(QWidget *parent) : QDialog(parent), ui(new Ui::PlotViewer) {
  ui->setupUi(this);

  setWindowTitle(tr("对话链"));

  ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
  ui->listWidget->setDragEnabled(true);
  ui->listWidget->viewport()->setAcceptDrops(true);
  ui->listWidget->setDropIndicatorShown(true);

  for (int i = 0; i < 10; i++) {
    QString strA = QString("A%1").arg(i);
    QString strB = QString("B%1").arg(i);
    QString strC = QString("C%1").arg(i);
    QString strD = QString("D%1").arg(i);

    auto viewer_item = new PlotViewerItem(nullptr, strA, strB, strC, strD);
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
