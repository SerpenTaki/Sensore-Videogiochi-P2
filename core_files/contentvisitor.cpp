#include"headers/contentvisitor.h"

ContentVisitor::ContentVisitor() {}

ContentVisitor::~ContentVisitor() {
    delete dispWidget;
}

void ContentVisitor::visitFisico(fisico* f) override {
    dispWidget = new QLabel("Sensore Fisico:\nNome:" + QString::fromStdString(f->getNome()) +
     "\nDannoBase:" + QString::number(f->getDanno()) +
     "\nNumero di Turni:" + QString::number(f->getNTurni()) +
     "\nAttacchi per Turno:" + QString::number(f->attacchiPerTurno.size()) + 
     "\nAffilatura:" + QString::number(f->getAffilatura()) + "%");
}

void ContentVisitor::visitMagico(magico* m) override {
    dispWidget = new QLabel("Sensore Magico:\nNome:" + QString::fromStdString(m->getNome()) +
     "\nDannoBase:" + QString::number(m->getDanno()) +
     "\nNumero di Turni:" + QString::number(m->getNTurni()) +
     "\nAttacchi per Turno:" + QString::number(m->attacchiPerTurno.size()) + 
     "\nLivello Magia:" + QString::number(m->getLvMagia()) +
     "\nCondizione:" + (m->checkCondition() ? "Si" : "No"));
}

void ContentVisitor::visitSacro(sacro* s) override {
    dispWidget = new QLabel("Sensore Sacro:\nNome:" + QString::fromStdString(s->getNome()) +
     "\nDannoBase:" + QString::number(s->getDanno()) +
     "\nNumero di Turni:" + QString::number(s->getNTurni()) +
     "\nAttacchi per Turno:" + QString::number(s->attacchiPerTurno.size()) + 
     "\nLivello Fede:" + QString::number(s->getLvFede()) +
     "\nValore Limit:" + QString::number(s->getlimitBreak()));
}

QWidget* ContentVisitor::returnQWidget() {
    return dispWidget;
}