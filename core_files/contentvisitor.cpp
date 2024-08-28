#include"headers/contentvisitor.h"

ContentVisitor::ContentVisitor() {}

ContentVisitor::~ContentVisitor() {
    delete dispWidget;
}

void ContentVisitor::visitFisico(fisico* f){
    dispWidget = new QLabel("Sensore Fisico \nNome:\t\t" + QString::fromStdString(f->getNome()) +
     "\nDannoBase:\t\t" + QString::number(f->getDanno()) + "\tNumero di Hit:\t\t" + QString::number(f->getNHit()) +
     "\nNumero di Turni:\t\t" + QString::number(f->getNTurni()) + "\tNumero di Miss:\t\t" + QString::number(f->getNMiss()) +
     "\nAttacchi per Turno:\t" + QString::number(f->getAtt()) + "\tHit Rate:\t\t\t" + QString::number(f->getHitRate()) + "%" +
     "\nAffilatura:\t\t" + QString::number(f->getAffilatura()) + "%" + "\tDanno Massimo:\t\t" + QString::number(f->getMaxDanno()));
}

void ContentVisitor::visitMagico(magico* m){
    dispWidget = new QLabel("Sensore Magico \nNome:\t\t" + QString::fromStdString(m->getNome()) +
     "\nDannoBase:\t\t" + QString::number(m->getDanno()) + "\tNumero di Hit:\t\t" + QString::number(m->getNHit()) +
     "\nNumero di Turni:\t\t" + QString::number(m->getNTurni()) + "\tNumero di Miss:\t\t" + QString::number(m->getNMiss()) +
     "\nAttacchi per Turno:\t" + QString::number(m->getAtt()) + "\tHit Rate:\t\t\t" + QString::number(m->getHitRate()) + "%" +
     "\nLivello Magia:\t\t" + QString::number(m->getLvMagia()) + "\tDanno Massimo:\t\t" + QString::number(m->getMaxDanno()) +
     "\nCondizione:\t\t" + (m->checkCondition() ? "Si" : "No"));
}

void ContentVisitor::visitSacro(sacro* s){
    dispWidget = new QLabel("Sensore Sacro \nNome:\t\t" + QString::fromStdString(s->getNome()) +
     "\nDannoBase:\t\t" + QString::number(s->getDanno()) + "\tNumero di Hit:\t\t" + QString::number(s->getNHit()) +
     "\nNumero di Turni:\t\t" + QString::number(s->getNTurni()) + "\tNumero di Miss:\t\t" + QString::number(s->getNMiss()) +
     "\nAttacchi per Turno:\t" + QString::number(s->getAtt()) + "\tHit Rate:\t\t\t" + QString::number(s->getHitRate()) + "%" +
     "\nLivello Fede:\t\t" + QString::number(s->getLvFede()) + "\tDanno Massimo:\t\t" + QString::number(s->getMaxDanno()) +
     "\nUltimo valore Limit:\t" + QString::number(s->getlimitBreak()));
}

QWidget* ContentVisitor::returnQWidget() {
    return dispWidget;
}