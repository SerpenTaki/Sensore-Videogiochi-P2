#include "headers/sensoreDanno.h"
#include <random>

sensoreDanno::sensoreDanno(string n, double d, int nT, int nA)
: nome(n), danno(d), nTurni(nT), nAtt(nA) {
  recordDanniPerTurno.resize(nT);
}

sensoreDanno::sensoreDanno(string n, double d, int nT, int nA, vector<double> rDPT)
: nome(n), danno(d), nTurni(nT), nAtt(nA), recordDanniPerTurno(rDPT) { }

sensoreDanno::~sensoreDanno() {cout << "Distrutto " << nome << endl;}

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

void sensoreDanno::incrementaHit(){
  hit++;
}

void sensoreDanno::incrementaMiss(){
  miss++;
}

void sensoreDanno::generaValoriRandomGrafico() {
  hit = 0;
  miss = 0;
  setSizeAttacchiPerTurno();
  if(recordDanniPerTurno.empty() == false){
    recordDanniPerTurno.clear();
  }
  for (auto i = attacchiPerTurno.begin(); i != attacchiPerTurno.end(); i++) {
    double dannoPerTurno = 0;
    for(int n=0; n < nAtt; n++){
      dannoPerTurno += getHit();
    }
    recordDanniPerTurno.push_back(dannoPerTurno);
  }
} // Questa non si ovverrida da nessuna parte

vector<double> sensoreDanno::getRecordDanniPerTurno() const{
  return recordDanniPerTurno;
}

void sensoreDanno::setNome(const string& n) {
    nome = n;
}

void sensoreDanno::setDanno(double d) {
    danno = d;
}

void sensoreDanno::setNTurni(int nT) {
    nTurni = nT;
}

void sensoreDanno::setAttacchiPerTurno(const vector<int>& att) {
    attacchiPerTurno = att;
}

void sensoreDanno::setRecordDanniPerTurno(const vector<double>& record) {
    recordDanniPerTurno = record;
}

void sensoreDanno::setAtt(int nA){
    nAtt = nA;
}

int sensoreDanno::getNHit() const{
  return hit;
}

int sensoreDanno::getNMiss() const{
  return miss;
}

int sensoreDanno::getHitRate() const{
  return (hit*100)/(nAtt*nTurni);
}