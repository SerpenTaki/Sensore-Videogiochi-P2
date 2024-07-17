#include "headers/fuoco.h"

const std::string fuoco::tipo = "Fuoco";
void fuoco::accept(visitor &sensore) { sensore.visit(this); }

double fuoco::getHit() {
  if (getProbHit() > 45) {
    return this->calcolaDanno();
  }
  return 0.0;
}
/*
void fuoco::accept(visitor &visitor){

}*/

double fuoco::calcolaDanno() {
  double nDanni = getDanno();
  nDanni = nDanni + ((getLvMagia() / 2) * 2);
  if (checkCondition() == true) {
    nDanni = nDanni + nDanni * 0.3;
    if (getProbCrit() > 85) {
      nDanni = (nDanni * 20) / 100;
    }
    return nDanni;
  }
  setStatus();
  return nDanni;
}

string fuoco::setStatus() {
  if (getRand() > 70) {
    checkCondition() == true;
    return "Bruciato";
  } else
    return "nope";
}
