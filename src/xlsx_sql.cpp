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

  //  if (npc_book_->load(wnpc_path)) {
  //    PrintMsg("Load Npc Book.");
  //  }

  if (plot_book_->load(wplot_path)) {
    PrintMsg("Load Plot Book.");
  }

  //  if (scene_book_->load(wscene_path)) {
  //    PrintMsg("Load Scene Book.");
  //  }
}

XlsxSQL::~XlsxSQL() {
  if (nullptr != plot_book_)
    delete (plot_book_);

  if (nullptr != npc_book_)
    delete (npc_book_);

  if (nullptr != scene_book_)
    delete (scene_book_);
}

QString XlsxSQL::GetCell(libxl::Sheet *sheet, unsigned row, unsigned col) {
  QString msg = "";
  libxl::CellType cellType = sheet->cellType(row, col);

  switch (cellType) {
    case libxl::CELLTYPE_BLANK: {
      msg = "";
      break;
    }
    case libxl::CELLTYPE_STRING: {
      const wchar_t *p = sheet->readStr(row, col);
      msg = QString::fromWCharArray(p);
      break;
    }
    case libxl::CELLTYPE_BOOLEAN: {
      bool b = sheet->readBool(row, col);
      if (b)
        msg = "TRUE";
      else
        msg = "FALSE";
      break;
    }
    case libxl::CELLTYPE_NUMBER: {
      int d = sheet->readNum(row, col);
      msg = QString::number(d, 10);
      break;
    }
    case libxl::CELLTYPE_ERROR: {
      msg = "";
      break;
    }
  }

  return msg;
}
