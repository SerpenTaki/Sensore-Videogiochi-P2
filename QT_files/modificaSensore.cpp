#include "headers/modificaSensore.h"

modificaSensore::modificaSensore(QWidget* parent, sensoreDanno* sensoreDaModificare)
    : aggiungiSensore(parent){
    this->sensoreDaModificare = sensoreDaModificare;   
    setWindowTitle("Modifica Sensore");
    // Populate the UI with the existing sensor data
    insNome->setText("Nome Sensore:");
    selezionaTipo->setText("Tipo Sensore:");
    nomeSensoreInserimento->setText(QString::fromStdString(sensoreDaModificare->getNome()));
    nomeSensoreInserimento->setReadOnly(true);
    DannoBase->setValue(sensoreDaModificare->getDanno());
    NumeroDiTurni->setValue(sensoreDaModificare->getNTurni());
    AttPerTurno->setValue(sensoreDaModificare->getAtt());
    checkBoxFisico->setEnabled(false);
    checkBoxMagico->setEnabled(false);
    checkBoxSacro->setEnabled(false);
    // Populate specific sensor data based on its type
    if (fisico* fisicoPtr = dynamic_cast<fisico*>(sensoreDaModificare)) {
        checkBoxFisico->setChecked(true);
        PAffilatura->setValue(fisicoPtr->getAffilatura());
    } else if (magico* magicoPtr = dynamic_cast<magico*>(sensoreDaModificare)) {
        checkBoxMagico->setChecked(true);
        SLvMagia->setValue(magicoPtr->getLvMagia());
        StatusApp->setChecked(magicoPtr->checkCondition());
    } else if (sacro* sacroPtr = dynamic_cast<sacro*>(sensoreDaModificare)) {
        checkBoxSacro->setChecked(true);
        SLvFede->setValue(sacroPtr->getLvFede());
    }
    connect(conferma, &QPushButton::clicked, this, &modificaSensore::confermaClicked);
    connect(annulla, &QPushButton::clicked, this, &QDialog::reject);
}

void modificaSensore::confermaClicked() {
    sensoreDaModificare->setDanno(DannoBase->value());
    sensoreDaModificare->setNTurni(NumeroDiTurni->value());
    sensoreDaModificare->setAtt(AttPerTurno->value());
    if (checkBoxFisico->isChecked()) {
        if (PAffilatura) {
            dynamic_cast<fisico*>(sensoreDaModificare)->setAff(PAffilatura->value());
        } else {
            QMessageBox::warning(this, "Errore", "Valore di affilatura non impostato.");
            return;
        }
    } else if (checkBoxMagico->isChecked()) {
        if (SLvMagia) {
            auto castMagico = dynamic_cast<magico*>(sensoreDaModificare);
            castMagico->setLvMagia(SLvMagia->value());
            castMagico->setTheStatus(StatusApp ? StatusApp->isChecked() : false);
        } else {
            QMessageBox::warning(this, "Errore", "Valore di magia non impostato.");
            return;
        }
    } else if (checkBoxSacro->isChecked()) {
        if (SLvFede) {
           dynamic_cast<sacro*>(sensoreDaModificare)->setLvFede(SLvFede->value());
        } else {
            QMessageBox::warning(this, "Errore", "Valore di fede non impostato.");
            return;
        }
    }

    if (sensoreDaModificare) {
        //emit sensoreAggiuntoStats(sensoreDaModificare);
        accept(); // Chiudi il dialogo
    } else {
        QMessageBox::warning(this, "Errore", "Impossibile creare il sensore.");
    }
}
