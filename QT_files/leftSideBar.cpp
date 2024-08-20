#include "headers/leftSideBar.h"

leftSideBar::leftSideBar(content* contentWidget, QWidget* parent)
    : QWidget(parent) {
    left = new QVBoxLayout(this);
    this->contentWidget = contentWidget;

    aggiungiSensoreBottone = new QPushButton("Aggiungi Sensore");
    importaSensoreBottone = new QPushButton("Importa Sensore");
    salvaSensoreBottone = new QPushButton("Salva Sensore");
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Cerca sensore...");
    sensoreList = new vector<sensoreDanno*>; // Inizializza la lista dei sensori
    sensoreListLabel = new QListWidget();


    left->addWidget(searchBox);
    left->addWidget(aggiungiSensoreBottone);
    left->addWidget(importaSensoreBottone);
    left->addWidget(sensoreListLabel);
    left->addWidget(salvaSensoreBottone);

    connect(aggiungiSensoreBottone, &QPushButton::clicked, this, &leftSideBar::stampaSelSensore);
    connect(searchBox, &QLineEdit::textChanged, this, &leftSideBar::eseguiRicerca);
    connect(sensoreListLabel, &QListWidget::itemClicked, [=](QListWidgetItem* item) {
        vector<sensoreDanno*>::iterator i;
        for(i = sensoreList->begin(); i != sensoreList->end(); ++i){
            if(QString::fromStdString((*i)->getNome()) == item->text()){
                emit sensoreSelezionato(*i);
            }
        }
    });

    
}

void leftSideBar::stampaSelSensore() { //fa apparire la selezione del sensore
    aggiungiSensore* dialog = new aggiungiSensore(this);

    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, this, &leftSideBar::aggiungiSensoreToList);
    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, contentWidget, &content::aggiungiSensoreAlContenuto);

    dialog->exec(); // Mostra il dialogo come modale
}

void leftSideBar::aggiungiSensoreToList(sensoreDanno* sensore) {
    sensoreList->push_back(sensore);
    sensoreListLabel->addItem(QString::fromStdString(sensore->getNome()));

}

void leftSideBar::eseguiRicerca(const QString& text) {
    for (int i = 0; i < sensoreListLabel->count(); ++i) {
        QListWidgetItem* item = sensoreListLabel->item(i);
        item->setHidden(!item->text().contains(text, Qt::CaseInsensitive));
    }
}

void leftSideBar::eliminaSensore(sensoreDanno* sensore) {
    QList<QListWidgetItem*> items = sensoreListLabel->findItems(QString::fromStdString(sensore->getNome()), Qt::MatchExactly);
    if (!items.empty()) {
        delete items.first();  // Rimuovi l'elemento dalla QListWidget
        for(vector<sensoreDanno*>::iterator i = sensoreList->begin(); i != sensoreList->end(); ++i){
            if((*i)->getNome() == sensore->getNome()){
                sensoreList->erase(i);
                i--;
            }
        }
    }
}




