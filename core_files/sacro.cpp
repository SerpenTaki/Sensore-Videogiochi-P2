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
    nDanni = nDanni * 33; //valore simbolico
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
  file << "  <lvFede>" << getLvFede() << "</lvFede>\n";
  file << "  <limitbreak>" << getlimitBreak() << "</limitbreak>\n";

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


#include <fstream>
#include <sstream>
#include <iostream>
#include "sacro.h"

bool sacro::fromXML(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Errore nell'aprire il file XML." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string tag, value;
        
        if (line.find("<nome>") != std::string::npos) {
            tag = "nome";
            value = line.substr(line.find("<" + tag + ">") + tag.size() + 2, line.find("</" + tag + ">") - tag.size() - 2);
            setNome(value);
        } else if (line.find("<danno_base>") != std::string::npos) {
            tag = "danno_base";
            value = line.substr(line.find("<" + tag + ">") + tag.size() + 2, line.find("</" + tag + ">") - tag.size() - 2);
            setDanno(std::stod(value));
        } else if (line.find("<lvFede>") != std::string::npos) {
            tag = "lvFede";
            value = line.substr(line.find("<" + tag + ">") + tag.size() + 2, line.find("</" + tag + ">") - tag.size() - 2);
            lvFede = std::stoi(value);
        } else if (line.find("<limitbreak>") != std::string::npos) {
            tag = "limitbreak";
            value = line.substr(line.find("<" + tag + ">") + tag.size() + 2, line.find("</" + tag + ">") - tag.size() - 2);
            limitbreak = std::stoi(value);
        } else if (line.find("<limit>") != std::string::npos) {
            tag = "limit";
            value = line.substr(line.find("<" + tag + ">") + tag.size() + 2, line.find("</" + tag + ">") - tag.size() - 2);
            limitBar.push_back(std::stoi(value));
        } else if (line.find("<danno>") != std::string::npos) {
            tag = "danno";
            value = line.substr(line.find("<" + tag + ">") + tag.size() + 2, line.find("</" + tag + ">") - tag.size() - 2);
            recordDanniPerTurno.push_back(std::stod(value));
        }
    }

    file.close();
    return true;
}
