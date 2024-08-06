#include "headers/leftSideBar.h"

leftSideBar::leftSideBar(QWidget* parent)
: QWidget(parent) {
    left = new QVBoxLayout(this);
    aggiungiSensoreBottone = new QPushButton("Aggiungi Sensore");
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Cerca sensore...");
    sensoreList = new QListWidget(); // Inizializza la lista dei sensori

    left->addWidget(searchBox);
    left->addWidget(aggiungiSensoreBottone);
    left->addWidget(sensoreList); // Aggiungi la lista al layout

    connect(aggiungiSensoreBottone, &QPushButton::clicked, this, &leftSideBar::stampaSelSensore);
    connect(searchBox, &QLineEdit::textChanged, this, &leftSideBar::eseguiRicerca);
    connect(sensoreList, &QListWidget::itemClicked, [=](QListWidgetItem* item) {
        emit sensoreSelezionato(item->text());
    });
}
/*
void leftSideBar::stampaSelSensore() {
    aggiungiSensore* dialog = new aggiungiSensore(this);
    connect(dialog->conferma, &QPushButton::clicked, [=]() {
        QString nomeSensore = dialog->nomeSensoreInserimento->text();
        aggiungiSensoreToList(nomeSensore);
        emit sensoreAggiunto(nomeSensore); // Emetti il segnale quando un sensore è aggiunto
        dialog->accept(); // Chiudi il dialogo
    });
    dialog->exec(); // Mostra il dialogo
}*/

void leftSideBar::stampaSelSensore() {
    // Crea e mostra la finestra di dialogo per aggiungere un sensore
    aggiungiSensore* dialog = new aggiungiSensore(this);
    
    // Connetti il segnale del dialogo per aggiungere sensore
    connect(dialog, &aggiungiSensore::sensoreAggiunto, this, &leftSideBar::aggiungiSensoreToList);
    
    dialog->exec(); // Mostra il dialogo come modale
}

void leftSideBar::aggiungiSensoreToList(const QString& sensoreName) {
    sensoreList->addItem(sensoreName);
    sensori.append(sensoreName); // Aggiungi il sensore alla lista per la ricerca
}

void leftSideBar::eseguiRicerca(const QString& text) {
    for (int i = 0; i < sensoreList->count(); ++i) {
        QListWidgetItem* item = sensoreList->item(i);
        item->setHidden(!item->text().contains(text, Qt::CaseInsensitive));
    }
}
