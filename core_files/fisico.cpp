#include "headers/fisico.h"

fisico::fisico(string n, double d, int nT, int nA, int aff): sensoreDanno(n, d, nT, nA), affilatura(aff) {
  cout << "Oggetto fisico Creato" << endl;
  setSizeAttacchiPerTurno();
   cout << "Nome: " << getNome() 
         << "\nDanno Base: " << getDanno() 
         << "\nNTurni: " << getNTurni() 
         << "\nAff: " << affilatura 
         << "\nAtt per Turno: " << getAtt()
         << endl;
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

void fisico::accept(Visitor* v) {
  v->visitFisico(this);
}