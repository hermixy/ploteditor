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
  CreateNpcTable();
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
    QString sql_statement = "CREATE TABLE IF NOT EXISTS " + table_name +
                            "("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"  // key
                            "sn INTEGER UNIQUE NOT NULL,"            // plotSn
                            "next INTEGER,"                          // order
                            "npcId INTEGER,"                         // npcSn
                            "content BLOB,"                          // content
                            "voiceChat TEXT,"                        // voiceChat mp3 filename
                            "remark BLOB)";                          // editor remark

    if (!query.exec(sql_statement)) {
      PrintMsg("Create table " + table_name + " failed.");
      return false;
    }
  }

  QXlsx::CellRange cell_range = plot_doc_->currentWorksheet()->dimension();

  int col = cell_range.lastColumn();
  int row = cell_range.lastRow();

  for (int i = 1; i <= col; i++) {
    for (int j = 1; j <= row; j++) {
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

    if (i == 5)
      PrintMsg(sn + "\n" + name + "\n" + scene + "\n" + sql_stament);

    query.exec(sql_stament);
  }

  return true;
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
  return cell->value().toString();
}

bool XlsxSQL::TryGetString(QXlsx::Worksheet *sheet, unsigned row, unsigned col, QString &ret) {
  QXlsx::Cell *cell = sheet->cellAt(row, col);

  QXlsx::Cell::CellType cellType = cell->cellType();
  if (cellType == QXlsx::Cell::SharedStringType || cellType == QXlsx::Cell::StringType ||
      QXlsx::Cell::InlineStringType) {
    ret = cell->value().toString();
    return true;
  }

  return false;
}

bool XlsxSQL::TryGetUInt(QXlsx::Worksheet *sheet, unsigned row, unsigned col, unsigned &ret) {
  QXlsx::Cell *cell = sheet->cellAt(row, col);

  QXlsx::Cell::CellType cellType = cell->cellType();
  if (cellType == QXlsx::Cell::NumberType) {
    ret = cell->value().toUInt();
    return true;
  }

  return false;
}
