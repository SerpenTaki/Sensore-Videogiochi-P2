#include"headers/contentvisitor.h"

ContentVisitor::ContentVisitor() {}

ContentVisitor::~ContentVisitor() {
    delete dispWidget;
}

void ContentVisitor::visitFisico(fisico* f){
    dispWidget = new QLabel("Sensore Fisico \n\nNome:\t" + QString::fromStdString(f->getNome()) +
     "\n\nDannoBase:\t" + QString::number(f->getDanno()) +
     "\n\nNumero di Turni:\t" + QString::number(f->getNTurni()) +
     "\n\nAttacchi per Turno:\t" + QString::number(f->getAtt()) + 
     "\n\nAffilatura:\t" + QString::number(f->getAffilatura()) + "%");
}

void ContentVisitor::visitMagico(magico* m){
    dispWidget = new QLabel("Sensore Magico \n\nNome:\t" + QString::fromStdString(m->getNome()) +
     "\n\nDannoBase:\t" + QString::number(m->getDanno()) +
     "\n\nNumero di Turni:\t" + QString::number(m->getNTurni()) +
     "\n\nAttacchi per Turno:\t" + QString::number(m->getAtt()) + 
     "\n\nLivello Magia:\t" + QString::number(m->getLvMagia()) +
     "\n\nCondizione:\t" + (m->checkCondition() ? "Si" : "No"));
}

void ContentVisitor::visitSacro(sacro* s){
    dispWidget = new QLabel("Sensore Sacro \nNome:\t" + QString::fromStdString(s->getNome()) +
     "\n\nDannoBase:\t" + QString::number(s->getDanno()) +
     "\n\nNumero di Turni:\t" + QString::number(s->getNTurni()) +
     "\n\nAttacchi per Turno:\t" + QString::number(s->getAtt()) + 
     "\n\nLivello Fede:\t" + QString::number(s->getLvFede()) +
     "\n\nValore Limit:\t" + QString::number(s->getlimitBreak()));
}

QWidget* ContentVisitor::returnQWidget() {
    return dispWidget;
}