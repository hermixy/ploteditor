#ifndef PCH_H
#define PCH_H

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

static void PrintMsg(const QString &content) {
  QMessageBox msg_box;
  msg_box.setText(content);
  msg_box.exec();
}

namespace GlobalStrs {
static const QString CONFIG_FILE_NAME = QString("config.json");
static const QString NPC_XLSX_FILE_KEY = QString("NpcXlsxPath");
static const QString PLOT_XLSX_FILE_KEY = QString("PlotXlsxPath");
static const QString SCENE_XLSX_FILE_KEY = QString("SceneXlsxPath");

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
}

static bool IsFileExists(const QString &path) {
  QFileInfo check_file(path);
  // check if file exists and if yes: Is it really a file and no directory?
  return check_file.exists() && check_file.isFile();
}

#endif  // PCH_H
