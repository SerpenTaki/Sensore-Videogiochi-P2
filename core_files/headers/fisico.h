#ifndef FISICO_H
#define FISICO_H

#include "sensoreDanno.h"
#include "visitor.h"

class fisico : virtual public sensoreDanno {
private:
  int affilatura;
public:
  // per implementazione grafica
  fisico(string n, double d, int nT, int aff);

  int getAffilatura() const;

  double getHit() override;
  double calcolaDanno() override;

  void accept(Visitor* v) override { v->visitFisico(this); }
};

#endif
