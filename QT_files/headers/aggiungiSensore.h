#ifndef AGGIUNGISENSORE_H
#define AGGIUNGISENSORE_H

#include<QDialog>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QCheckBox>
#include<QRadioButton>
#include<QDebug>
#include <QSpinBox>

class aggiungiSensore: public QDialog{
private:
    QVBoxLayout* nuovoSens;
    QPushButton* conferma;
    QLineEdit* nomeSensoreInserimento;
    QRadioButton *checkBoxFisico;
    QRadioButton *checkBoxMagico;
    QRadioButton *checkBoxSacro;
    QSpinBox *DannoBase;
    QSpinBox *NumeroDiTurni;
    QPushButton* annulla;
    QWidget *dynamicWidget;
    QVBoxLayout *dynamicLayout;
public:
    aggiungiSensore(QWidget* parent = nullptr){
        nuovoSens = new QVBoxLayout(this);
        QLabel* insNome = new QLabel("inserisci Nome Sensore:");
        nuovoSens->addWidget(insNome);
        nomeSensoreInserimento = new QLineEdit;
        nuovoSens->addWidget(nomeSensoreInserimento);
        QLabel* selezionaTipo = new QLabel("Seleziona tipo Sensore");
        nuovoSens->addWidget(selezionaTipo);
        checkBoxFisico = new QRadioButton("Fisico");
        checkBoxMagico = new QRadioButton("Magico");
        checkBoxSacro = new QRadioButton("Sacro");
        nuovoSens->addWidget(checkBoxFisico);
        nuovoSens->addWidget(checkBoxMagico);
        nuovoSens->addWidget(checkBoxSacro);
        
        dynamicWidget = new QWidget(this);
        dynamicLayout = new QVBoxLayout(dynamicWidget);  // Inizializza il layout dinamico
        dynamicWidget->setLayout(dynamicLayout);
        nuovoSens->addWidget(dynamicWidget);

        connect(checkBoxFisico, &QRadioButton::toggled, this, &aggiungiSensore::onRadioButtonToggled);
        connect(checkBoxMagico, &QRadioButton::toggled, this, &aggiungiSensore::onRadioButtonToggled);
        connect(checkBoxSacro, &QRadioButton::toggled, this, &aggiungiSensore::onRadioButtonToggled);

        DannoBase = new QSpinBox();
        QLabel* DannoBaseLabel = new QLabel("Seleziona il danno base 1-100");
        nuovoSens->addWidget(DannoBaseLabel);
        DannoBase->setMinimum(1);
        DannoBase->setMaximum(100);
        DannoBase->setSingleStep(5);
        DannoBase->setValue(50);
        nuovoSens->addWidget(DannoBase);
        QLabel* NTurniLabel = new QLabel("Seleziona il numero di turni 1-30");
        nuovoSens->addWidget(NTurniLabel);
        NumeroDiTurni = new QSpinBox();
        NumeroDiTurni->setMinimum(1);
        NumeroDiTurni->setMaximum(30);
        NumeroDiTurni->setSingleStep(1);
        NumeroDiTurni->setValue(1);
        nuovoSens->addWidget(NumeroDiTurni);


        conferma = new QPushButton("Crea Sensore");
        annulla = new QPushButton("Annulla");
        nuovoSens->addWidget(conferma);
        nuovoSens->addWidget(annulla);
    }

    void changeUIForOption1() {
        clearDynamicWidget();
        QLineEdit *lineEdit1 = new QLineEdit();
        lineEdit1->setPlaceholderText("Textbox per Opzione 1");
        dynamicLayout->addWidget(lineEdit1);
    }

    void changeUIForOption2() {
        clearDynamicWidget();
        QLineEdit *lineEdit1 = new QLineEdit();
        QLineEdit *lineEdit2 = new QLineEdit();
        lineEdit1->setPlaceholderText("Textbox 1 per Opzione 2");
        lineEdit2->setPlaceholderText("Textbox 2 per Opzione 2");
        dynamicLayout->addWidget(lineEdit1);
        dynamicLayout->addWidget(lineEdit2);
    }

    void changeUIForOption3() {
        clearDynamicWidget();
        QLineEdit *lineEdit1 = new QLineEdit();
        QLineEdit *lineEdit2 = new QLineEdit();
        QLineEdit *lineEdit3 = new QLineEdit();
        lineEdit1->setPlaceholderText("Textbox 1 per Opzione 3");
        lineEdit2->setPlaceholderText("Textbox 2 per Opzione 3");
        lineEdit3->setPlaceholderText("Textbox 3 per Opzione 3");
        dynamicLayout->addWidget(lineEdit1);
        dynamicLayout->addWidget(lineEdit2);
        dynamicLayout->addWidget(lineEdit3);
    }

    void clearDynamicWidget(){
            // Rimuove tutti i widget dal layout del dynamicWidget
    QLayoutItem *child;
    while ((child = dynamicWidget->layout()->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
    }

public slots:
    void onRadioButtonToggled(){
        QRadioButton *radioButton = qobject_cast<QRadioButton *>(sender());
        if (radioButton && radioButton->isChecked()) {
            QLabel* label = new QLabel();
            label->setText("Hai selezionato: " + radioButton->text());
            clearDynamicWidget();
            if (radioButton == checkBoxFisico) {
                changeUIForOption1();
            } else if (radioButton == checkBoxMagico) {
                changeUIForOption2();
            } else if (radioButton == checkBoxSacro) {
                changeUIForOption3();
            }
        }
    }
};



#endif