#include "headers/magico.h"
#include <iostream>

magico::magico(double d, int ph, int pc, vector<int> tpt, int lvM, string stat,
               bool isInSta)
    : sensoreDanno(d, ph, pc, tpt), lvMagia(lvM), status(stat),
      isInStatus(isInSta) {
  std::cout << "Oggetto magico creato" << std::endl;
}

int magico::getLvMagia() const { return lvMagia; }

string magico::getStatus() const { return status; }

bool magico::checkCondition() const { return isInStatus; }
