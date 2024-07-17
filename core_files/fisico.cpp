#include "headers/fisico.h"
#include <iostream>

const std::string fisico::tipo = "Fisico";

int fisico::getAffilatura() const { return affilatura; }

double fisico::getHit() { /*si collega all'interfaccia grafica*/
  if (getProbHit() > 30) {
    return this->calcolaDanno();
  }
  return 0.0;
}

fisico::fisico(double d, int ph, int pc, vector<int> tpt, int aff)
    : sensoreDanno(d, ph, pc, tpt), affilatura(aff) {
  std::cout << "Oggetto fisico Creato" << std::endl;
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

void fisico::accept(visitor &sensore) { sensore.visit(this); }
/*
void fisico::accept(visitor &visitor){

}*/
