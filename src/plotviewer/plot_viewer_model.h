#ifndef PLOTVIEWERMODEL_H
#define PLOTVIEWERMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "plot_row_data.h"

class PlotViewerModel : public QAbstractListModel {
  Q_OBJECT

 public:
  explicit PlotViewerModel(const QString &, QObject *parent = nullptr);

  // Header:
  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  // Add data:
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

  // Remove data:
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

 private:
  QList<PlotRowData> plot_datas_;
};

#endif  // PLOTVIEWERMODEL_H
