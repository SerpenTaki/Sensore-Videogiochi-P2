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

void content::visualizzaSensore(const QString& sensoreName) {
    // Pulisci la visualizzazione corrente
    QLayoutItem* item;
    while ((item = layout()->takeAt(0)) != 0) {
        delete item->widget();
        delete item;
    }

    // Mostra i dettagli del sensore selezionato
    QLabel* nomeLabel = new QLabel("Nome Sensore: " + sensoreName);
    QLabel* tipoLabel = new QLabel("Tipo:");
    
    layout()->addWidget(nomeLabel);
    layout()->addWidget(tipoLabel);
    setLayout(layout());
}