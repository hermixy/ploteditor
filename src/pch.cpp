#include "pch.h"

ProgressBar *CreateNewProgressBar(const QString &title, const QString &progname, int min, int max,
                                  int val) {
  ProgressBar *pb = new ProgressBar(title, progname);
  pb->SetRange(min, max);
  pb->SetValue(val);

  return pb;
}
