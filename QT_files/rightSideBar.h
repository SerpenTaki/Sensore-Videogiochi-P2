#ifndef RIGHTSIDEBAR_H
#define RIGHTSIDEBAR_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QApplication>

#include"content.h"

class rightSideBar: public QWidget{
private:
    QVBoxLayout* right;
    QPushButton* avviaSimulaButt;
    QPushButton* modificaSensButt;
    QPushButton* eliminaSensButt;
    content* cont;
public:
    rightSideBar(content* c,QWidget* parent = nullptr): QWidget(parent), cont(c){
        right = new QVBoxLayout(this);
        avviaSimulaButt = new QPushButton("Avvia Simulazione");
        modificaSensButt = new QPushButton("Modifica Sensore");
        eliminaSensButt = new QPushButton("Elimina Sensore");
        right->addWidget(avviaSimulaButt);
        right->addWidget(modificaSensButt);
        right->addWidget(eliminaSensButt);

        if (cont) {
            connect(avviaSimulaButt, &QPushButton::clicked, cont, &content::avviaSimulazione);
            connect(eliminaSensButt, &QPushButton::clicked, cont, &content::eliminaSensore);
        }
        
        connect(modificaSensButt, &QPushButton::clicked, this, &rightSideBar::modificaSensore);
    }
public slots:
    void modificaSensore(){
        QLabel* testoModifica = new QLabel("Modifica Sensore");
        testoModifica->show();
    }
};

#endif