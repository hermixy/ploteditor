#include "progressbar.h"
#include "ui_progressbar.h"

ProgressBar::ProgressBar(const QString &title, const QString &progname, QWidget *parent)
    : QWidget(parent), ui(new Ui::ProgressBar) {
  ui->setupUi(this);

  setWindowTitle(title);
  ui->label->setText(progname);
  ui->progressBar->setAttribute(Qt::WA_DeleteOnClose, true);

  ui->progressBar->reset();
  ui->progressBar->setMinimum(0);
  ui->progressBar->setMaximum(100);
}

ProgressBar::~ProgressBar() {
  delete ui;
}

void ProgressBar::SetValue(int value) {
  QApplication::processEvents();
  ui->progressBar->setValue(value);
}

void ProgressBar::SetRange(int min, int max) {
  ui->progressBar->setMinimum(min);
  ui->progressBar->setMaximum(max);
}
