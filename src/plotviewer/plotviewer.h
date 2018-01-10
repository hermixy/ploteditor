#ifndef PLOTVIEWER_H
#define PLOTVIEWER_H

#include "plot_row_data.h"
#include "plotviewer/plot_viewer_model.h"
#include "plotviewer/ploteditdialog.h"

#include <QDialog>
#include <QEvent>
#include <QListWidgetItem>

namespace Ui {
class PlotViewer;
}

class PlotViewer : public QDialog {
  Q_OBJECT

 public:
  explicit PlotViewer(const QString &, QWidget *parent = 0);
  ~PlotViewer();

 private:
  void UpdatePlotChain();
  void UpdatePlot(const PlotRowData &);

 protected:
  bool eventFilter(QObject *, QEvent *);

 private slots:
  void OnItemDoubleClicked(const QModelIndex &);
  void OnItemSelected();

 private:
  QVector<QListWidgetItem *> widget_items_;

  QString plot_chain_;

  QVector<PlotRowData> plot_datas_;

 private:
  Ui::PlotViewer *ui;
  PlotEditDialog *edit_dialog_;
};

#endif  // PLOTVIEWER_H
