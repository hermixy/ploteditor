#ifndef CONFIG_H
#define CONFIG_H

#include "pch.h"

class EditorConfig {
 public:
  explicit EditorConfig(const QString &);
  ~EditorConfig();

 public:
  QString GetField(const QString &);

 private:
  void ParserData(const QString &);

  // If the configuration file not found, then create a default file.
  void CreateConfigFile(const QString &);

 private:
  QString json_file_path_;

  QJsonDocument json_document_;
};

#endif  // CONFIG_H
