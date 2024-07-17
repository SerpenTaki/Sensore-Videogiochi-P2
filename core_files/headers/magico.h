#ifndef MAGICO_H
#define MAGICO_H

#include "sensoreDanno.h"

class sensoreDanno;

class magico : virtual public sensoreDanno {
private:
  int lvMagia; // dall' 1 al 5
  string status;
  bool isInStatus;

public:
  magico(double, int, int, vector<int>, int, string, bool);
  ~magico();

  int getLvMagia() const;
  string getStatus() const;
  bool checkCondition() const;

  virtual string setStatus();
};

#endif
