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

    connect(conferma, &QPushButton::clicked, this, &aggiungiSensore::confermaClicked); // Connetti il pulsante "Conferma"
    connect(annulla, &QPushButton::clicked, this, &aggiungiSensore::close);
}

void aggiungiSensore::confermaClicked() {
    QString nomeSensore = nomeSensoreInserimento->text();

    if (nomeSensore.isEmpty()) {
        QMessageBox::warning(this, "Dati Mancanti", "Per favore, inserisci un nome per il sensore.");
        return;
    }

    if (!checkBoxFisico->isChecked() && !checkBoxMagico->isChecked() && !checkBoxSacro->isChecked()) {
        QMessageBox::warning(this, "Tipo di Sensore Mancante", "Per favore, seleziona un tipo di sensore.");
        return;
    }
    emit sensoreAggiunto(nomeSensore);
    accept();
}
/* da problemi
void aggiungiSensore::confermaClicked() {
    QString nomeSensore = nomeSensoreInserimento->text();
    QString tipoSensore;
    int extra1 = 0, extra2 = 0;
    bool status = false;
    QString statusStr;

    if (checkBoxFisico->isChecked()) {
        tipoSensore = "Fisico";
        extra1 = DannoBase->value(); // Affilatura
    } else if (checkBoxMagico->isChecked()) {
        tipoSensore = "Magico";
        extra1 = DannoBase->value(); // Livello Magia
        status = StatusApp->isChecked();
        statusStr = StatusApp->text(); // Presumendo che StatusApp sia una QCheckBox
    } else if (checkBoxSacro->isChecked()) {
        tipoSensore = "Sacro";
        extra1 = DannoBase->value(); // Livello Fede
        extra2 = 10; // Limit Break iniziale, o un valore di default
    }

    if (nomeSensore.isEmpty()) {
        QMessageBox::warning(this, "Dati Mancanti", "Per favore, inserisci un nome per il sensore.");
        return;
    }

    if (tipoSensore.isEmpty()) {
        QMessageBox::warning(this, "Tipo di Sensore Mancante", "Per favore, seleziona un tipo di sensore.");
        return;
    }

    GestoreSensori gestore;  // Istanza del gestore
    sensoreDanno* sensore = gestore.creaSensore(tipoSensore, DannoBase->value(), 50, 50, { NumeroDiTurni->value() }, extra1, extra2, status, statusStr);

    if (sensore) {
        emit sensoreAggiunto(nomeSensore);
        accept(); // Chiudi il dialogo
    } else {
        QMessageBox::warning(this, "Errore", "Impossibile creare il sensore.");
    }
}
*/

void aggiungiSensore::changeUIForOption1() {
    clearDynamicWidget();
    QLabel* labelAff = new QLabel("Seleziona percentuale affilatura");
    dynamicLayout->addWidget(labelAff);
    QSpinBox* PAffilatura = new QSpinBox();
    PAffilatura->setMinimum(1);
    PAffilatura->setMaximum(100);
    PAffilatura->setSingleStep(5);
    PAffilatura->setValue(40);
    dynamicLayout->addWidget(PAffilatura);
}

void aggiungiSensore::changeUIForOption2() {
    clearDynamicWidget();
    QLabel* labelLvMagia = new QLabel("Seleziona Livello di Magia 1-5");
    dynamicLayout->addWidget(labelLvMagia);
    QSpinBox* SLvMagia = new QSpinBox();
    SLvMagia->setMinimum(1);
    SLvMagia->setMaximum(5);
    SLvMagia->setSingleStep(1);
    SLvMagia->setValue(1);
    dynamicLayout->addWidget(SLvMagia);
    StatusApp = new QCheckBox("Vuoi l'avversario in status?");
    dynamicLayout->addWidget(StatusApp);
}

void aggiungiSensore::changeUIForOption3() {
    clearDynamicWidget();
    QLabel* labelLvFede = new QLabel("Seleziona livello Fede 0-2");
    dynamicLayout->addWidget(labelLvFede);
    QSpinBox* SLvFede = new QSpinBox();
    SLvFede->setMinimum(0);
    SLvFede->setMaximum(2);
    SLvFede->setSingleStep(1);
    SLvFede->setValue(0);
    dynamicLayout->addWidget(SLvFede);
}

void aggiungiSensore::clearDynamicWidget() {
    // Rimuove tutti i widget dal layout del dynamicWidget
    QLayoutItem *child;
    while ((child = dynamicWidget->layout()->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
}

void aggiungiSensore::onRadioButtonToggled() {
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
