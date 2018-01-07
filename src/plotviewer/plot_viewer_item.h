#ifndef PLOT_VIEWER_ITEM_H
#define PLOT_VIEWER_ITEM_H

#include <QHBoxLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QWidget>

class PlotViewerItem : public QWidget {
  Q_OBJECT

 public:
  explicit PlotViewerItem(QWidget *,
                          const QString &, /* sn */
                          const QString &, /* next plot sn */
                          const QString &, /* npc sn */
                          const QString &, /* content */
                          const QString &  /* voice */
                          );
  ~PlotViewerItem();

 public:
  QString GetSn();
  void SetNextSn(const QString &);

 private:
  QString sn_;

 private:
  QLabel *label_sn_;
  QLabel *label_next_sn_;
  QLabel *label_npc_sn_;
  QLabel *label_content_;
  QLabel *label_voice_;

  QHBoxLayout *hbl_;
};

#endif  // PLOT_VIEWER_ITEM_H
