#include "editorconfig.h"

EditorConfig::EditorConfig(const QString &jsonfile) {
  json_file_path_ = jsonfile;
  ParserData(json_file_path_);
}

EditorConfig::~EditorConfig() {}

QString EditorConfig::GetField(const QString &fieldname) {
  QString retqstr = QString();

  if (json_document_.isEmpty()) {
    PrintMsg(GlobalStrs::GetWarning(GlobalStrs::JSON_DOCUMENT_NOT_OBJECT));
    return retqstr;
  }

  QJsonValue value = json_document_.object().value(fieldname);
  if (value.isString()) {
    retqstr = value.toString();
    return retqstr;
  }

  return retqstr;
}

void EditorConfig::ParserData(const QString &filepath) {
  QFile file(filepath);
  if (!file.exists()) {
    // PrintMsg(GlobalStrs::GetWarning(GlobalStrs::FILE_NOT_FOUND));
    this->CreateConfigFile(filepath);
  }

  file.open(QFile::ReadOnly);
  json_document_ = QJsonDocument::fromJson(file.readAll());

  file.close();
}

void EditorConfig::CreateConfigFile(const QString &filepath) {
  QJsonDocument doc;

  QJsonObject obj;
  obj[GlobalStrs::SCENE_XLSX_FILE_KEY] = "s";
  obj[GlobalStrs::NPC_XLSX_FILE_KEY] = "n";
  obj[GlobalStrs::PLOT_XLSX_FILE_KEY] = "p";
  obj[GlobalStrs::COLOR1] = "#ff0000";
  obj[GlobalStrs::COLOR2] = "#00ff00";
  obj[GlobalStrs::COLOR3] = "#0000ff";
  obj[GlobalStrs::COLOR4] = "#1f2f3f";
  obj[GlobalStrs::COLOR5] = "#4f5f6f";

  doc.setObject(obj);

  QFile file(filepath);
  file.open(QFile::WriteOnly);
  file.write(doc.toJson());
  file.close();
}
