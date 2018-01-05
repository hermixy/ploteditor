#include "plotitem.h"

PlotItem::PlotItem(QWidget *parent) : QWidget(parent) {
  label1 = new QLabel();
  label2 = new QLabel();

  hbl = new QHBoxLayout(this);

  label1->setText("Sn");
  label2->setText("Next Sn");

  hbl->addWidget(label1);
  hbl->addWidget(label2);
}

PlotItem::~PlotItem() {
  if (nullptr != labelSn) {
    delete labelSn;
  }

  if (nullptr != labelNextSn) {
    delete labelNextSn;
  }

  if (nullptr != labelContent) {
    delete labelContent;
  }

  if (nullptr != labelVoice) {
    delete hbl;
  }
}
