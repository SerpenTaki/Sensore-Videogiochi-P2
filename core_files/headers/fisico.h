#ifndef FISICO_H
#define FISICO_H

#include "sensoreDanno.h"

class sensoreDanno;

class fisico : virtual public sensoreDanno {
private:
  int affilatura; //% da richiedere all'utente altrimenti random
public:
  // per implementazione grafica
  fisico(double d, int ph, int pc, vector<int> tpt, int aff);
  ~fisico() = default;
  int getAffilatura() const;

  double getHit() override;
  double calcolaDanno() override;
};

#endif
