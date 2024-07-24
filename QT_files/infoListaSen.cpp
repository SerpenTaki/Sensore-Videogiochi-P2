#include "infoListaSen.h"

infoListaSen::infoListaSen(QWidget* parent = 0)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    nome_sensore = new QLabel("Nome: sensore");
    tipo_sensore = new QLabel("TIPO: fisico ex");

    layout->addWidget(nome_sensore);
    layout->addWidget(tipo_sensore);
}

void infoListaSen::show(){
    
}