#ifndef MAGICO_H
#define MAGICO_H

#include "sensoreDanno.h"

class magico : virtual public sensoreDanno {
private:
  int lvMagia; // dall' 1 al 5
  string status;
  bool isInStatus;

public:
  magico(double d, int ph, int pc, vector<int> tpt, int lvM, string stat, bool isInSta);


  int getLvMagia() const;
  string getStatus() const;
  bool checkCondition() const;

  string setStatus();

  double calcolaDanno();
  double getHit();
};

#endif
