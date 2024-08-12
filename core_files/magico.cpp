#include "headers/magico.h"

magico::magico(string n, double d, int nT, int nA, int lvM, bool isInSta): sensoreDanno(n, d, nT, nA), lvMagia(lvM), isInStatus(isInSta) {
  if(getNome().empty()){
    std::cerr << "Oggetto non creato, nome vuoto" << endl;
    return;
  }
  cout << "Oggetto magico creato" << endl;
    setSizeAttacchiPerTurno();
   cout << "Nome: " << getNome() 
         << "\nDanno Base: " << getDanno() 
         << "\nNTurni: " << getAttacchiPerTurno().size()
         << "\nlvMagia: " << getLvMagia()
         << "\nisInSta: " << checkCondition()
         << "\nAtt per Turno: " << getAtt()
         << endl;
}

int magico::getLvMagia() const { return lvMagia; }

bool magico::checkCondition() const { return isInStatus; }

double magico::getHit() {
  if (getProbHit() > 45) {
    return calcolaDanno();
  }
  return 0.0;
}

double magico::calcolaDanno() {
  double nDanni = getDanno();
  nDanni = nDanni + ((getLvMagia() / 2) * 2);
  if (checkCondition()) {
    nDanni = nDanni + nDanni * 0.3;
    if (getProbCrit() > 85) {
      nDanni = (nDanni * 20) / 100;
    }
    return nDanni;
  }
  setStatus();
  return nDanni;
}

string magico::setStatus() {
  if (getRand() > 70) {
    //checkCondition() = true; //da sistemare
    return "incantato";
  }
  else
    return "nope";
}

void magico::accept(Visitor* v){
  v->visitMagico(this);
}
