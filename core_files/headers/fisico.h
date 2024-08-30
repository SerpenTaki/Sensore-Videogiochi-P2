#ifndef FISICO_H
#define FISICO_H

#include "sensoreDanno.h"
#include "visitor.h"

class fisico : virtual public sensoreDanno {
private:
  int affilatura;
public:
  // per implementazione grafica
  fisico(string n, double d, int nT, int nA, int aff);
  fisico(string n, double d, int nT, int nA, vector<double> rDPT, int aff);
  int getAffilatura() const;

  double getHit() override;
  double calcolaDanno() override;
  bool toXML(const std::string& filename) const override;
  //bool fromXML(const std::string& filename) override;

  void setAff(int aff);

  void accept(Visitor* v) override;
};

#endif
