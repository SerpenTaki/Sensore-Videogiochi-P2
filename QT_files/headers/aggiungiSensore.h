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
    QLineEdit* specifica;
    QCheckBox *checkBoxFisico;
    QCheckBox *checkBoxMagico;
    QCheckBox *checkBoxSacro;
public:
    aggiungiSensore(QWidget* parent = nullptr){
        nuovoSens = new QVBoxLayout(this);
        QCheckBox *checkBoxFisico = new QCheckBox("Fisico");
        QCheckBox *checkBoxMagico = new QCheckBox("Magico");
        QCheckBox *checkBoxSacro = new QCheckBox("Sacro");
        nuovoSens->addWidget(checkBoxFisico);
        nuovoSens->addWidget(checkBoxMagico);
        nuovoSens->addWidget(checkBoxSacro);
    }
};



#endif