#include "headers/fisico.h"
#include <iostream>

fisico::fisico(double d, int ph, int pc, vector<int> tpt, int aff): sensoreDanno(d, ph, pc, tpt), affilatura(aff) {
  std::cout << "Oggetto fisico Creato" << std::endl;
}

int fisico::getAffilatura() const { return affilatura; }

double fisico::getHit() { /*si collega all'interfaccia grafica*/
  if (getProbHit() > 30) {
    return this->calcolaDanno();
  }
  return 0.0;
}

double fisico::calcolaDanno() { // assestante
  double nDanni = getDanno();
  nDanni = nDanni * affilatura / 10;
  if (getProbCrit() > 75) {
    nDanni = (nDanni * 30) / 100;
    return nDanni;
  } else
    return nDanni;
}
