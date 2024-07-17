#include "headers/sensoreDanno.h"
#include <iostream>
#include <random>

sensoreDanno::sensoreDanno(double d, int ph, int pc, vector<int> tpt)
    : danno(d), probHit(ph), probCrit(pc), attacchiPerTurno(tpt) {
  std::cout << "Oggetto Creato" << std::endl;
}

double sensoreDanno::getDanno() const { return danno; }

int sensoreDanno::getProbCrit() const {
  /*random*/
  return probCrit;
}

int sensoreDanno::getProbHit() const {
  /*random*/
  return probHit;
}

std::string sensoreDanno::getNome() const { return nome; }

int sensoreDanno::getRand() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);
  randN = dis(gen);
  return randN;
}

vector<double> sensoreDanno::getValoriGrafico() {
  vector<double> result;
  for (unsigned int i = 0; i < attacchiPerTurno.size(); i++) {
    double dannoPerTurno = attacchiPerTurno[i] * calcolaDanno();
    result.push_back(dannoPerTurno);
  }
  return result;
} // Questa non si ovverrida da nessuna parte
