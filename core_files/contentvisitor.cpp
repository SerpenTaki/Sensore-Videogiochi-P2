#include"headers/contentvisitor.h"

ContentVisitor::ContentVisitor() {}

ContentVisitor::~ContentVisitor() {
    delete dispWidget;
}

void ContentVisitor::visitFisico(fisico* f){
    dispWidget = new QLabel("Sensore Fisico \nNome:\t\t\t" + QString::fromStdString(f->getNome()) +
     "\nDannoBase:\t\t" + QString::number(f->getDanno()) +
     "\nNumero di Turni:\t\t" + QString::number(f->getNTurni()) +
     "\nAttacchi per Turno:\t" + QString::number(f->getAtt()) + 
     "\nAffilatura:\t\t" + QString::number(f->getAffilatura()) + "%");
}

void ContentVisitor::visitMagico(magico* m){
    dispWidget = new QLabel("Sensore Magico \nNome:\t\t\t" + QString::fromStdString(m->getNome()) +
     "\nDannoBase:\t\t" + QString::number(m->getDanno()) +
     "\nNumero di Turni:\t\t" + QString::number(m->getNTurni()) +
     "\nAttacchi per Turno:\t" + QString::number(m->getAtt()) + 
     "\nLivello Magia:\t\t" + QString::number(m->getLvMagia()) +
     "\nCondizione:\t\t" + (m->checkCondition() ? "Si" : "No"));
}

void ContentVisitor::visitSacro(sacro* s){
    dispWidget = new QLabel("Sensore Sacro \nNome:\t\t\t" + QString::fromStdString(s->getNome()) +
     "\nDannoBase:\t\t" + QString::number(s->getDanno()) +
     "\nNumero di Turni:\t\t" + QString::number(s->getNTurni()) +
     "\nAttacchi per Turno:\t" + QString::number(s->getAtt()) + 
     "\nLivello Fede:\t\t" + QString::number(s->getLvFede()) +
     "\nValore Limit:\t\t" + QString::number(s->getlimitBreak()));
}

QWidget* ContentVisitor::returnQWidget() {
    return dispWidget;
}