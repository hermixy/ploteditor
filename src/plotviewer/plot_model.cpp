#include "plot_model.h"

PlotModel::PlotModel(QObject *parent)
  : QAbstractItemModel(parent)
{
}

QModelIndex PlotModel::index(int row, int column, const QModelIndex &parent) const
{
  // FIXME: Implement me!
}

QModelIndex PlotModel::parent(const QModelIndex &index) const
{
  // FIXME: Implement me!
}

int PlotModel::rowCount(const QModelIndex &parent) const
{
  if (!parent.isValid())
    return 0;

  // FIXME: Implement me!
}

int PlotModel::columnCount(const QModelIndex &parent) const
{
  if (!parent.isValid())
    return 0;

  // FIXME: Implement me!
}

QVariant PlotModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  // FIXME: Implement me!
  return QVariant();
}

bool PlotModel::insertRows(int row, int count, const QModelIndex &parent)
{
  beginInsertRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endInsertRows();
}

bool PlotModel::insertColumns(int column, int count, const QModelIndex &parent)
{
  beginInsertColumns(parent, column, column + count - 1);
  // FIXME: Implement me!
  endInsertColumns();
}

bool PlotModel::removeRows(int row, int count, const QModelIndex &parent)
{
  beginRemoveRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endRemoveRows();
}

bool PlotModel::removeColumns(int column, int count, const QModelIndex &parent)
{
  beginRemoveColumns(parent, column, column + count - 1);
  // FIXME: Implement me!
  endRemoveColumns();
}
