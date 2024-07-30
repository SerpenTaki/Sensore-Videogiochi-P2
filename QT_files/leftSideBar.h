#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QDebug>

class leftSideBar: public QWidget{
private:
    QVBoxLayout* left;
    QPushButton* aggiungiSensoreBottone;
    QLineEdit* searchBox;
public:
    leftSideBar(QWidget* parent = nullptr): QWidget(parent){
        left = new QVBoxLayout(this);
        aggiungiSensoreBottone = new QPushButton("Aggiungi Sensore");
        searchBox = new QLineEdit();
        searchBox->setPlaceholderText("Cerca sensore..."); // Placeholder per la search box
        left->addWidget(searchBox);
        left->addWidget(aggiungiSensoreBottone);
        connect(aggiungiSensoreBottone, &QPushButton::clicked, this, &leftSideBar::stampaSelSensore);
        connect(searchBox, &QLineEdit::textChanged, this, &leftSideBar::eseguiRicerca);
    }

public slots:
    void stampaSelSensore(){
        QLabel* testo = new QLabel("Specifica il tipo di sensore");
        testo->show();
    }

    void eseguiRicerca(const QString& text){ //DA FARE
        // Logica di ricerca qui
        // Ad esempio, puoi filtrare una lista di sensori o aggiornare un display basato sul testo
        qDebug() << "Ricerca: " << text;
    }
};


#endif