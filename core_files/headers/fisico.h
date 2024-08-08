#ifndef FISICO_H
#define FISICO_H

#include "sensoreDanno.h"
#include "visitor.h"

class fisico : virtual public sensoreDanno {
private:
  int affilatura;
public:
  // per implementazione grafica
  fisico(double d, int ph, int pc, vector<int> tpt, int aff);

  int getAffilatura() const;

  double getHit() override;
  double calcolaDanno() override;

  void accept(Visitor* v) override { v->visit(this); }
};

#endif
