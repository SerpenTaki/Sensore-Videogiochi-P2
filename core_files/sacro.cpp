#include "headers/sacro.h"
#include <iostream>
#include <random>

const std::string sacro::tipo = "Sacro";

int sacro::getLvFede() const { return lvFede; }

int sacro::getlimitBreak() const { return limitbreak; }

sacro::sacro(double d, int ph, int pc, std::vector<int> tpt, int lvFede,
             int limitbreak)
    : sensoreDanno(d, ph, pc, tpt), lvFede(lvFede), limitbreak(limitbreak) {
  std::cout << "Oggetto sacro Creato" << std::endl;
}

sacro::sacro(double d, int ph, int pc, vector<int> tpt, int lvFede,
             int limitbreak, vector<int> limitBar)
    : sensoreDanno(d, ph, pc, tpt), lvFede(lvFede), limitbreak(limitbreak),
      limitBar(limitBar) {
  std::cout << "Oggetto sacro Creato" << std::endl;
}

sacro::sacro() : sensoreDanno() {
  std::cout << "Oggetto sacro Creato" << std::endl;
}

bool sacro::checkLimit() { /*Gestito dalla UI mi fa vincere magari pop-up*/
  if (limitbreak < 100)
    return false;
  else
    return true;
}

double sacro::getHit() { /*si collega all'interfaccia grafica*/
  if (getProbHit() > 80) {
    return this->calcolaDanno();
  }
  return 0.0;
}

double sacro::calcolaDanno() {
  double nDanni = getDanno();
  if (lvFede == fedeBassa) {
    nDanni = nDanni * 20 / 10;
  } else if (lvFede == fedeMedia) {
    nDanni = nDanni * 40 / 10;
  } else {
    nDanni = nDanni * 65 / 10;
  }
  if (getProbCrit() > 40) {
    nDanni = (nDanni * 15) / 100;
  }
  updateLimitbreak();
  return nDanni;
}

void sacro::updateLimitbreak() {
  /*Questo metodo mi calcola un numero random da 1 a 10 e mi restituisce il
   * valore aggiornato di limit*/
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 10);
  int n = 7;
  limitbreak = limitbreak + 7;
}
/*PER mostrare il grafico di limit la UI farà un cast da sensore a sacro. Se
 * il cast va a buon fine chiama la funzione get grafico limit specifica di
 * sacro*/
// SU SACRO GABRIELE QUINDI DOVRAI IMPLEMENTARTI UNA TUA FUNZIONE CHE
// COMUNQUE SARà SIMILE a quella di sensore danno (nel senso che ritorna un
// vettore di qualcosa)

void sacro::accept(visitor &sensore) { sensore.visit(this); }
/*PER mostrare il grafico di limit la UI farà un cast da sensore a sacro. Se
 * il cast va a buon fine chiama la funzione get grafico limit specifica di
 * sacro*/
// SU SACRO GABRIELE QUINDI DOVRAI IMPLEMENTARTI UNA TUA FUNZIONE CHE
// COMUNQUE SARà SIMILE a quella di sensore danno (nel senso che ritorna un
// vettore di qualcosa)

vector<int> sacro::getValoriLimitBar() {
  vector<int> result;
  for (auto i = limitBar.begin(); i != limitBar.end(); i++) {
    int limitPerTurno = *i + limitbreak;
    result.push_back(limitbreak);
  }
  return result;
}

/*
void sacro::accept(visitor &visitor){

}*/
