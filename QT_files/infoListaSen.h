#ifndef INFOLISTASEN_H
#define INFOLISTASEN_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QApplication>

class infoListaSen: public QWidget{
private:
    QLabel* nome_sensore;
    QLabel* tipo_sensore;
public:
    infoListaSen(QWidget* parent = 0);

    void show();
};


#endif