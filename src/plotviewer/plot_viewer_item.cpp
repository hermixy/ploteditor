#include "pch.h"

PlotViewerItem::PlotViewerItem(QWidget *parent,
                               const QString &sn,
                               const QString &next_sn,
                               const QString &npc_sn,
                               const QString &content,
                               const QString &voice)
    : QWidget(parent) {
  sn_ = sn;

  label_sn_ = new QLabel();
  label_sn_->setAlignment(Qt::AlignCenter);

  label_next_sn_ = new QLabel();
  label_next_sn_->setAlignment(Qt::AlignCenter);

  label_npc_sn_ = new QLabel();
  label_npc_sn_->setAlignment(Qt::AlignCenter);

  label_content_ = new QLabel();
  label_content_->setAlignment(Qt::AlignCenter);

  label_voice_ = new QLabel();
  label_voice_->setAlignment(Qt::AlignCenter);

  label_sn_->setText(sn);
  label_next_sn_->setText(next_sn);
  label_npc_sn_->setText(npc_sn);
  label_content_->setText(content);
  label_voice_->setText(voice);

  hbl_ = new QHBoxLayout(this);
  hbl_->setAlignment(Qt::AlignLeft);

  hbl_->addWidget(label_sn_);
  hbl_->addWidget(label_next_sn_);
  hbl_->addWidget(label_npc_sn_);
  hbl_->addWidget(label_content_);
  hbl_->addWidget(label_voice_);
}

PlotViewerItem::~PlotViewerItem() {
  if (nullptr != label_sn_)
    delete label_sn_;

  if (nullptr != label_next_sn_)
    delete label_next_sn_;

  if (nullptr != label_content_)
    delete label_content_;

  if (nullptr != label_voice_)
    delete label_voice_;

  if (nullptr != hbl_)
    delete hbl_;
}

QString PlotViewerItem::GetSn() {
  return sn_;
}

void PlotViewerItem::SetNextSn(const QString &next_sn) {
  label_next_sn_->setText(next_sn);
}
