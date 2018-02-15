#include "plotabout.h"
#include "ui_plotabout.h"

PlotAbout::PlotAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotAbout)
{
    ui->setupUi(this);
}

PlotAbout::~PlotAbout()
{
    delete ui;
}
