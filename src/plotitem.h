#ifndef PLOTITEM_H
#define PLOTITEM_H

#include <QHBoxLayout>
#include <QLabel>

class PlotItem : public QWidget {
  Q_OBJECT
 public:
  explicit PlotItem(QWidget *parent = nullptr);
  ~PlotItem();
 signals:

 public slots:

 private:
  QLabel *labelSn;
  QLabel *labelNextSn;
  QLabel *labelContent;
  QLabel *labelVoice;

  QHBoxLayout *hbl;
};

#endif  // PLOTITEM_H
