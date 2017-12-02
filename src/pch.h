#ifndef PCH_H
#define PCH_H

#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>

#include <qapplication.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qwidget.h>

static void PrintMsg(const QString &content) {
  QMessageBox msg_box;
  msg_box.setText(content);
  msg_box.exec();
}

namespace GlobalStrs {

// some fixed data definition
static const QString CONFIG_FILE_NAME = QString("config.json");
static const QString NPC_XLSX_FILE_KEY = QString("NpcXlsxPath");
static const QString PLOT_XLSX_FILE_KEY = QString("NpcXlsxPath");
static const QString SCENE_XLSX_FILE_KEY = QString("NpcXlsxPath");

// error information definition
static const QString JSON_DOCUMENT_NOT_OBJECT =
    QString("Json document is not an object.");
static const QString FILE_NOT_FOUND = QString("File Not Found.");
}

#endif // PCH_H
