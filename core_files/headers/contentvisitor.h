#ifndef CONTENTVISITOR_H
#define CONTENTVISITOR_H

#include "Visitor.h"
#include "fisico.h"
#include "magico.h"
#include "sacro.h"
#include<QString>
#include<QApplication>

class ContentVisitor : public Visitor {
private:
    QWidget* dispWidget;
public:
    ContentVisitor() = default;

    void visitFisico(fisico* f) override {
        dispWidget = new QLabel("Sensore Fisico:\nNome:" + getNome() +
         "\nDannoBase:" + getDanno() +
         "\nNumero di Turni:"+ getNTurni() +
         "\nAffilatura:" + getAffilatura()+ "%");
    }

    void visitMagico(magico* m) override {
        dispWidget = new QLabel("Sensore Magico:\nNome:" + getNome() +
         "\nDannoBase:" + getDanno() +
         "\nNumero di Turni:"+ getNTurni() +
         "\nLivello Magia:" + getLvMagia() +
         "\nCondizione:" + checkCondition());
    }

    void visitSacro(sacro* s) override {
        dispWidget = new QLabel("Sensore Magico:\nNome:" + getNome() +
         "\nDannoBase:" + getDanno() +
         "\nNumero di Turni:"+ getNTurni() +
         "\nLivello Fede:" + getLvFede()+
         "\nValore Limit:" + getLimitbreak());
    }

    QWidget* returnQWidget(){
        return dispWidget;
    }

};

#endif
