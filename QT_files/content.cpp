#include "headers/content.h"

content::content(QWidget* parent)
    : QWidget(parent), selectedSensore("") {
    center = new QVBoxLayout(this);
    grafichino = new QLabel("Mostra qui il grafico", this);
    center->addWidget(grafichino);
}

void content::avviaSimulazione() {
    sim = new QLabel("Simulazione Avviata", this);
    center->addWidget(sim);
}

void content::eliminaSensore(const QString& sensoreName) {
    // Pulisci la visualizzazione corrente
    QLayoutItem* item;
    while ((item = center->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    // Elimina il sensore selezionato se corrisponde a quello specificato
    if (selectedSensore == sensoreName) {
        selectedSensore = "";
    }
}

void content::aggiornaContenuto(const QString& sensoreName) {
    // Mostra il sensore aggiunto nel widget content
    QLabel* nuovoSensore = new QLabel("Sensore creato: " + sensoreName, this);
    center->addWidget(nuovoSensore);
}

void content::visualizzaSensore(const QString& sensoreName) {
    // Pulisci la visualizzazione corrente
    QLayoutItem* item;
    while ((item = center->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    // Mostra i dettagli del sensore selezionato
    QLabel* nomeLabel = new QLabel("Nome Sensore: " + sensoreName, this);
    QLabel* tipoLabel = new QLabel("Tipo:", this);
    center->addWidget(nomeLabel);
    center->addWidget(tipoLabel);
    selectedSensore = sensoreName; // Aggiorna il sensore selezionato
}

QString content::getSelectedSensore() const {
    return selectedSensore;
}
