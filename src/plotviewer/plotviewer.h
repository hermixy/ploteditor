#ifndef PLOTVIEWER_H
#define PLOTVIEWER_H

#include "plotviewer/plotitem.h"

#include <QDialog>
#include <QEvent>
#include <QListWidgetItem>

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
  QString UpdatePlotChain();

 protected:
  bool eventFilter(QObject *, QEvent *);

 private:
  QVector<PlotItem *> plot_items_;
  QVector<QListWidgetItem *> widget_items_;

  QString plot_chain_;

 private:
  Ui::PlotViewer *ui;
};

#endif  // PLOTVIEWER_H
