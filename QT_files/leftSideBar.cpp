#include"headers/leftSideBar.h"

leftSideBar::leftSideBar(QWidget* parent)
: QWidget(parent){
    left = new QVBoxLayout(this);
    aggiungiSensoreBottone = new QPushButton("Aggiungi Sensore");
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Cerca sensore..."); // Placeholder per la search box
    left->addWidget(searchBox);
    left->addWidget(aggiungiSensoreBottone);
    connect(aggiungiSensoreBottone, &QPushButton::clicked, this, &leftSideBar::stampaSelSensore);
    connect(searchBox, &QLineEdit::textChanged, this, &leftSideBar::eseguiRicerca);
}

void leftSideBar::stampaSelSensore(){
    QLabel* testo = new QLabel("Specifica il tipo di sensore");
    testo->show();
}

void leftSideBar::eseguiRicerca(const QString& text){ //DA FARE
    // Logica di ricerca qui
    // Ad esempio, puoi filtrare una lista di sensori o aggiornare un display basato sul testo
    qDebug() << "Ricerca: " << text;
}