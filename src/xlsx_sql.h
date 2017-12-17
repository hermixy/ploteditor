#ifndef XLSX_SQL_H
#define XLSX_SQL_H

#include "pch.h"
#include "settings.h"

class XlsxSQL {
 public:
  XlsxSQL(const QString &, const QString &, const QString &);
  ~XlsxSQL();

 public:
  bool ConnectDB();

  bool CreatePlotTable();

  /*
   * @param current selected sheet name
   * @param current sheet name
   * */
  bool CreateSubPlotTable(const QString &, const QString &);

  bool CreateNpcTable();
  bool CreateSceneTable();

  bool CreateSceneNpcTable();

 public:
  void ReloadPlotXlsx();
  void ReloadNpcXlsx();
  void ReloadSceneXlsx();

 private:
  //
  // @param QXlsx::Worksheet *
  // @param row
  // @param col
  //
  QString GetCell(QXlsx::Worksheet *, unsigned, unsigned);

  bool TryGetString(QXlsx::Worksheet *, unsigned, unsigned, QString &);
  bool TryGetUInt(QXlsx::Worksheet *, unsigned, unsigned, unsigned &);

 private:
  QString filename_;

  QXlsx::Document *plot_doc_;
  QXlsx::Document *npc_doc_;
  QXlsx::Document *scene_doc_;

  QSqlDatabase db_;
};

#endif  // XLSX_SQL_H
