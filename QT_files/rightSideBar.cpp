#include "headers/rightSideBar.h"
#include "headers/modificaSensore.h"


rightSideBar::rightSideBar(content* c, leftSideBar* l, QWidget* parent)
    : QWidget(parent), cont(c), leftSide(l) {
    right = new QVBoxLayout(this);
    avviaSimulaButt = new QPushButton("Avvia Simulazione", this);
    modificaSensButt = new QPushButton("Modifica Sensore", this);
    eliminaSensButt = new QPushButton("Elimina Sensore", this);
    right->addWidget(avviaSimulaButt);
    right->addWidget(modificaSensButt);
    right->addWidget(eliminaSensButt);

    connect(avviaSimulaButt, &QPushButton::clicked, [this]() {
        sensoreDanno* sensor = cont->getSelectedSensore(); 
        if (sensor) {
            cont->avviaSimulazione(sensor);
            cont->displayVector(sensor); 
        } else {
            QMessageBox::warning(this, "Errore", "Nessun sensore selezionato per la simulazione.");
        }
    });
    connect(modificaSensButt, &QPushButton::clicked, this, &rightSideBar::modificaSensore);
    connect(eliminaSensButt, &QPushButton::clicked, this, &rightSideBar::eliminaSensore);
}

void rightSideBar::modificaSensore() {
    sensoreDanno* sensore = cont->getSelectedSensore();
    if (sensore) {
        class modificaSensore dialog(this, sensore); 
        if (dialog.exec() == QDialog::Accepted) {
            cout << "Log di modifica" << endl;
            cont->aggiungiSensoreAlContenuto(sensore->getNome());  
        }
    } else {
        QMessageBox::warning(this, "Errore", "Nessun sensore selezionato per la modifica.");
    }
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
            leftSide->eliminaSensore(sensore->getNome());
            cont->eliminaSensore(sensore);
        }
    } else {
        QMessageBox::warning(this, "Errore", "Nessun sensore selezionato per l'eliminazione.");
    }
}


void rightSideBar::avviaSimulazione() {
  //  cont->mostraGraficoSensore();
}
