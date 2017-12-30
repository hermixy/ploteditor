#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>

namespace Ui {
class ProgressBar;
}

class ProgressBar : public QWidget {
  Q_OBJECT

 public:
  /*
   * @param title Window title
   * @param label Progress name
   * */
  explicit ProgressBar(const QString &, const QString &, QWidget *parent = 0);
  ~ProgressBar();

  void SetValue(int);
  void SetRange(int, int);

 private:
  Ui::ProgressBar *ui;
};

#endif  // PROGRESSBAR_H
