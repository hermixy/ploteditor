#ifndef PLOTITEM_H
#define PLOTITEM_H

#include <QHBoxLayout>
#include <QLabel>

// TODO -> model item.
class PlotItem {
 public:
  explicit PlotItem();
  ~PlotItem();
 signals:

 public slots:

 public:
  void SetData(const QString &, const QString &, const QString &, const QString &);

 private:
  QString sn_;
  QString next_sn_;
  QString content_;
  QString voice_;

 private:
};

#endif  // PLOTITEM_H
