#ifndef CONTENTVISITOR_H
#define CONTENTVISITOR_H

#include "Visitor.h"
#include "content.h"
#include "fisico.h"
#include "magico.h"
#include "sacro.h"

class ContentVisitor : public Visitor {
private:
    content* contentWidget;
public:
    ContentVisitor(content* c) : contentWidget(c) {}

    void visit(fisico* f) override {
        QString info = QString("Sensore Fisico:\nNome: %1\nDanno: %2\nProbabilità Hit: %3\nAffilatura: %4")
                        .arg(QString::fromStdString(f->getNome()))
                        .arg(f->getDanno())
                        .arg(f->getProbHit())
                        .arg(f->getAffilatura());
        contentWidget->aggiornaContenuto(info);
    }

    void visit(magico* m) override {
        QString info = QString("Sensore Magico:\nNome: %1\nDanno: %2\nProbabilità Hit: %3\nLivello Magia: %4\nStatus: %5")
                        .arg(QString::fromStdString(m->getNome()))
                        .arg(m->getDanno())
                        .arg(m->getProbHit())
                        .arg(m->getLvMagia())
                        .arg(QString::fromStdString(m->getStatus()));
        contentWidget->aggiornaContenuto(info);
    }

    void visit(sacro* s) override {
        QString info = QString("Sensore Sacro:\nNome: %1\nDanno: %2\nProbabilità Hit: %3\nLivello Fede: %4\nLimit Break: %5")
                        .arg(QString::fromStdString(s->getNome()))
                        .arg(s->getDanno())
                        .arg(s->getProbHit())
                        .arg(s->getLvFede())
                        .arg(s->getlimitBreak());
        contentWidget->aggiornaContenuto(info);
    }
};

#endif
