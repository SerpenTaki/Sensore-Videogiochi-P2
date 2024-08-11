#ifndef MAGICO_H
#define MAGICO_H

#include "sensoreDanno.h"

class magico : virtual public sensoreDanno {
private:
  int lvMagia; // dall' 1 al 5
  bool isInStatus;
public:
  magico(string n, double d, int nT, int lvM, bool isInSta);


  int getLvMagia() const;
  bool checkCondition() const;

  string setStatus();

  double calcolaDanno() override;
  double getHit() override;

  void accept(Visitor* v) override;
};

#endif
