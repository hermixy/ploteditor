#include "editorconfig.h"

EditorConfig::EditorConfig(const QString &jsonfile) {
  json_file_path_ = jsonfile;
  ParserData(json_file_path_);
}

EditorConfig::~EditorConfig() {}

QString EditorConfig::GetField(const QString &fieldname) {
  QString retqstr = QString();

  if (!json_document_.isObject()) {

    return retqstr;
  }

  QJsonValue value = json_document_.object().value(fieldname);
  if (value.isObject()) {
    retqstr = value.toString();
    return retqstr;
  }

  return retqstr;
}

void EditorConfig::ParserData(const QString &filepath) {
  QFile file(filepath);
  if (!file.exists()) {
    PrintMsg(GlobalStrs::FILE_NOT_FOUND);
    return;
  }

  file.open(QIODevice::ReadOnly);

  QByteArray bytes = file.readAll();
  json_document_ = QJsonDocument::fromBinaryData(bytes);

  file.close();
}
