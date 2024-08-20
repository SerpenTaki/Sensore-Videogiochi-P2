#include "headers/sacro.h"

sacro::sacro(string n, double d, int nT, int nA, int lvFede)
: sensoreDanno(n, d, nT, nA), lvFede(lvFede){
  if(getNome().empty()){
    std::cerr << "Oggetto non creato, nome vuoto" << endl;
    return;
  }
  cout << "Oggetto sacro Creato" << endl;
    setSizeAttacchiPerTurno();
    setLimit();
   cout << "Nome: " << getNome() 
         << "\nDanno Base: " << getDanno() 
         << "\nNTurni: " << getAttacchiPerTurno().size()
         << "\nAff: " << getLvFede()
         << "\nAtt per Turno: " << getAtt()
         << endl;
}

sacro::sacro(string n, double d, int nT, int nA, vector<double> rDPT, int lvFede, vector<int> limit)
: sensoreDanno(n, d, nT, nA, rDPT), lvFede(lvFede), limitBar(limit){
  if(getNome().empty()){
    std::cerr << "Oggetto non creato, nome vuoto" << endl;
    return;
  }
  cout << "Oggetto sacro Importato" << endl;
    setSizeAttacchiPerTurno();
    setLimit();
   cout << "Nome: " << getNome() 
         << "\nDanno Base: " << getDanno() 
         << "\nNTurni: " << getAttacchiPerTurno().size()
         << "\nAff: " << getLvFede()
         << "\nAtt per Turno: " << getAtt()
         << endl;
}

int sacro::getLvFede() const { return lvFede; }
int sacro::getlimitBreak() const { return limitbreak; }

void sacro::setLimit(){
  limitBar.resize(getNTurni());
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
  if(checkLimit() == true){
    nDanni = 10000;
    cout << "Hai superato la limit fai un mega danno" << endl;
    limitbreak = 0; //reset della limit
  }
  return nDanni;
}

void sacro::updateLimitbreak() {
    /* Questo metodo mi calcola un numero random da 1 a 10 e mi restituisce il
     * valore aggiornato di limit */
    int randomValue;
    std::random_device rd;
    std::mt19937 gen(rd());
    if(lvFede == fedeBassa){
      std::uniform_int_distribution<> dis(1, 2);
      randomValue = dis(gen);
    }
    else if (lvFede == fedeMedia){
      std::uniform_int_distribution<> dis(1, 5);
      randomValue = dis(gen);
    }
    else{
      std::uniform_int_distribution<> dis(3, 10);
      randomValue = dis(gen);
    }
    limitbreak += randomValue;
}


vector<int> sacro::getValoriLimitBar() {
  vector<int> result;
  for (auto i = limitBar.begin(); i != limitBar.end(); i++) {
    int limitPerTurno = *i + limitbreak;
    result.push_back(limitPerTurno);
  }
  return result;
}

string sacro::toXML() const {
  std::ostringstream oss;
  oss << "<sacro>\n";
  oss << "  <nome>" << getNome() << "</nome>\n";
  oss << "  <danno_base>" << getDanno() << "</danno_base>\n";
  oss << "  <numero_turni>" << getAttacchiPerTurno().size() << "</numero_turni>\n";
  oss << "  <lvFede>" << getLvFede() << "</lvFede>\n";
  oss << "  <limitbreak>" << getlimitBreak() << "</limitbreak>\n";

  oss << "  <danni_per_turno>\n";
  for (double danno : getAttacchiPerTurno()) {
    oss << "    <danno>" << danno << "</danno>\n";
  }
  oss << "  </danni_per_turno>\n";

  oss << "  <limitBar>\n";
  for (int limit : limitBar) {
    oss << "    <limit>" << limit << "</limit>\n";
  }
  oss << "  </limitBar>\n";

  oss << "</sacro>\n";
  return oss.str();
}

void sacro::accept(Visitor* v){
  v->visitSacro(this);
}