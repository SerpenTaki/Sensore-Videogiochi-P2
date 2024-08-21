#include "headers/modificaSensore.h"

modificaSensore::modificaSensore(QWidget* parent, sensoreDanno* sensoreDaModificare)
    : aggiungiSensore(parent){
    setWindowTitle("Modifica Sensore");
    // Populate the UI with the existing sensor data
    nomeSensoreInserimento->setText(QString::fromStdString(sensoreDaModificare->getNome()));
    DannoBase->setValue(sensoreDaModificare->getDanno());
    NumeroDiTurni->setValue(sensoreDaModificare->getNTurni());
    AttPerTurno->setValue(sensoreDaModificare->getAtt());

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
}


void modificaSensore::caricaDatiSensore() {
    if (sensoreDaModificare) {
        nomeSensoreInserimento->setText(QString::fromStdString(sensoreDaModificare->getNome()));
        DannoBase->setValue(sensoreDaModificare->getDanno());
        NumeroDiTurni->setValue(sensoreDaModificare->getNTurni());
        AttPerTurno->setValue(sensoreDaModificare->getAtt());

        if (auto fisicoPtr = dynamic_cast<fisico*>(sensoreDaModificare)) {
            checkBoxFisico->setChecked(true);
            PAffilatura->setValue(fisicoPtr->getAffilatura());
        } else if (auto magicoPtr = dynamic_cast<magico*>(sensoreDaModificare)) {
            checkBoxMagico->setChecked(true);
            SLvMagia->setValue(magicoPtr->getLvMagia());
            StatusApp->setChecked(magicoPtr->checkCondition());
        } else if (auto sacroPtr = dynamic_cast<sacro*>(sensoreDaModificare)) {
            checkBoxSacro->setChecked(true);
            SLvFede->setValue(sacroPtr->getLvFede());
        }
    }
}

void modificaSensore::confermaClicked() {
    // Utilizza il metodo originale per validare e aggiornare i dati
    aggiungiSensore::confermaClicked();

    // Dopo la conferma, emetti un segnale specifico per la modifica
    emit sensoreModificato(nomeSensoreInserimento->text());
    emit sensoreModificatoStats(sensoreDaModificare);
}
