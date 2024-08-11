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
    QString sensoreName = cont->getSelectedSensore();
    leftSide->eliminaSensore(sensoreName);
    cont->eliminaSensore(sensoreName);
}

void rightSideBar::avviaSimulazione() {
    cont->mostraGraficoSensore();
}
