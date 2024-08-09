#ifndef CONTENTVISITOR_H
#define CONTENTVISITOR_H

#include "visitor.h"
#include "fisico.h"
#include "magico.h"
#include "sacro.h"
#include <QWidget>
#include <QLabel>

class ContentVisitor : public Visitor {
private:
    QWidget* dispWidget;
public:
    ContentVisitor() = default;
    ~ContentVisitor() {
        delete dispWidget; // Assicurati di deallocare la memoria
    }

    void visitFisico(fisico* f) override {
        dispWidget = new QLabel("Sensore Fisico:\nNome:" + QString::fromStdString(f->getNome()) +
         "\nDannoBase:" + QString::number(f->getDanno()) +
         "\nNumero di Turni:" + QString::number(f->attacchiPerTurno.size()) +
         "\nAffilatura:" + QString::number(f->getAffilatura()) + "%");
    }

    void visitMagico(magico* m) override {
        dispWidget = new QLabel("Sensore Magico:\nNome:" + QString::fromStdString(m->getNome()) +
         "\nDannoBase:" + QString::number(m->getDanno()) +
         "\nNumero di Turni:" + QString::number(m->attacchiPerTurno.size()) +
         "\nLivello Magia:" + QString::number(m->getLvMagia()) +
         "\nCondizione:" + (m->checkCondition() ? "Si" : "No"));
    }

    void visitSacro(sacro* s) override {
        dispWidget = new QLabel("Sensore Sacro:\nNome:" + QString::fromStdString(s->getNome()) +
         "\nDannoBase:" + QString::number(s->getDanno()) +
         "\nNumero di Turni:" + QString::number(s->attacchiPerTurno.size()) +
         "\nLivello Fede:" + QString::number(s->getLvFede()) +
         "\nValore Limit:" + QString::number(s->getlimitBreak()));
    }

    QWidget* returnQWidget() {
        return dispWidget;
    }
};

#endif
