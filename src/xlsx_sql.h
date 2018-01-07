#ifndef XLSX_SQL_H
#define XLSX_SQL_H

#include <xlsxdocument.h>

#include <QSqlDatabase>
#include <QString>

#include "plot_row_data.h"

class XlsxSQL {
 public:
  explicit XlsxSQL(const QString &, const QString &, const QString &);
  ~XlsxSQL();

 public:
  static XlsxSQL *Instance();

 public:
  bool ConnectDB();

  QSqlDatabase &GetDataBase();

 public:
  bool CreatePlotTable();

  /*
   * @param current selected sheet name
   * @param current sheet name
   * */
  bool CreateSubPlotTable(const QString &, const QString &);
  bool CreateNpcTable();
  bool CreateSceneTable();

  /*
   * Create table for combining scene and npc
   * */
  bool CreateSceneNpcTable();

  bool CreateMissionTable();

 public:
  void ReloadPlotXlsx();
  void ReloadNpcXlsx();
  void ReloadSceneXlsx();

 public:
  /*
   * @param plot table name
   * @param [out] result
   * @descriptin Analysint the plot data, store the plot chain
   * */
  void AnalysePlots(const QString &, QList<PlotRowData> &);

 private:
  //
  // @param QXlsx::Worksheet *
  // @param row
  // @param col
  //
  QString GetCell(QXlsx::Worksheet *, unsigned, unsigned);

 private:
  QString filename_;

  QXlsx::Document *plot_doc_;
  QXlsx::Document *npc_doc_;
  QXlsx::Document *scene_doc_;

  QSqlDatabase db_;

 private:
  static XlsxSQL *instance_;
};

#endif  // XLSX_SQL_H
