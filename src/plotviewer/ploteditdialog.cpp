#include "ploteditdialog.h"
#include "ui_ploteditdialog.h"

#include "pch.h"

PlotEditDialog::PlotEditDialog(const QString &sn, QWidget *parent)
    : QDialog(parent), ui(new Ui::PlotEditDialog) {
  ui->setupUi(this);

  plot_sn_ = sn;

  setWindowTitle(tr("Plot Editor"));

  connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(released()), this, SLOT(Close()));
  connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(released()), this, SLOT(Save()));

  this->InitScenes();
  //  this->InitNpcs();
}

PlotEditDialog::~PlotEditDialog() {
  delete ui;

  //  if (nullptr != scenes_completer_)
  //    delete scenes_completer_;

  //  if (nullptr != npcs_completer_)
  //    delete npcs_completer_;
}

void PlotEditDialog::Save() {
  PrintMsg("FUCK");
}

void PlotEditDialog::Close() {
  this->close();
}

void PlotEditDialog::InitScenes() {
  if (nullptr != XlsxSQL::Instance()) {
    XlsxSQL::Instance()->GetScenes(this->scenes_);

    ui->comboScenes->addItems(this->scenes_);
  }
}

void PlotEditDialog::InitNpcs(const QString &scene_sn) {}
