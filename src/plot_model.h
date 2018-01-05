#ifndef PLOTMODEL_H
#define PLOTMODEL_H

#include <QAbstractItemModel>

class PlotModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  explicit PlotModel(QObject *parent = nullptr);

  // Basic functionality:
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  // Add data:
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

  // Remove data:
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
};

#endif // PLOTMODEL_H