#ifndef PLOTABOUT_H
#define PLOTABOUT_H

#include <QDialog>

namespace Ui {
class PlotAbout;
}

class PlotAbout : public QDialog
{
    Q_OBJECT

public:
    explicit PlotAbout(QWidget *parent = 0);
    ~PlotAbout();

private:
    Ui::PlotAbout *ui;
};

#endif // PLOTABOUT_H
