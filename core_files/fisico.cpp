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

string fisico::toXML() const{
  std::ostringstream oss;
  oss << "<fisico>\n";
  oss << "  <nome>" << getNome() << "</nome>\n";
  oss << "  <danno_base>" << getDanno() << "</danno_base>\n";
  oss << "  <numero_turni>" << getAttacchiPerTurno().size() << "</numero_turni>\n";
  oss << "  <affilatura>" << affilatura << "</affilatura>\n";
  oss << "  <attacchi_per_turno>" << getAtt() << "</attacchi_per_turno>\n";
    
  // Aggiungiamo i dati del vettore rDPT (se esiste)
  oss << "  <danni_per_turno>\n";
  for (const auto& danno : getAttacchiPerTurno()) {
      oss << "    <danno>" << danno << "</danno>\n";
  }
  oss << "  </danni_per_turno>\n";

  oss << "</fisico>";
  return oss.str();
}

void fisico::accept(Visitor* v) {
  v->visitFisico(this);
}