#include "plot_viewer_model.h"

PlotViewerModel::PlotViewerModel(const QString &plot_sn, QObject *parent)
    : QAbstractListModel(parent) {
  //  XlsxSQL *xlsx_sql = XlsxSQL::Instance();

  //  if (xlsx_sql != nullptr) {
  //    xlsx_sql->AnalysePlots(plot_sn, plot_datas_);
  //    // PrintMsg(plot_sn + "\t" + QString::number(plot_datas_.size()));
  //  } else {
  //    PrintMsg("nullptr xlsx_sql");
  //  }
}

QVariant PlotViewerModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return tr("Sn");
      case 1:
        return tr("Next Sn");
      case 2:
        return tr("NpcSn");
      case 3:
        return tr("Content");
      case 4:
        return tr("Voice");
    }
  }

  return QVariant();
}

int PlotViewerModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;

  return plot_datas_.size();
}

QVariant PlotViewerModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (index.row() >= plot_datas_.size() || index.row() < 0)
    return QVariant();

  if (role == Qt::DisplayRole) {
    PlotRowData plot_data = plot_datas_.at(index.row());

    QVariant var;
    var.setValue(plot_data);
    return var;
  }

  return QVariant();
}

bool PlotViewerModel::insertRows(int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endInsertRows();

  return false;
}

bool PlotViewerModel::removeRows(int row, int count, const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endRemoveRows();

  return false;
}
