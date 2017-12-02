#ifndef CONFIG_H
#define CONFIG_H

#include "pch.h"

class EditorConfig {
 public:
  explicit EditorConfig(QString &);
  ~EditorConfig();

 public:
  QString GetField(QString &);

 private:
  void ParserData(QString &);

 private:
  QString json_file_path_;

  QJsonDocument json_document_;
};

#endif  // CONFIG_H
