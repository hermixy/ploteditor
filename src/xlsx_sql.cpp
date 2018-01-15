#include "pch.h"

XlsxSQL *XlsxSQL::instance_ = nullptr;

XlsxSQL::XlsxSQL(const QString &plot_path, const QString &npc_path, const QString &scene_path) {
  instance_ = this;

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

XlsxSQL::~XlsxSQL() {
  this->db_.close();

  if (nullptr != plot_doc_)
    delete (plot_doc_);

  if (nullptr != npc_doc_)
    delete (npc_doc_);

  if (nullptr != scene_doc_)
    delete (scene_doc_);

  instance_ = nullptr;
}

XlsxSQL *XlsxSQL::Instance() {
  return instance_;
}

QSqlDatabase &XlsxSQL::GetDataBase() {
  return db_;
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

    qDebug() << "Create table " << table_name << " start.";

    query.prepare(sql_statement);
    if (!query.exec()) {
      query.finish();
      return false;
    }
  }

  qDebug() << "Create table done.";

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
      if (!query.first()) {
        hasChanged = true;
      } else {
        if (query.next()) {
          if (sn != query.value(0).toString() || order != query.value(1).toString() ||
              npcsn != query.value(2).toString() || content != query.value(3).toString() ||
              voice != query.value(4).toString()) {
            hasChanged = true;
          }
        } else {
          hasChanged = true;
        }
      }
    }

    query.finish();

    if (hasChanged) {
      QString sql_statement = "INSERT INTO " + table_name + " VALUES (?, ?, ?, ?, ?, ?)";
      query.prepare(sql_statement);
      query.addBindValue(sn);       // sn
      query.addBindValue(order);    // order(next)
      query.addBindValue(npcsn);    // npc sn
      query.addBindValue(content);  // content
      query.addBindValue(voice);    // voice
      query.addBindValue(QString::number(i));

      error_tips = GlobalStrs::InsertFailed + sql_statement;
      if (!query.exec()) {
        PrintMsg(error_tips);

        query.finish();

        pb->close();
        delete pb;

        return false;
      }

      query.finish();
    }

    pb->SetValue(i);
  }

  pb->close();
  delete pb;

  return true;
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

    query.finish();
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
      } else {
        hasChanged = true;
      }
    }

    query.finish();

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

      query.finish();
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

    query.finish();
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
      } else {
        hasChanged = true;
      }
    }

    query.finish();

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

      query.finish();
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

void XlsxSQL::DropPlotTable() {
  QSqlQuery query(this->db_);
  QString sql = "DROP TABLE IF EXISTS Plot";
  query.prepare(sql);
  if (query.exec()) {
    qDebug() << "Drop Plot done.";
  } else {
    qDebug() << "SqLite error:" << query.lastError().text()
             << ", SqLite error code:" << query.lastError().number();
  }

  query.finish();

  sql = "DROP TABLE IF EXISTS FightPlot";
  query.prepare(sql);
  if (query.exec()) {
    qDebug() << "Drop FightPlot done.";
  } else {
    qDebug() << "SqLite error:" << query.lastError().text()
             << ", SqLite error code:" << query.lastError().number();
  }

  query.finish();

  sql = "DROP TABLE IF EXISTS FunctionPlot";
  query.prepare(sql);
  if (query.exec()) {
    qDebug() << "Drop FunctionPlot done.";
  } else {
    qDebug() << "SqLite error:" << query.lastError().text()
             << ", SqLite error code:" << query.lastError().number();
  }

  query.finish();
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

void XlsxSQL::AnalysePlots(const QString &plot_sn, QVector<PlotRowData> &data) {
  // check is already insert.
  for (int i = 0; i < data.size(); i++) {
    if (data[i].sn == plot_sn)
      return;
  }

  QSqlQuery query;
  QString sql = "SELECT * FROM Plot WHERE sn=:sn";
  query.prepare(sql);
  query.bindValue(":sn", plot_sn);

  if (query.exec()) {
    if (query.next()) {
      QString next_sn = query.value(1).toString();

      data.append(PlotRowData(query.value(0).toString(),
                              next_sn,
                              query.value(2).toString(),
                              query.value(3).toString(),
                              query.value(4).toString()));

      if (next_sn.isEmpty())
        return;
      else
        AnalysePlots(next_sn, data);
    }
  }

  query.finish();

  sql = "SELECT * FROM Plot WHERE next=:next";
  query.prepare(sql);
  query.bindValue(":next", plot_sn);

  if (query.exec()) {
    if (query.next()) {
      QString sn = query.value(0).toString();
      AnalysePlots(sn, data);
    }
  }

  query.finish();
}

void XlsxSQL::RearrangePlots(QVector<PlotRowData> &data) {
  // get head
  QMap<QString, int> in_degrees;
  for (auto &row_data : data) {
    if (in_degrees[row_data.sn] >= 1) {
      continue;
    } else {
      in_degrees[row_data.sn] = 0;
      in_degrees[row_data.next_sn] = 1;
    }
  }

  QString head_sn;
  for (auto &key : in_degrees.keys()) {
    if (in_degrees.value(key) == 0) {
      head_sn = key;
      break;
    }
  }

  int prev_size = data.size();
  int pos = 0;
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data.size(); j++) {
      if (head_sn == data[j].sn) {
        head_sn = data[j].next_sn;
        data.insert(pos, data[j]);
        pos += 1;
        break;
      }
    }
  }

  data.resize(prev_size);
}

void XlsxSQL::GetScenes(QStringList &scenes) {
  scenes.clear();

  QSqlQuery query;
  QString sql = QString("SELECT * FROM %1").arg(GlobalStrs::SceneTableName);

  query.prepare(sql);
  if (query.exec()) {
    while (query.next()) {
      QString sn = query.value(0).toString();
      QString name = query.value(1).toString();

      scenes.append(QString("%1,%2").arg(sn, name));
    }
  }

  query.finish();
}

void XlsxSQL::GetSceneOfNpc(const QString &npc_sn,
                            QString &npc_name,
                            QString &scene_sn,
                            QString &scene_name) {
  scene_sn = "";
  scene_name = "";

  qDebug() << "npc_sn: " << npc_sn;

  if (npc_sn == "" || npc_sn == "0") {
    return;
  }

  QSqlQuery query;
  QString sql = QString("SELECT * FROM Npc WHERE sn=:sn");
  query.prepare(sql);
  query.bindValue(":sn", npc_sn);

  if (query.exec()) {
    if (query.next()) {
      npc_name = query.value(1).toString();
      scene_sn = query.value(2).toString();
    }
  }

  query.finish();

  qDebug() << "scene_sn: " << scene_sn;

  sql = QString("SELECT * FROM Scene WHERE sn=:sn");
  query.prepare(sql);
  query.bindValue(":sn", scene_sn);

  if (query.exec()) {
    if (query.next()) {
      scene_name = query.value(1).toString();
    }
  }

  query.finish();
}
