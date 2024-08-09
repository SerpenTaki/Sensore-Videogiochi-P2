#include "headers/aggiungiSensore.h"

aggiungiSensore::aggiungiSensore(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Aggiungi Sensore");
    nuovoSens = new QVBoxLayout(this);

    QLabel* insNome = new QLabel("Inserisci Nome Sensore:");
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
    dynamicLayout = new QVBoxLayout(dynamicWidget);
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

    connect(conferma, &QPushButton::clicked, this, &aggiungiSensore::confermaClicked);
    connect(annulla, &QPushButton::clicked, this, &QDialog::reject);
}

void aggiungiSensore::changeUIForOption1() { // Fisico
    clearDynamicWidget();
    QLabel* labelAff = new QLabel("Seleziona percentuale affilatura");
    dynamicLayout->addWidget(labelAff);
    PAffilatura = new QSpinBox();
    PAffilatura->setMinimum(1);
    PAffilatura->setMaximum(100);
    PAffilatura->setSingleStep(5);
    PAffilatura->setValue(40);
    dynamicLayout->addWidget(PAffilatura);
}

void aggiungiSensore::changeUIForOption2() { // Magico
    clearDynamicWidget();
    QLabel* labelLvMagia = new QLabel("Seleziona Livello di Magia 1-5");
    dynamicLayout->addWidget(labelLvMagia);
    SLvMagia = new QSpinBox();
    SLvMagia->setMinimum(1);
    SLvMagia->setMaximum(5);
    SLvMagia->setSingleStep(1);
    SLvMagia->setValue(1);
    dynamicLayout->addWidget(SLvMagia);
    StatusApp = new QCheckBox("Vuoi l'avversario in status?");
    dynamicLayout->addWidget(StatusApp);
}

void aggiungiSensore::changeUIForOption3() { // Sacro
    clearDynamicWidget();
    QLabel* labelLvFede = new QLabel("Seleziona livello Fede 0-2");
    dynamicLayout->addWidget(labelLvFede);
    SLvFede = new QSpinBox();
    SLvFede->setMinimum(0);
    SLvFede->setMaximum(2);
    SLvFede->setSingleStep(1);
    SLvFede->setValue(0);
    dynamicLayout->addWidget(SLvFede);
}

void aggiungiSensore::clearDynamicWidget() {
    // Rimuove tutti i widget dal layout del dynamicWidget
    QLayoutItem *child;
    while ((child = dynamicWidget->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}

void aggiungiSensore::onRadioButtonToggled() {
    QRadioButton *radioButton = qobject_cast<QRadioButton *>(sender());
    if (radioButton && radioButton->isChecked()) {
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

void aggiungiSensore::confermaClicked() {
    QString nomeSensoreQString = nomeSensoreInserimento->text();
    std::string nomeSensore = nomeSensoreQString.toStdString(); // Converti QString in std::string

    sensoreDanno* sensore = nullptr;

    if (checkBoxFisico->isChecked()) {
        if (PAffilatura) {
            sensore = new fisico(nomeSensore, DannoBase->value(), NumeroDiTurni->value(), PAffilatura->value());
        } else {
            QMessageBox::warning(this, "Errore", "Valore di affilatura non impostato.");
            return;
        }
    } else if (checkBoxMagico->isChecked()) {
        if (SLvMagia) {
            sensore = new magico(nomeSensore, DannoBase->value(), NumeroDiTurni->value(), SLvMagia->value(), StatusApp ? StatusApp->isChecked() : false);
        } else {
            QMessageBox::warning(this, "Errore", "Valore di magia non impostato.");
            return;
        }
    } else if (checkBoxSacro->isChecked()) {
        if (SLvFede) {
            sensore = new sacro(nomeSensore, DannoBase->value(), NumeroDiTurni->value(), SLvFede->value());
        } else {
            QMessageBox::warning(this, "Errore", "Valore di fede non impostato.");
            return;
        }
    }

    if (nomeSensoreQString.isEmpty()) {
        QMessageBox::warning(this, "Dati Mancanti", "Per favore, inserisci un nome per il sensore.");
        return;
    }

    if (!checkBoxFisico->isChecked() && !checkBoxMagico->isChecked() && !checkBoxSacro->isChecked()) {
        QMessageBox::warning(this, "Tipo di Sensore Mancante", "Per favore, seleziona un tipo di sensore.");
        return;
    }

    if (sensore) {
        emit sensoreAggiunto(nomeSensoreQString);
        emit sensoreAggiuntoStats(sensore);
        accept(); // Chiudi il dialogo
    } else {
        QMessageBox::warning(this, "Errore", "Impossibile creare il sensore.");
    }
}
