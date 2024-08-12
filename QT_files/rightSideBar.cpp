#include "headers/rightSideBar.h"

rightSideBar::rightSideBar(content* c, leftSideBar* l, QWidget* parent)
    : QWidget(parent), cont(c), leftSide(l) {
    right = new QVBoxLayout(this);
    avviaSimulaButt = new QPushButton("Avvia Simulazione", this);
    modificaSensButt = new QPushButton("Modifica Sensore", this);
    eliminaSensButt = new QPushButton("Elimina Sensore", this);
    right->addWidget(avviaSimulaButt);
    right->addWidget(modificaSensButt);
    right->addWidget(eliminaSensButt);

    connect(avviaSimulaButt, &QPushButton::clicked, this, &rightSideBar::avviaSimulazione);
    connect(modificaSensButt, &QPushButton::clicked, this, &rightSideBar::modificaSensore);
    connect(eliminaSensButt, &QPushButton::clicked, this, &rightSideBar::eliminaSensore);
}

void rightSideBar::modificaSensore() {
    QLabel* testoModifica = new QLabel("Modifica Sensore");
    testoModifica->show();
}

void rightSideBar::eliminaSensore() {
    sensoreDanno* sensore = cont->getSelectedSensore();
    if (sensore) {
        // Chiedi conferma all'utente
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Eliminazione Sensore", 
                                      "Sei sicuro di voler eliminare il sensore " + QString::fromStdString(sensore->getNome()) + "?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // Elimina il sensore dal contenuto
            cont->eliminaSensore(sensore);
            // Rimuovi il sensore dalla lista di sinistra
            leftSide->eliminaSensore(sensore);
        }
    } else {
        QMessageBox::warning(this, "Errore", "Nessun sensore selezionato per l'eliminazione.");
    }
}


void rightSideBar::avviaSimulazione() {
  //  cont->mostraGraficoSensore();
}
