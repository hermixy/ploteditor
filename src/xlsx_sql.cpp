#include "xlsx_sql.h"

/*
 * @param plot path
 * @param npc path
 * @param scene path
 * */
XlsxSQL::XlsxSQL(const QString &plot_path, const QString &npc_path, const QString &scene_path) {
  npc_doc_ = new QXlsx::Document(npc_path);
  scene_doc_ = new QXlsx::Document(scene_path);
  plot_doc_ = new QXlsx::Document(plot_path);

  //  QStringList name_list = npc_doc_->sheetNames();
  //  PrintMsg(name_list.join(','));

  //  auto str = GetCell(npc_doc_->currentWorksheet(), 23, 11);
  //  PrintMsg(str);

  //  auto cell_range = npc_doc_->dimension();

  //  PrintMsg(QString::number(cell_range.lastColumn()) + ", " +
  //  QString::number(cell_range.lastRow()));

  if (!ConnectDB()) {
    PrintMsg("ERROR: CREATE SQLITE DB FAILED.");
  }

  CreatePlotTable();
}

XlsxSQL::~XlsxSQL() {
  if (nullptr != plot_doc_)
    delete (plot_doc_);

  if (nullptr != npc_doc_)
    delete (npc_doc_);

  if (nullptr != scene_doc_)
    delete (scene_doc_);
}

bool XlsxSQL::ConnectDB() {
  db_ = QSqlDatabase::addDatabase("QSQLITE");
  db_.setDatabaseName(GetDBFilePath());

  if (!db_.open()) {
    return false;
  } else {
    return true;
  }
}

bool XlsxSQL::CreatePlotTable() {
  QStringList sheet_names = plot_doc_->sheetNames();

  for (int i = 0; i < sheet_names.size(); i++) {
    QString current_sheet_name = sheet_names[i];

    // split sheet name
    QStringList split_names = current_sheet_name.split("|");
    if (split_names.size() != 2) {
      continue;
    } else {
      QString sheet_table_name = split_names[1] + "_plot";
      CreateSubPlotTable(current_sheet_name, sheet_table_name);
    }
  }

  return true;
}

bool XlsxSQL::CreateSubPlotTable(const QString &current_sheet_name, const QString &table_name) {
  plot_doc_->selectSheet(current_sheet_name);

  if (!db_.tables().contains(table_name)) {
    QSqlQuery query;
    QString sql_statement = "CREATE TABLE " + table_name +
                            "("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "sn INTEGER,"
                            "scene INTEGER,"
                            "name BLOB)";

    if (!query.exec(sql_statement)) {
      PrintMsg("Create table " + table_name + " failed.");
      return false;
    }
  }

  return true;
}

bool XlsxSQL::CreateNpcTable() {
  return false;
}

bool XlsxSQL::CreateSceneTable() {
  return false;
}

bool XlsxSQL::CreateSceneNpcTable() {
  return false;
}

QString XlsxSQL::GetCell(QXlsx::Worksheet *sheet, unsigned row, unsigned col) {
  QString msg = "";

  QXlsx::Cell *cell = sheet->cellAt(row, col);
  switch (cell->cellType()) {
    case QXlsx::Cell::BooleanType: {
      msg = "Boolean " + cell->value().toString();
      break;
    }
    case QXlsx::Cell::NumberType: {
      msg = "Number " + cell->value().toString();
      break;
    }
    case QXlsx::Cell::ErrorType: {
      msg = "Error " + cell->value().toString();
      break;
    }
    case QXlsx::Cell::SharedStringType:
    case QXlsx::Cell::StringType:
    case QXlsx::Cell::InlineStringType: {
      msg = "String " + cell->value().toString();
      break;
    }
  }

  return msg;
}
