#include "headers/sensoreDanno.h"
#include <random>

sensoreDanno::sensoreDanno(string n, double d, int nT, int nA): nome(n), danno(d), nTurni(nT), nAtt(nA) {}

sensoreDanno::~sensoreDanno() {cout << "Distrutto" << endl;} //ho notato che elimina sensore non distrugge il sensore alla fine

int sensoreDanno::getNTurni() const{
  return nTurni;
}

double sensoreDanno::getDanno() const { 
  return danno;
}

int sensoreDanno::getProbCrit(){
  /*random*/
  probCrit = getRand(); 
  return probCrit;
}

int sensoreDanno::getProbHit(){
  /*random*/
  probHit = getRand();
  return probHit;
}

std::string sensoreDanno::getNome() const {
  return nome;
}

int sensoreDanno::getRand() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);
  randN = dis(gen);
  return randN;
}

vector<int> sensoreDanno::getAttacchiPerTurno() const{
  return attacchiPerTurno;
}

int sensoreDanno::getAtt() const{
  return nAtt;
}

void sensoreDanno::setSizeAttacchiPerTurno(){
  attacchiPerTurno.resize(nTurni);
}

vector<double> sensoreDanno::getValoriGrafico() {
  vector<double> result;
  setSizeAttacchiPerTurno();
  for (auto i = attacchiPerTurno.begin(); i != attacchiPerTurno.end(); i++) {
    double dannoPerTurno = 0;
    for(int n=0; n < nAtt; n++){
      dannoPerTurno += *i * getHit();
    }
    result.push_back(dannoPerTurno);
  }
  return result;
} // Questa non si ovverrida da nessuna parte
