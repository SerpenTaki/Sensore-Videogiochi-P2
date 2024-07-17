#ifndef SENSOREDANNO_H
#define SENSOREDANNO_H

// #include <iostream>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class sensoreDanno {
private:
  std::string nome;
  double danno;
  int probHit;  // random
  int probCrit; // random
  int randN;
  vector<int> attacchiPerTurno;
public:
  
  sensoreDanno(double d, int ph, int pc, vector<int> tpt);
  virtual ~sensoreDanno();

  virtual vector<double> getValoriGrafico() final; // metodo per il grafico
  // Metodi getter
  double getDanno() const;
  int getProbHit() const;
  int getProbCrit() const;
  int getRand();
  string getNome() const;
  // metodi virtuali puri
  virtual double calcolaDanno() =0;
  virtual double getHit() =0;
};

#endif
