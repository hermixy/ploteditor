#ifndef XLSX_SQL_H
#define XLSX_SQL_H

#include "pch.h"
#include "settings.h"

class XlsxSQL {
 public:
  XlsxSQL(const QString &, const QString &, const QString &);
  ~XlsxSQL();

 public:
  bool CreateDB();

  bool CreatePlotTable();
  bool CreateNpcTable();
  bool CreateSceneTable();

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

 private:
  QString filename_;

  QXlsx::Document *plot_doc_;
  QXlsx::Document *npc_doc_;
  QXlsx::Document *scene_doc_;

  QSqlDatabase db_;
};

#endif  // XLSX_SQL_H
