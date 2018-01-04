#include "plotsegmentviewer.h"
#include "ui_plotsegmentviewer.h"

PlotSegmentViewer::PlotSegmentViewer(QWidget *parent)
    : QDialog(parent), ui(new Ui::PlotSegmentViewer) {
  ui->setupUi(this);

  auto item = new PlotItem(this);

  auto listItem = new QListWidgetItem();
  listItem->setSizeHint(QSize(0, 50));

  ui->listWidget->addItem(listItem);
  ui->listWidget->setItemWidget(listItem, item);
}

PlotSegmentViewer::~PlotSegmentViewer() {
  delete ui;
}
