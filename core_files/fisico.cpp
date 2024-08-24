#include "headers/fisico.h"

fisico::fisico(string n, double d, int nT, int nA, int aff)
: sensoreDanno(n, d, nT, nA), affilatura(aff) {
  if(getNome().empty()){
    std::cerr << "Oggetto non creato, nome vuoto" << endl;
    return;
  }
  cout << "Oggetto fisico Creato" << endl;
  setSizeAttacchiPerTurno();
   cout << "Nome: " << getNome() 
         << "\nDanno Base: " << getDanno() 
         << "\nNTurni: " << getAttacchiPerTurno().size()
         << "\nAff: " << affilatura 
         << "\nAtt per Turno: " << getAtt()
         << endl;
}

fisico::fisico(string n, double d, int nT, int nA, vector<double> rDPT, int aff)
: sensoreDanno(n, d, nT, nA, rDPT), affilatura(aff) {
  if(getNome().empty()){
    std::cerr << "Oggetto non creato, nome vuoto" << endl;
    return;
  }
  cout << "Oggetto fisico Importato" << endl;
  setSizeAttacchiPerTurno();
   cout << "Nome: " << getNome() 
         << "\nDanno Base: " << getDanno() 
         << "\nNTurni: " << getAttacchiPerTurno().size()
         << "\nAff: " << affilatura 
         << "\nAtt per Turno: " << getAtt()
         << endl;
}

int fisico::getAffilatura() const { return affilatura; }

double fisico::getHit() { /*si collega all'interfaccia grafica*/
  if (getProbHit() > 30) {
    return this->calcolaDanno();
  }
  return 0.0;
}

double fisico::calcolaDanno() { // assestante
  double nDanni = getDanno();
  nDanni = nDanni * affilatura / 10;
  if (getProbCrit() > 75) {
    nDanni = (nDanni * 30) / 100;
    return nDanni;
  } else
    return nDanni;
}

bool fisico::toXML(const std::string& filename) const {
    std::ofstream file(filename);  // Apertura del file in modalità scrittura
    if (!file.is_open()) {         // Controllo se il file è stato aperto correttamente
        return false;              // Restituisce false se il file non è stato aperto
    }

    file << "<fisico>\n";
    file << "  <nome>" << getNome() << "</nome>\n";
    file << "  <danno_base>" << getDanno() << "</danno_base>\n";
    file << "  <numero_turni>" << getAttacchiPerTurno().size() << "</numero_turni>\n";
    file << "  <affilatura>" << affilatura << "</affilatura>\n";
    file << "  <attacchi_per_turno>" << getAtt() << "</attacchi_per_turno>\n";
    
       // Aggiunta dei dati del vettore recordDanniPerTurno
    file << "  <danni_per_turno>\n";
    for (const auto& danno : getRecordDanniPerTurno()) {
        file << "    <danno>" << danno << "</danno>\n";
    }
    file << "  </danni_per_turno>\n";


    file << "</fisico>";

    file.close();  // Chiudi il file dopo aver scritto
    return true;   // Restituisce true per indicare il successo dell'operazione
}

bool fisico::fromXML(const std::string& filename) {
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
        } else if (line.find("<affilatura>") != std::string::npos) {
            value = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
            affilatura = std::stoi(value);
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


void fisico::accept(Visitor* v) {
  v->visitFisico(this);
}