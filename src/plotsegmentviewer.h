#ifndef PLOTSEGMENTVIEWER_H
#define PLOTSEGMENTVIEWER_H

#include "pch.h"

namespace Ui {
class PlotSegmentViewer;
}

class PlotSegmentViewer : public QDialog {
  Q_OBJECT

 public:
  explicit PlotSegmentViewer(QWidget *parent = 0);
  ~PlotSegmentViewer();

 private:
  QVector<PlotItem *> plot_items_;
  QVector<QListWidgetItem *> widget_items_;

 private:
  Ui::PlotSegmentViewer *ui;
};

#endif  // PLOTSEGMENTVIEWER_H
