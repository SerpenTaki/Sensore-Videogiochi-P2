#include"headers/content.h"

content::content(QWidget* parent)
: QWidget(parent) {
    center = new QVBoxLayout(this);
    grafichino = new QLabel("Mostra qui il grafico");
    center->addWidget(grafichino);
}

void content::avviaSimulazione() {
    sim = new QLabel("Simulazione Avviata");
    center->addWidget(sim);
}

void content::eliminaSensore() {
    // Logica per eliminare i sensori
}

void content::aggiornaContenuto(const QString& sensoreName) {
    // Mostra il sensore aggiunto nel widget content
    QLabel* nuovoSensore = new QLabel("Sensore creato: " + sensoreName);
    center->addWidget(nuovoSensore);
}
