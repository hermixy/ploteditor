#ifndef PCH_H
#define PCH_H

#include <string>

#include <qapplication.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qlineedit.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qregularexpression.h>
#include <qsettings.h>
#include <qstring.h>
#include <qwidget.h>

#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>

#include <xlsxdocument.h>

// global variables

// end global variables

namespace GlobalStrs {
static const QString CONFIG_FILE_NAME = QString("config.json");
static const QString NPC_XLSX_FILE_KEY = QString("NpcXlsxPath");
static const QString PLOT_XLSX_FILE_KEY = QString("PlotXlsxPath");
static const QString SCENE_XLSX_FILE_KEY = QString("SceneXlsxPath");
static const QString MISSION_XLSX_FILE_KEY = QString("MissionXlsxPath");

static const QString COLOR1_KEY = QString("Color1");  // #ff0000
static const QString COLOR2_KEY = QString("Color2");  // #00ff00
static const QString COLOR3_KEY = QString("Color3");  // #0000ff
static const QString COLOR4_KEY = QString("Color4");  // #1f2f3f
static const QString COLOR5_KEY = QString("Color5");  // #4f5f6f

static const QString COLOR1 = QString("#FF0000");  // #ff0000
static const QString COLOR2 = QString("#00FF00");  // #00ff00
static const QString COLOR3 = QString("#0000FF");  // #0000ff
static const QString COLOR4 = QString("#1F2F3F");  // #1f2f3f
static const QString COLOR5 = QString("#4F5F6F");  // #4f5f6f

static const QString WARNING_NO_NPC_FILE = QString("没有选定Npc配置文件\n");
static const QString WARNING_NO_SCENE_FILE = QString("没有选定Scene配置文件\n");
static const QString WARNING_NO_PLOT_FILE = QString("没有选定Plot配置文件\n");
static const QString WARNING_NO_MISSION_FILE = QString("没有选定Mission配置文件\n");

static const QString NpcSheetName = QString("Npc|Npc");
static const QString NpcTableName = QString("Npc");
static const QString SceneSheetName = QString("场景副本|Scene");
static const QString SceneTableName = QString("Scene");

}  // namespace GlobalStrs

static QString GetINIFilePath() {
  return QApplication::applicationDirPath() + "/config.ini";
}

static QString GetDBFilePath() {
  return QApplication::applicationDirPath() + "/xlsx.db";
}

static bool IsFileExists(const QString &path) {
  QFileInfo check_file(path);
  // check if file exists and if yes: Is it really a file and no directory?
  return check_file.exists() && check_file.isFile();
}

static void PrintMsg(const QString &content) {
  QMessageBox msg_box;
  msg_box.setText(content);
  msg_box.exec();
}

#endif  // PCH_H
