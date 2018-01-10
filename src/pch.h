#ifndef PCH_H
#define PCH_H

#include <QtDebug>

#include <QAbstractItemView>
#include <QApplication>
#include <QDialog>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMainWindow>
#include <QMap>
#include <QMessageBox>
#include <QModelIndex>
#include <QProgressDialog>
#include <QPushButton>
#include <QRegularExpression>
#include <QSettings>
#include <QSqlTableModel>
#include <QString>
#include <QVector>
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>

#include <xlsxdocument.h>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>

#include "settings.h"
#include "settings_data.h"
#include "xlsx_sql.h"

#include "plot_row_data.h"
#include "plotviewer/plot_viewer_item.h"
//#include "plotviewer/plot_viewer_model.h"
#include "plotviewer/ploteditdialog.h"
#include "plotviewer/plotviewer.h"
#include "progressbar.h"

#include "utils.h"

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
static const QString MissionSheetName = QString("任务配置|Quest");
static const QString MissionTableName = QString("Mission");

static const QString InsertFailed = QString("Insert failed: ");
static const QString CheckProgressHead = QString("Check Execel: ");

}  // namespace GlobalStrs

QString GetINIFilePath();
QString GetDBFilePath();

/*
 * @param file path
 * @return boolean
 * */
bool IsFileExists(const QString &path);

/*
 * @param content
 * */
void PrintMsg(const QString &content);

/*
 * @param title Window title
 * @param progname Label
 * @param min value
 * @param max value
 * @param initial value
 * */
ProgressBar *CreateNewProgressBar(const QString &, const QString &, int, int, int);

/*
 * @param QSqlQuery
 * @param Sql statement
 * @param Error tips
 * */
bool ExecuteSQLQuery(QSqlQuery &, const QString &, const QString &);

#endif  // PCH_H
