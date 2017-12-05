#ifndef XLSX_SQL_H
#define XLSX_SQL_H

#include "pch.h"
#include "settings.h"

class XlsxSQL {
 public:
  //
  // @param QString Plot.xlsx path
  // @param QString Npc.xlsx path
  // @param QString Scene.xlsx path
  //
  XlsxSQL(const QString &, const QString &, const QString &);
  ~XlsxSQL();

 public:
  void CreatePlotTable();
  void CreateNpcTable();
  void CreateSceneTable();

 public:
  void ReloadPlotXlsx();
  void ReloadNpcXlsx();
  void ReloadSceneXlsx();

 private:
  //
  // @param libxl::Sheet
  // @param row
  // @param col
  //
  QString GetCell(libxl::Sheet *, unsigned, unsigned);

 private:
  QString filename_;

  libxl::Book *plot_book_;
  libxl::Book *npc_book_;
  libxl::Book *scene_book_;
};

#endif  // XLSX_SQL_H
