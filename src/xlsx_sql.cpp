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

  if (!ConnectDB()) {
    PrintMsg("ERROR: CREATE SQLITE DB FAILED.");
  }

  CreatePlotTable();
  CreateNpcTable();
  CreateSceneTable();
}

QSqlDatabase &XlsxSQL::GetDataBase() {
  return db_;
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
      QString sheet_table_name = split_names[1];
      CreateSubPlotTable(current_sheet_name, sheet_table_name);
    }
  }

  return true;
}

bool XlsxSQL::CreateSubPlotTable(const QString &current_sheet_name, const QString &table_name) {
  plot_doc_->selectSheet(current_sheet_name);

  if (!db_.tables().contains(table_name)) {
    QSqlQuery query;
    QString sql_statement = "CREATE TABLE IF NOT EXISTS " + table_name +
                            "("
                            "sn INTEGER PRIMARY KEY NOT NULL,"  // plotSn
                            "next INTEGER,"                     // order
                            "npcId INTEGER,"                    // npcSn
                            "content BLOB,"                     // content
                            "voiceChat TEXT)";                  // voiceChat mp3 filename

    if (!query.exec(sql_statement)) {
      PrintMsg("Create table " + table_name + " failed.");
      return false;
    }
  }

  QXlsx::Worksheet *sheet = plot_doc_->currentWorksheet();
  QXlsx::CellRange cell_range = plot_doc_->currentWorksheet()->dimension();

  int col = cell_range.lastColumn();
  int row = cell_range.lastRow();

  QSqlQuery query;

  for (int i = 5; i <= row; i++) {
    QString sn = GetCell(sheet, i, 1);
    QString next = GetCell(sheet, i, 2);
    QString npcId = GetCell(sheet, i, 3);
    QString content = GetCell(sheet, i, 4);
    QString voice = GetCell(sheet, i, 5);

    //    PrintMsg(sn + " " + next + " " + npcId + " " + content + " " + voice);

    QString sql_statement = "INSERT OR REPLACE INTO " + table_name + " VALUES " + "(\"" + sn +
                            "\",\"" + next + "\",\"" + npcId + "\",\"" + content + "\",\"" + voice +
                            "\");";

    if (!query.exec(sql_statement)) {
      PrintMsg("INSERT FALIED");
    }
  }

  return true;
}

bool XlsxSQL::CreateNpcTable() {
  npc_doc_->selectSheet(GlobalStrs::NpcSheetName);
  if (!db_.tables().contains(GlobalStrs::NpcTableName)) {
    QSqlQuery query;
    QString sql_statement = "CREATE TABLE IF NOT EXISTS " + GlobalStrs::NpcTableName +
                            "("
                            "sn INTEGER PRIMARY KEY,"
                            "name TEXT,"
                            "scene INTEGER)";

    if (!query.exec(sql_statement)) {
      PrintMsg("Create table " + GlobalStrs::NpcTableName + " failed");
      return false;
    }
  }

  QXlsx::Worksheet *sheet = npc_doc_->currentWorksheet();
  QXlsx::CellRange cell_range = npc_doc_->currentWorksheet()->dimension();

  QSqlQuery query;

  int row = cell_range.lastRow();

  for (int i = 5; i <= row; i++) {
    QString sn = GetCell(sheet, i, 1);
    QString name = GetCell(sheet, i, 2);
    QString scene = GetCell(sheet, i, 5);

    QString sql_stament = "INSERT OR REPLACE INTO " + GlobalStrs::NpcTableName + " VALUES " +
                          "(\"" + sn + "\",\"" + name + "\",\"" + scene + "\");";

    query.exec(sql_stament);
  }

  return true;
}

bool XlsxSQL::CreateSceneTable() {
  scene_doc_->selectSheet(GlobalStrs::SceneSheetName);
  if (!db_.tables().contains(GlobalStrs::SceneTableName)) {
    QSqlQuery query;
    QString sql_statement = "CREATE TABLE IF NOT EXISTS " + GlobalStrs::SceneTableName +
                            "("
                            "sn INTEGER PRIMARY KEY,"
                            "name TEXT)";

    if (!query.exec(sql_statement)) {
      PrintMsg("Create table " + GlobalStrs::SceneTableName + " failed");
      return false;
    }
  }

  QXlsx::Worksheet *sheet = scene_doc_->currentWorksheet();
  QXlsx::CellRange cell_range = scene_doc_->currentWorksheet()->dimension();

  QSqlQuery query;

  int row = cell_range.lastRow();

  for (int i = 5; i <= row; i++) {
    QString sn = GetCell(sheet, i, 1);
    QString name = GetCell(sheet, i, 2);

    QString sql_stament = "INSERT OR REPLACE INTO " + GlobalStrs::SceneTableName + " VALUES " +
                          "(\"" + sn + "\",\"" + name + "\");";

    query.exec(sql_stament);
  }

  return true;
}

bool XlsxSQL::CreateSceneNpcTable() {
  return false;
}

bool XlsxSQL::CreateMissionTable() {
  return false;
}

QString XlsxSQL::GetCell(QXlsx::Worksheet *sheet, unsigned row, unsigned col) {
  QString msg = "";

  QXlsx::Cell *cell = sheet->cellAt(row, col);

  if (nullptr == cell) {
    return msg;
  }

  QXlsx::Cell::CellType cellType = cell->cellType();

  switch (cellType) {
    case QXlsx::Cell::CellType::BooleanType:
      msg = cell->value().toString();
      break;
    case QXlsx::Cell::CellType::NumberType:
      msg = cell->value().toString();
      break;
    case QXlsx::Cell::CellType::ErrorType:
      break;
    case QXlsx::Cell::CellType::SharedStringType:
      msg = cell->value().toString();
      break;
    case QXlsx::Cell::CellType::StringType:
      msg = cell->value().toString();
      break;
    case QXlsx::Cell::CellType::InlineStringType:
      msg = cell->value().toString();
      break;
  }

  return msg;
}
