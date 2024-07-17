#ifndef FISICO_H
#define FISICO_H

#include "sensoreDanno.h"

class sensoreDanno;

class fisico : virtual public sensoreDanno {
private:
  int affilatura; //% da richiedere all'utente altrimenti random
public:
  static const std::string tipo;
  // per implementazione grafica
  void accept(visitor &) override;
  fisico(double, int, int, vector<int>, int);
  fisico();
  ~fisico();
  int getAffilatura() const;

  double getHit() override;
  double calcolaDanno() override;
};

#endif
