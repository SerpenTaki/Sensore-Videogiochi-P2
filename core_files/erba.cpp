#include "headers/erba.h"

const std::string erba::tipo = "Erba";
void erba::accept(visitor &sensore) { sensore.visit(this); }

double erba::getHit() {
  if (getProbHit() > 30) {
    return this->calcolaDanno();
  }
  return 0.0;
}
/*
void erba::accept(visitor &visitor){

}*/

double erba::calcolaDanno() {
  double nDanni = getDanno();
  nDanni = nDanni + ((getLvMagia() / 2) * 2);
  if (checkCondition() == true) {
    nDanni = nDanni + nDanni * 0.15;
    if (getProbCrit() > 45) {
      nDanni = (nDanni * 15) / 100;
    }
    return nDanni;
  }
  setStatus();
  return nDanni;
}

string erba::setStatus() {
  if (getRand() > 70) {
    checkCondition() == true;
    return "Legato";
  } else
    return "nope";
}
