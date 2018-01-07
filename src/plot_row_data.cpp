#include "plot_row_data.h"

PlotRowData::PlotRowData() {}

PlotRowData::PlotRowData(const QString& sn,
                         const QString& next_sn,
                         const QString& npc_sn,
                         const QString& content,
                         const QString& voice)
    : sn(sn),
      next_sn(next_sn),
      npc_sn(npc_sn),
      content(content),
      voice(voice)

{}

PlotRowData::PlotRowData(const PlotRowData& prd) {
  sn = prd.sn;
  next_sn = prd.next_sn;
  npc_sn = prd.npc_sn;
  content = prd.content;
  voice = prd.voice;
}

PlotRowData& PlotRowData::operator=(const PlotRowData& prd) {
  sn = prd.sn;
  next_sn = prd.next_sn;
  npc_sn = prd.npc_sn;
  content = prd.content;
  voice = prd.voice;

  return *this;
}
