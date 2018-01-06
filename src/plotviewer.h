#ifndef PLOTVIEWER_H
#define PLOTVIEWER_H

#include "pch.h"

namespace Ui {
class PlotViewer;
}

class PlotViewer : public QDialog {
  Q_OBJECT

 public:
  explicit PlotViewer(QWidget *parent = 0);
  ~PlotViewer();

 public:
  void AddItem(PlotItem *);
  void RemoveItem(PlotItem *);
  void RemoveItem(int);

 private:
  QString GetPlotChain() {
    QString ret = "";
    if (plot_chain_.empty()) {
      return ret;
    }
  }

 private:
  QVector<PlotItem *> plot_items_;
  QVector<QListWidgetItem *> widget_items_;

  QVector<QString> plot_chain_;

 private:
  Ui::PlotViewer *ui;
};

#endif  // PLOTSEGMENTVIEWER_H
