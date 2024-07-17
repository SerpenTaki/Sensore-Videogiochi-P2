#ifndef SENSOREDANNO_H
#define SENSOREDANNO_H

// #include <iostream>
#include <string>
#include <vector>

#include "../../visitor/visitor.h"

using std::string;
using std::vector;

class sensoreDanno {
private:
  std::string nome;
  double danno;
  int probHit;  // random
  int probCrit; // random
  int randN;

protected:
  vector<int> attacchiPerTurno;

public:
  sensoreDanno(double, int, int, vector<int>);

  sensoreDanno();
  virtual ~sensoreDanno();

  virtual vector<double> getValoriGrafico() final; // metodo per il grafico
  // Metodi getter
  double getDanno() const;
  int getProbHit() const;
  int getProbCrit() const;
  int getRand();
  std::string getNome() const;
  // altro
  virtual double calcolaDanno();
  virtual double getHit();
  // per implementazione grafica
  virtual void accept(visitor &visitor) = 0;
};

#endif
