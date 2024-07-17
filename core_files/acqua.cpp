#include "headers/acqua.h"
#include <iostream>
// #include "../visitor/getType.h"

const std::string acqua::tipo = "Acqua";
void acqua::accept(visitor &sensore) { sensore.visit(this); }

double acqua::getHit() {
  if (getProbHit() > 10) {
    return this->calcolaDanno();
  }
  return 0.0;
}

double acqua::calcolaDanno() {
  double nDanni = getDanno();
  nDanni = nDanni + (nDanni * (getLvMagia() / 10));
  if (checkCondition() == true) {
    std::cout << "Hai Vinto" << std::endl;
    return nDanni;
  }
  if (getProbCrit() > 75) {
    nDanni = (nDanni * 20) / 100;
    return nDanni;
  }
  setStatus();
  return nDanni;
}

string acqua::setStatus() {
  if (getRand() > 95) {
    checkCondition() == true;
    return "Annegato";
  } else
    return "nope";
}
