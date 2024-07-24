#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QApplication>

class leftSideBar: public QWidget{
private:
    QVBoxLayout* left;
    QPushButton* aggiungiSensoreBottone;
public:
    leftSideBar(QWidget* parent = nullptr): QWidget(parent){
        left = new QVBoxLayout(this);
        aggiungiSensoreBottone = new QPushButton("Aggiungi Sensore");
        //aggiungiSensoreBottone->setFixedSize(200, 100);  // Imposta la dimensione fissa del bottone (larghezza, altezza)
        left->addWidget(aggiungiSensoreBottone);
        connect(aggiungiSensoreBottone, &QPushButton::clicked, this, &leftSideBar::stampaSelSensore);
    }

    QVBoxLayout* getLeftLayout() { return left; }

public slots:
    void stampaSelSensore(){
        QLabel* testo = new QLabel("Specifica il tipo di sensore");
        testo->show();
    }
};


#endif