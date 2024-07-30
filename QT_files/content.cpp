#include"headers/content.h"

content::content(QWidget* parent)
: QWidget(parent){
    center = new QVBoxLayout(this);
    grafichino = new QLabel("Mostra qui il grafico");
    center->addWidget(grafichino);
}

void content::avviaSimulazione(){
        /* UTILE
    if (sensoreWidget) {
        sensoreWidget->deleteLater(); // Rimuove il widget esistente prima di crearne uno nuovo
    }
    sensoreWidget = new aggiungiSensore(this); // Crea un nuovo widget
    left->addWidget(sensoreWidget); // Aggiungilo al layout*/
    if(sim){
        sim->deleteLater(); 
    }
    sim = new QLabel("Simulazione Avviata");
    center->addWidget(sim);
}

void content::eliminaSensore(){ // Da sistemare
       /* QLayoutItem* item;
        while ((item = center->takeAt(0))) {
        QWidget* widget = item->widget();
        if (widget) {
            widget->deleteLater(); // Rimuove e pianifica la cancellazione del widget
        }
        delete item; // Rimuove l'elemento di layout
        QLabel* messaggioRimozione = new QLabel("Sensore Rimosso");
        center->addWidget(messaggioRimozione);
        }*/ //Buggata da sistemare
}