#ifndef PLOTEDITDIALOG_H
#define PLOTEDITDIALOG_H

#include <QCompleter>
#include <QDialog>
#include <QStringList>
#include <QWidget>

#include "ui_ploteditdialog.h"

namespace Ui {
class PlotEditDialog;
}

class PlotEditDialog : public QDialog {
  Q_OBJECT

 public:
  explicit PlotEditDialog(const QString &, QWidget *parent = 0);
  ~PlotEditDialog();

 private slots:
  void Save();
  void Close();

 private:
  void InitScenes();
  void InitNpcs(const QString &);

  QStringList scenes_;
  QStringList npcs_;

  //  QCompleter *scenes_completer_;
  //  QCompleter *npcs_completer_;

  QString plot_sn_;

 private:
  Ui::PlotEditDialog *ui;
};

#endif  // PLOTEDITDIALOG_H
