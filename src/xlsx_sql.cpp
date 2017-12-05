#include "xlsx_sql.h"

XlsxSQL::XlsxSQL(const QString &plot_path, const QString &npc_path, const QString &scene_path) {
  npc_book_ = xlCreateBook();
  plot_book_ = xlCreateBook();
  scene_book_ = xlCreateBook();

  wchar_t wnpc_path[256];
  wchar_t wplot_path[256];
  wchar_t wscene_path[256];

  npc_path.toWCharArray(wnpc_path);
  plot_path.toWCharArray(wplot_path);
  scene_path.toWCharArray(wscene_path);

  if (npc_book_->load(wnpc_path)) {
    PrintMsg("Load Npc Book.");
  }

  if (plot_book_->load(wplot_path)) {
    PrintMsg("Load Plot Book.");
  }

  if (scene_book_->load(wscene_path)) {
    PrintMsg("Load Scene Book.");
  }
}

XlsxSQL::~XlsxSQL() {
  if (nullptr != book_)
    delete (book_);

  if (nullptr != npc_sheet_)
    delete (npc_sheet_);

  if (nullptr != plot_sheet_)
    delete (plot_sheet_);

  if (nullptr != scene_sheet_)
    delete (scene_sheet_);
}

XlsxSQL::GetCell(libxl::Sheet *sheet, unsigned row, unsigned col) {
  QString msg = "";
  libxl::CellType cellType = sheet->cellType(row, col);

  switch (cellType) {
    case libxl::CELLTYPE_BLANK: {
      msg = "";
      break;
    }
    case libxl::CELLTYPE_STRING: {
      const char *p = sheet->readStr(row, col);
      msg = QString(QLatin1String(p)).toLatin1();
      break;
    }
    case libxl::CELLTYPE_BOOLEAN: {
      bool b = sheet1->readBool(row, col);
      if (b)
        msg = "TRUE";
      else
        msg = "FALSE";
      break;
    }
    case libxl::CELLTYPE_NUMBER: {
      int d = sheet1->readNum(row, col);
      msg = QString::number(d, 10);
      break;
    }
    case libxl::CELLTYPE_BLANK: {
      msg = "";
      break;
    }
    case libxl::CELLTYPE_ERROR: {
      msg = "";
      break;
    }
  }

  return msg;
}
