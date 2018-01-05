#include "PlotViewer.h"
#include "ui_plotviewer.h"

PlotViewer::PlotViewer(QWidget *parent) : QDialog(parent), ui(new Ui::PlotViewer) {
  ui->setupUi(this);

  //  auto item = new PlotItem(this);

  //  auto listItem = new QListWidgetItem();
  //  listItem->setSizeHint(QSize(0, 50));

  //  item->SetData("a", "b", "c", "d");

  //  ui->listWidget->addItem(listItem);
  //  ui->listWidget->setItemWidget(listItem, item);

  //  ui->listView->
}

PlotViewer::~PlotViewer() {
  delete ui;
}

void PlotViewer::AddItem(PlotItem *item) {
  QListWidgetItem *listWidgetItem = new QListWidgetItem();
}
