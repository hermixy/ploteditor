#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class Settings;
} // namespace Ui

class Settings : public QWidget {
  Q_OBJECT

public:
  explicit Settings(QWidget *parent = 0);
  ~Settings();

private slots:

private:
  Ui::Settings *ui;
};

#endif // SETTINGS_H
