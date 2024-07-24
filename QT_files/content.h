#ifndef CONTENT_H   
#define CONTENT_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QApplication>

class content: public QWidget{
private:
    QVBoxLayout* center;
    QLabel* grafichino;
public:
    content(QWidget* parent = nullptr): QWidget(parent){
        center = new QVBoxLayout(this);
        grafichino = new QLabel("Mostra qui il grafico");
        center->addWidget(grafichino);
    }
public slots:
    void avviaSimulazione(){
        QLabel* sim = new QLabel("Simulazione Avviata");
        center->addWidget(sim);
    }

    void eliminaSensore(){ // Da sistemare
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
};


#endif