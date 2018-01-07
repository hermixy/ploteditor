#ifndef PLOT_ROW_DATA_H
#define PLOT_ROW_DATA_H

#include <QMetaType>
#include <QString>

struct PlotRowData {
  PlotRowData();
  explicit PlotRowData(const QString&,
                       const QString&,
                       const QString&,
                       const QString&,
                       const QString&);

  PlotRowData(const PlotRowData&);
  PlotRowData& operator=(const PlotRowData&);

  QString sn;
  QString next_sn;
  QString npc_sn;
  QString content;
  QString voice;
};

Q_DECLARE_METATYPE(PlotRowData)

#endif  // PLOT_ROW_DATA_H
