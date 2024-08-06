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

    connect(avviaSimulaButt, &QPushButton::clicked, cont, &content::avviaSimulazione);
    connect(modificaSensButt, &QPushButton::clicked, this, &rightSideBar::modificaSensore);
    connect(eliminaSensButt, &QPushButton::clicked, this, &rightSideBar::eliminaSensore);
}

void rightSideBar::modificaSensore() {
    QLabel* testoModifica = new QLabel("Modifica Sensore");
    testoModifica->show();
}

void rightSideBar::eliminaSensore() {
    // Ottieni il sensore selezionato dal contenuto
    QString sensoreName = cont->getSelectedSensore(); // Aggiungi un metodo in content per ottenere il sensore selezionato
    leftSide->eliminaSensore(sensoreName);
    cont->eliminaSensore(sensoreName); // Aggiungi un metodo in content per eliminare il sensore
}
