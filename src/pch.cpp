#include "pch.h"

QString GetINIFilePath() {
  return QApplication::applicationDirPath() + "/config.ini";
}

QString GetDBFilePath() {
  return QApplication::applicationDirPath() + "/xlsx.db";
}

bool IsFileExists(const QString &path) {
  QFileInfo check_file(path);
  // check if file exists and if yes: Is it really a file and no directory?
  return check_file.exists() && check_file.isFile();
}

void PrintMsg(const QString &content) {
  QMessageBox msg_box;
  msg_box.setText(content);
  msg_box.exec();
}

ProgressBar *CreateNewProgressBar(const QString &title, const QString &progname, int min, int max,
                                  int val) {
  ProgressBar *pb = new ProgressBar(title, progname);
  pb->SetRange(min, max);
  pb->SetValue(val);

  return pb;
}

bool ExecuteSQLQuery(QSqlQuery &query, const QString &sql_statement, const QString &error) {
  if (!query.exec(sql_statement)) {
    if (!(error.isNull() || error.isEmpty())) {
      PrintMsg(error);
    }

    return false;
  }

  return true;
}
