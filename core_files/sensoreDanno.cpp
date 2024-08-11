#include "headers/sensoreDanno.h"
#include <random>

sensoreDanno::sensoreDanno(string n, double d, int nT): nome(n), danno(d), nTurni(nT) {
  cout << "Oggetto Creato" << endl;
}

sensoreDanno::~sensoreDanno() {cout << "Distrutto porcamadonna" << endl;} //ho notato che elimina sensore non distrugge il sensore alla fine

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

vector<double> sensoreDanno::getValoriGrafico(int nTurni) {
  vector<double> result;
  for(int j=0; j<= nTurni; j++){
    double dannoPerTurno = 0;
    for (auto i = attacchiPerTurno.begin(); i != attacchiPerTurno.end(); i++) {
      dannoPerTurno = *i * calcolaDanno();
    }
    result.push_back(dannoPerTurno);
  }
  return result;
} // Questa non si ovverrida da nessuna parte
