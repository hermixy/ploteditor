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
  QVector<PlotItem *> plot_items_;
  QVector<QListWidgetItem *> widget_items_;

 private:
  Ui::PlotViewer *ui;
};

#endif  // PLOTSEGMENTVIEWER_H
