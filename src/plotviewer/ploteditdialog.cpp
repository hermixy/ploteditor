#include "ploteditdialog.h"
#include "ui_ploteditdialog.h"

PlotEditDialog::PlotEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PlotEditDialog) {
  ui->setupUi(this);

  setWindowTitle(tr("Plot Edit"));

  connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(released()), this, SLOT(close()));
  connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(released()), this, SLOT(Save()));
}

PlotEditDialog::~PlotEditDialog() {
  delete ui;
}

void PlotEditDialog::Save() {
  PrintMsg("FUCK");
}
