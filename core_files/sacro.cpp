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
         << "\nLvFede: " << getLvFede()
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
         << "\nLvFede: " << getLvFede()
         << "\nAtt per Turno: " << getAtt()
         << endl;
}

int sacro::getLvFede() const { return lvFede; }
int sacro::getlimitBreak() const { return limitbreak; }

void sacro::setLimit(){
  limitbreak = 0; //resetta la limitbreak
  limitBar.resize(1); //resetta la limitbar
}

bool sacro::checkLimit() {
  if (limitbreak < 50)
    return false;
  else{
    limitbreak = 0; //reset limit
    return true;
  }
}

double sacro::getHit() { /*si collega all'interfaccia grafica*/
  if (getProbHit() > 80) {
    incrementaHit();
    return this->calcolaDanno();
  }
  incrementaMiss();
  //updateLimitbreak();
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
    nDanni = nDanni * 33; //valore simbolico
    cout << "Hai superato la limit fai un mega danno" << endl;
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
    limitBar.push_back(limitbreak);
}


vector<int> sacro::getValoriLimitBar() const{
  return limitBar;
}

bool sacro::toXML(const std::string& filename) const {
  std::ofstream file(filename);
  if(!file.is_open()){
    return false;
  }

  file << "<sacro>\n";
  file << "  <nome>" << getNome() << "</nome>\n";
  file << "  <danno_base>" << getDanno() << "</danno_base>\n";
  file << "  <numero_turni>" << getAttacchiPerTurno().size() << "</numero_turni>\n";
  file << "  <attacchi_per_turno>" << getAtt() << "</attacchi_per_turno>\n";
  file << "  <lvFede>" << getLvFede() << "</lvFede>\n";
  file << "  <limitbreak>" << getlimitBreak() << "</limitbreak>\n";
  file << "  <hit>" << getNHit() << "</hit>\n";
  file << "  <miss>" << getNMiss() << "</miss>\n";
  file << "  <danno_massimo>" << getMaxDanno() << "</danno_massimo>\n";
  file << "  <hit_rate>" << getHitRate() << "</hit_rate>\n";

  file << "  <danni_per_turno>\n";
  for (const auto& danno : getRecordDanniPerTurno()) {
    file << "    <danno>" << danno << "</danno>\n";
  }
  file << "  </danni_per_turno>\n";

  file << "  <limitBar>\n";
  for (const auto& limit : getValoriLimitBar()) {
    file << "    <limit>" << limit << "</limit>\n";
  }
  file << "  </limitBar>\n";

  file << "</sacro>\n";

  file.close();
  return true;
}

void sacro::accept(Visitor* v){
  v->visitSacro(this);
}
/*
bool sacro::fromXML(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Errore nell'aprire il file XML." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        string tag, value;
        
        if (line.find("<nome>") != string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            setNome(value);
        } else if (line.find("<danno_base>") != string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            setDanno(std::stod(value));
        } else if (line.find("<lvFede>") != string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            lvFede = std::stoi(value);
        } else if (line.find("<limitbreak>") != string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            limitbreak = std::stoi(value);
        } else if (line.find("<limit>") != string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            limitBar.push_back(std::stoi(value));
        } else if (line.find("<danno>") != string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            getRecordDanniPerTurno().push_back(std::stod(value));
        }
    }

    file.close();
    return true;
}
*/

void sacro::setLvFede(int lvFede){
  this->lvFede = lvFede;
}