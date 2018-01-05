#include "xlsx_sql.h"

#include "progressbar.h"

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
                            "(sn TEXT PRIMARY KEY NOT NULL,"  // plotSn
                            "next TEXT,"                      // order
                            "npcId INTEGER,"                  // npcSn
                            "content BLOB,"                   // content
                            "voiceChat TEXT,"                 // voiceChat mp3 filename
                            "row INTEGER)";                   // row number

    QString error_tips = "Create table " + table_name + " failed.";

    if (!ExecuteSQLQuery(query, sql_statement, error_tips)) {
      return false;
    }
  }

  QXlsx::Worksheet *sheet = plot_doc_->currentWorksheet();
  QXlsx::CellRange cell_range = plot_doc_->currentWorksheet()->dimension();

  int row = cell_range.lastRow();

  // init ui progressbar
  QString title = GlobalStrs::CheckProgressHead + current_sheet_name;
  QString progname = table_name;
  ProgressBar *pb = CreateNewProgressBar(title, progname, 0, row, 5);
  pb->show();

  QSqlQuery query;
  QString error_tips;
  for (int i = 5; i <= row; i++) {
    QString sn = GetCell(sheet, i, 1);
    QString order = GetCell(sheet, i, 2);
    QString npcsn = GetCell(sheet, i, 3);
    QString content = GetCell(sheet, i, 4);
    QString voice = GetCell(sheet, i, 5);

    bool hasChanged = false;

    // check is data changed.
    QString sql = QString("SELECT * FROM %1 WHERE sn = :sn").arg(table_name);
    query.prepare(sql);
    query.bindValue(":sn", sn);
    if (query.exec()) {
      if (query.next()) {
        if (sn != query.value(0).toString() || order != query.value(1).toString() ||
            npcsn != query.value(2).toString() || content != query.value(3).toString() ||
            voice != query.value(4).toString()) {
          hasChanged = true;
        }
      }
    }

    if (hasChanged) {
      QString sql_statement = "INSERT OR REPLACE INTO " + table_name + " VALUES (?, ?, ?, ?, ?, ?)";
      query.prepare(sql_statement);
      query.addBindValue(GetCell(sheet, i, 1));  // sn
      query.addBindValue(GetCell(sheet, i, 2));  // order(next)
      query.addBindValue(GetCell(sheet, i, 3));  // npc sn
      query.addBindValue(GetCell(sheet, i, 4));  // content
      query.addBindValue(GetCell(sheet, i, 5));  // voice
      query.addBindValue(QString::number(i));

      error_tips = GlobalStrs::InsertFailed + sql_statement;
      if (!query.exec()) {
        PrintMsg(error_tips);

        pb->close();
        delete pb;

        return false;
      }
    }

    pb->SetValue(i);
  }

  pb->close();
  delete pb;

  return true;
}

bool XlsxSQL::AnalysePlots(const QString &table_name) {
  if (!db_.tables().contains(table_name)) {
    PrintMsg("Table " + table_name + " not exists.");
    return false;
  }

  QString plotchain_table_name = table_name + "Chain";
  if (!db_.tables().contains(plotchain_table_name)) {
    QSqlQuery query;
    QString sql_statement = "CREATE TABLE IF NOT EXISTS " + plotchain_table_name +
                            "(sn TEXT PRIMARY KEY," + "chain TEXT)";

    QString error_tips = "Create table " + plotchain_table_name + " failed.";

    if (!ExecuteSQLQuery(query, sql_statement, error_tips)) {
      return false;
    }
  }

  // analysing plot database
  //  std::map<QString> not_head_map;
  // TODO: analysing plot datbase.

  QSqlQuery query;
  QString sql_statement = "SELECT * FROM Plot";
  query.prepare(sql_statement);

  query.first();
  while (query.next()) {
  }

  return false;
}

bool XlsxSQL::CreateNpcTable() {
  npc_doc_->selectSheet(GlobalStrs::NpcSheetName);
  if (!db_.tables().contains(GlobalStrs::NpcTableName)) {
    QSqlQuery query;
    QString sql_statement = "CREATE TABLE IF NOT EXISTS " + GlobalStrs::NpcTableName +
                            "(sn INTEGER PRIMARY KEY,"
                            "name TEXT,"
                            "scene INTEGER,"
                            "row INTERGER)";

    if (!query.exec(sql_statement)) {
      PrintMsg("Create table " + GlobalStrs::NpcTableName + " failed");
      return false;
    }
  }

  QXlsx::Worksheet *sheet = npc_doc_->currentWorksheet();
  QXlsx::CellRange cell_range = npc_doc_->currentWorksheet()->dimension();

  QSqlQuery query;

  int row = cell_range.lastRow();

  // init ui progressbar
  QString title = GlobalStrs::CheckProgressHead + GlobalStrs::NpcSheetName;
  QString progname = GlobalStrs::NpcTableName;
  ProgressBar *pb = CreateNewProgressBar(title, progname, 0, row, 5);
  pb->show();

  for (int i = 5; i <= row; i++) {
    QString sn = GetCell(sheet, i, 1);
    QString name = GetCell(sheet, i, 2);
    QString scene = GetCell(sheet, i, 5);
    QString row = QString::number(i);

    bool hasChanged = false;

    // check is data changed.
    QString sql = QString("SELECT * FROM %1 WHERE sn = :sn").arg(GlobalStrs::NpcTableName);
    query.prepare(sql);
    query.bindValue(":sn", sn);
    if (query.exec()) {
      if (query.next()) {
        if (sn != query.value(0).toString() || name != query.value(1).toString() ||
            scene != query.value(2).toString() || row != query.value(3).toString()) {
          hasChanged = true;
        }
      }
    }

    if (hasChanged) {
      QString sql_statement =
          "INSERT OR REPLACE INTO " + GlobalStrs::NpcTableName + " VALUES (?, ?, ?, ?)";
      query.prepare(sql_statement);
      query.addBindValue(GetCell(sheet, i, 1));
      query.addBindValue(GetCell(sheet, i, 2));
      query.addBindValue(GetCell(sheet, i, 5));
      query.addBindValue(QString::number(i));

      if (!query.exec()) {
        QString error = GlobalStrs::InsertFailed + sql_statement;
        PrintMsg(error);

        pb->close();
        delete pb;

        return false;
      }
    }

    pb->SetValue(i);
  }

  pb->close();
  delete pb;

  return true;
}

bool XlsxSQL::CreateSceneTable() {
  scene_doc_->selectSheet(GlobalStrs::SceneSheetName);
  if (!db_.tables().contains(GlobalStrs::SceneTableName)) {
    QSqlQuery query;
    QString sql_statement = "CREATE TABLE IF NOT EXISTS " + GlobalStrs::SceneTableName +
                            "(sn INTEGER PRIMARY KEY,"
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

  // init ui progressbar
  QString title = GlobalStrs::CheckProgressHead + GlobalStrs::SceneSheetName;
  QString progname = GlobalStrs::SceneTableName;
  ProgressBar *pb = CreateNewProgressBar(title, progname, 0, row, 5);
  pb->show();

  for (int i = 5; i <= row; i++) {
    QString sn = GetCell(sheet, i, 1);
    QString scene = GetCell(sheet, i, 2);

    bool hasChanged = false;

    // check is data changed.
    QString sql = QString("SELECT * FROM %1 WHERE sn = :sn").arg(GlobalStrs::SceneTableName);
    query.prepare(sql);
    query.bindValue(":sn", sn);
    if (query.exec()) {
      if (query.next()) {
        if (sn != query.value(0).toString() || scene != query.value(1).toString()) {
          hasChanged = true;
        }
      }
    }

    if (hasChanged) {
      QString sql_statement =
          "INSERT OR REPLACE INTO " + GlobalStrs::SceneTableName + " VALUES(?, ?)";

      query.prepare(sql_statement);
      query.addBindValue(GetCell(sheet, i, 1));
      query.addBindValue(GetCell(sheet, i, 2));

      if (!query.exec()) {
        PrintMsg(GlobalStrs::InsertFailed + sql_statement);

        pb->close();
        delete pb;

        return false;
      }
    }

    pb->SetValue(i);
  }

  pb->close();
  delete pb;

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
