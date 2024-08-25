#include "headers/magico.h"

magico::magico(string n, double d, int nT, int nA, int lvM, bool isInSta)
: sensoreDanno(n, d, nT, nA), lvMagia(lvM), isInStatus(isInSta) {
  if(getNome().empty()){
    std::cerr << "Oggetto non creato, nome vuoto" << endl;
    return;
  }
  cout << "Oggetto magico creato" << endl;
    setSizeAttacchiPerTurno();
   cout << "Nome: " << getNome() 
         << "\nDanno Base: " << getDanno() 
         << "\nNTurni: " << getAttacchiPerTurno().size()
         << "\nlvMagia: " << getLvMagia()
         << "\nisInSta: " << checkCondition()
         << "\nAtt per Turno: " << getAtt()
         << endl;
}

magico::magico(string n, double d, int nT, int nA, vector<double> rDPT, int lvM, bool isInSta)
: sensoreDanno(n, d, nT, nA, rDPT), lvMagia(lvM), isInStatus(isInSta) {
  if(getNome().empty()){
    std::cerr << "Oggetto non creato, nome vuoto" << endl;
    return;
  }
  cout << "Oggetto magico Importato" << endl;
    setSizeAttacchiPerTurno();
   cout << "Nome: " << getNome() 
         << "\nDanno Base: " << getDanno() 
         << "\nNTurni: " << getAttacchiPerTurno().size()
         << "\nlvMagia: " << getLvMagia()
         << "\nisInSta: " << checkCondition()
         << "\nAtt per Turno: " << getAtt()
         << endl;
}

int magico::getLvMagia() const { return lvMagia; }

bool magico::checkCondition() const { return isInStatus; }

double magico::getHit() {
  if (getProbHit() > 45) {
    return calcolaDanno();
  }
  return 0.0;
}

double magico::calcolaDanno() {
  double nDanni = getDanno();
  nDanni = nDanni + ((getLvMagia() / 2) * 2);
  if (checkCondition()) {
    nDanni = nDanni + nDanni * 0.3;
    if (getProbCrit() > 85) {
      nDanni = (nDanni * 20) / 100;
    }
    return nDanni;
  }
  setStatus();
  return nDanni;
}

string magico::setStatus() {
  if (getRand() > 70) {
    //checkCondition() = true; //da sistemare
    return "incantato";
  }
  else
    return "nope";
}

bool magico::toXML(const std::string& filename) const{
  std::ofstream file(filename);
  if (!file.is_open()){
    return false;
  }

  file << "<magico>\n";
  file << "  <nome>" << getNome() << "</nome>\n";
  file << "  <danno_base>" << getDanno() << "</danno_base>\n";
  file << "  <numero_turni>" << getAttacchiPerTurno().size() << "</numero_turni>\n";
  file << "  <livello_magia>" << getLvMagia() << "</livello_magia>\n";
  file << "  <status>" << checkCondition() << "</status>\n";
  file << "  <attacchi_per_turno>" << getAtt() << "</attacchi_per_turno>\n";
    
  // Aggiungiamo i dati del vettore rDPT (se esiste)
  file << "  <danni_per_turno>\n";
  for (const auto& danno : getRecordDanniPerTurno()) {
      file << "    <danno>" << danno << "</danno>\n";
  }
  file << "  </danni_per_turno>\n";

  file << "</magico>";
  
  file.close();
  return true;
}

bool magico::fromXML(const std::string& filename) {
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
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            setNome(value);
        } else if (line.find("<danno_base>") != std::string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            setDanno(std::stod(value));
        } else if (line.find("<numero_turni>") != std::string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            setNTurni(std::stoi(value));
        } else if (line.find("<livello_magia>") != std::string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            lvMagia = std::stoi(value);
        } else if (line.find("<status>") != std::string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            isInStatus = (value == "true");
        } else if (line.find("<attacchi_per_turno>") != std::string::npos) {
            // Assuming attacchi_per_turno is a single integer value; otherwise, you would need a different approach.
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            setAttacchiPerTurno({std::stoi(value)});
        } else if (line.find("<danno>") != std::string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            getRecordDanniPerTurno().push_back(std::stod(value));
        }
    }

    file.close();
    return true;
}


void magico::accept(Visitor* v){
  v->visitMagico(this);
}


  void magico::setLvMagia(int lvM){
    lvMagia = lvM;
  }

  void magico::setTheStatus(bool isInSta){
    isInStatus = isInSta;
  }