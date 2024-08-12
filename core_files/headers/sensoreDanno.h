#ifndef SENSOREDANNO_H
#define SENSOREDANNO_H

// #include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include"visitor.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

class sensoreDanno {
private:
  string nome;
  double danno;
  int probHit;  // random
  int probCrit; // random
  int randN;
  int nTurni;
  int nAtt; 
  vector<int> attacchiPerTurno;
  vector<double> grafico;
public:
  sensoreDanno(string n, double d, int nT, int nA);
  virtual ~sensoreDanno();

  virtual vector<double> getValoriGrafico() final; // metodo per il grafico
  // Metodi getter
  double getDanno() const;
  int getProbHit();
  int getProbCrit();
  int getRand();
  string getNome() const;
  int getNTurni() const;
  vector<int> getAttacchiPerTurno() const;
  int getAtt() const;
  //Metodi setter per modifica sensore
  void setSizeAttacchiPerTurno();
  
  // metodi virtuali puri
  virtual double calcolaDanno()=0;
  virtual double getHit() =0;

  virtual void accept(Visitor* v) = 0;
};

#endif
