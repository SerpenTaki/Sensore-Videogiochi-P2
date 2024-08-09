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
/*
void content::aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore) {
    QLabel* nuovoSensoreLabel = new QLabel("Sensore creato: " + QString::fromStdString(nuovoSensore->getNome()), this);
    ContentVisitor RobertoBenigni;
    nuovoSensore->accept(RobertoBenigni);
    center->addWidget(nuovoSensoreLabel);
    center->addWidget(RobertoBenigni.returnQWidget());
    
    // Aggiorna il contenuto visualizzato
    selectedSensore = QString::fromStdString(nuovoSensore->getNome());
}*/

QString content::getSelectedSensore() const {
    return selectedSensore;
}
/*
void content::aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore) {
    QLabel* nuovoSensoreLabel = new QLabel("Sensore creato: " + QString::fromStdString(nuovoSensore->getNome()), this);
    ContentVisitor RobertoBenigni;
    nuovoSensore->accept(RobertoBenigni);
    center->addWidget(nuovoSensoreLabel);
    center->addWidget(RobertoBenigni.returnQWidget());
    
    // Aggiorna il contenuto visualizzato
    selectedSensore = QString::fromStdString(nuovoSensore->getNome());
}*/

void content::aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore) {
    if (!nuovoSensore) {
        // Gestisci il caso in cui il sensore è nullo
        return;
    }

    // Creazione e aggiunta dell'etichetta per il sensore
    QLabel* nuovoSensoreLabel = new QLabel("Sensore creato: " + QString::fromStdString(nuovoSensore->getNome()), this);
    center->addWidget(nuovoSensoreLabel);

    // Creazione del visitor
    ContentVisitor* visitor = new ContentVisitor();
    nuovoSensore->accept(visitor);  // Passa il visitor al sensore

    // Aggiungi il widget ottenuto dal visitor al layout
    QWidget* visitorWidget = visitor->returnQWidget();
    if (visitorWidget) {
        center->addWidget(visitorWidget);
    }

    // Aggiorna il contenuto visualizzato
    selectedSensore = QString::fromStdString(nuovoSensore->getNome());

    // Non dimenticare di deallocare il visitor se non lo usi più
    delete visitor;
}



