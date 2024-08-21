#ifndef MAGICO_H
#define MAGICO_H

#include "sensoreDanno.h"

class magico : virtual public sensoreDanno {
private:
  int lvMagia; // dall' 1 al 5
  bool isInStatus;
public:
  magico(string n, double d, int nT, int nA, int lvM, bool isInSta);
  magico(string n, double d, int nT, int nA, vector<double> rDPT, int lvM, bool isInSta);

  int getLvMagia() const;
  bool checkCondition() const;

  string setStatus();

  double calcolaDanno() override;
  double getHit() override;
  bool toXML(const std::string& filename) const override;

  void accept(Visitor* v) override;
};

#endif
