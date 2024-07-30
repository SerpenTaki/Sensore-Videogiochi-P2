#ifndef AGGIUNGISENSORE_H
#define AGGIUNGISENSORE_H

#include<QDialog>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QCheckBox>
#include<QDebug>

class aggiungiSensore: public QDialog{
private:
    QVBoxLayout* nuovoSens;
    QPushButton* conferma;
    QLineEdit* nomeSensoreInserimento;
    QCheckBox *checkBoxFisico;
    QCheckBox *checkBoxMagico;
    QCheckBox *checkBoxSacro;
public:
    aggiungiSensore(QWidget* parent = nullptr){
        nuovoSens = new QVBoxLayout(this);
        QLabel* insNome = new QLabel("inserisci Nome Sensore:");
        nuovoSens->addWidget(insNome);
        nomeSensoreInserimento = new QLineEdit;
        nuovoSens->addWidget(nomeSensoreInserimento);
        QLabel* selezionaTipo = new QLabel("Seleziona tipo Sensore");
        nuovoSens->addWidget(selezionaTipo);
        QCheckBox *checkBoxFisico = new QCheckBox("Fisico");
        QCheckBox *checkBoxMagico = new QCheckBox("Magico");
        QCheckBox *checkBoxSacro = new QCheckBox("Sacro");
        nuovoSens->addWidget(checkBoxFisico);
        nuovoSens->addWidget(checkBoxMagico);
        nuovoSens->addWidget(checkBoxSacro);
    }
};



#endif