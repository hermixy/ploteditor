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

static void PrintMsg(QString& content) {
  QMessageBox msg_box;
  msg_box.setText(content);
  msg_box.exec();
}

#endif  // PCH_H
