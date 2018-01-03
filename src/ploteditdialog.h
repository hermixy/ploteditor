#ifndef PLOTEDITDIALOG_H
#define PLOTEDITDIALOG_H

#include "pch.h"

namespace Ui {
class PlotEditDialog;
}

class PlotEditDialog : public QDialog {
  Q_OBJECT

 public:
  explicit PlotEditDialog(QWidget *parent = 0);
  ~PlotEditDialog();

 private slots:
  void Save();

 private:
  Ui::PlotEditDialog *ui;
};

#endif  // PLOTEDITDIALOG_H
