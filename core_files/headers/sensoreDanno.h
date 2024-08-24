#ifndef SENSOREDANNO_H
#define SENSOREDANNO_H

// #include <iostream>
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>
#include<random>
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
  vector<double> recordDanniPerTurno;
public:
  sensoreDanno(string n, double d, int nT, int nA);
  sensoreDanno(string n, double d, int nT, int nA, vector<double> rDPT);
  virtual ~sensoreDanno();

  virtual void generaValoriRandomGrafico() final; // metodo per il grafico
  
  // Metodi getter
  double getDanno() const;
  int getProbHit();
  int getProbCrit();
  int getRand();
  string getNome() const;
  int getNTurni() const;
  vector<int> getAttacchiPerTurno() const;
  int getAtt() const;
  vector<double> getRecordDanniPerTurno() const;

  //Metodi setter per modifica sensore
  void setSizeAttacchiPerTurno();
  void setNome(const string& n);
  void setDanno(double d);
  void setNTurni(int nT);
  void setAttacchiPerTurno(const vector<int>& att);
  void setRecordDanniPerTurno(const vector<double>& record);

  // metodi virtuali puri
  virtual double calcolaDanno()=0;
  virtual double getHit() =0;
  virtual bool toXML(const std::string& filename) const =0;
  virtual bool fromXML(const std::string& filename) =0;

  virtual void accept(Visitor* v) = 0;
};

#endif
