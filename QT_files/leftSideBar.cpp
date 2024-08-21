#include "headers/leftSideBar.h"

leftSideBar::leftSideBar(content* contentWidget, QWidget* parent)
    : QWidget(parent) {
    left = new QVBoxLayout(this);
    this->contentWidget = contentWidget;

    aggiungiSensoreBottone = new QPushButton("Aggiungi Sensore");
    importaSensoreBottone = new QPushButton("Importa Sensore");
    salvaSensoreBottone = new QPushButton("Salva Sensore");
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Cerca sensore...");
    sensoreList = new vector<sensoreDanno*>; // Inizializza la lista dei sensori
    sensoreListLabel = new QListWidget();


    left->addWidget(searchBox);
    left->addWidget(aggiungiSensoreBottone);
    left->addWidget(importaSensoreBottone);
    left->addWidget(sensoreListLabel);
    left->addWidget(salvaSensoreBottone);

    connect(aggiungiSensoreBottone, &QPushButton::clicked, this, &leftSideBar::stampaSelSensore);
    connect(searchBox, &QLineEdit::textChanged, this, &leftSideBar::eseguiRicerca);
    connect(sensoreListLabel, &QListWidget::itemClicked, [=](QListWidgetItem* item) {
        vector<sensoreDanno*>::iterator i;
        for(i = sensoreList->begin(); i != sensoreList->end(); ++i){
            if(QString::fromStdString((*i)->getNome()) == item->text()){
                emit sensoreSelezionato(*i);
            }
        }
    });

    connect(salvaSensoreBottone, &QPushButton::clicked, this, &leftSideBar::salvaSensoreXML);
    
}

void leftSideBar::stampaSelSensore() { //fa apparire la selezione del sensore
    aggiungiSensore* dialog = new aggiungiSensore(this);

    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, this, &leftSideBar::aggiungiSensoreToList);
    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, contentWidget, &content::aggiungiSensoreAlContenuto);

    dialog->exec(); // Mostra il dialogo come modale
}

void leftSideBar::aggiungiSensoreToList(sensoreDanno* sensore) {
    sensoreList->push_back(sensore);
    sensoreListLabel->addItem(QString::fromStdString(sensore->getNome()));

}

void leftSideBar::eseguiRicerca(const QString& text) {
    for (int i = 0; i < sensoreListLabel->count(); ++i) {
        QListWidgetItem* item = sensoreListLabel->item(i);
        item->setHidden(!item->text().contains(text, Qt::CaseInsensitive));
    }
}

void leftSideBar::eliminaSensore(sensoreDanno* sensore) {
    QList<QListWidgetItem*> items = sensoreListLabel->findItems(QString::fromStdString(sensore->getNome()), Qt::MatchExactly);
    if (!items.empty()) {
        delete items.first();  // Rimuovi l'elemento dalla QListWidget
        for(vector<sensoreDanno*>::iterator i = sensoreList->begin(); i != sensoreList->end(); ++i){
            if((*i)->getNome() == sensore->getNome()){
                sensoreList->erase(i);
                i--;
            }
        }
    }
}

void leftSideBar::salvaSensoreXML() {
    // Verifica se c'è un sensore selezionato
    QListWidgetItem* selectedItem = sensoreListLabel->currentItem();
    if (selectedItem) {
        QString nomeSensore = selectedItem->text();

        // Trova il sensore corrispondente
        for (auto sensore : *sensoreList) {
            if (QString::fromStdString(sensore->getNome()) == nomeSensore) {
                // Chiedi all'utente dove salvare il file
                QString fileName = QFileDialog::getSaveFileName(this, tr("Salva Sensore"), "",
                                                                tr("XML Files (*.xml);;All Files (*)"));
                if (!fileName.isEmpty()) {
                    // Salva il sensore in XML e controlla il successo dell'operazione
                    if (sensore->toXML(fileName.toStdString())) {
                        QMessageBox::information(this, "Salvataggio", "Sensore salvato con successo!");
                    } else {
                        QMessageBox::warning(this, "Errore", "Impossibile salvare il sensore!");
                    }
                }
                return;
            }
        }
    } else {
        QMessageBox::warning(this, "Attenzione", "Nessun sensore selezionato!");
    }
}

void leftSideBar::updateSensore(sensoreDanno* updatedSensore) {
    if (!updatedSensore) return;

    for (size_t i = 0; i < sensoreList->size(); ++i) {
        sensoreDanno* sensor = (*sensoreList)[i];
        if (sensor->getNome() == updatedSensore->getNome()) {
            // Update the sensor attributes
            sensor->setNome(updatedSensore->getNome());
            sensor->setDanno(updatedSensore->getDanno());
            sensor->setNTurni(updatedSensore->getNTurni());
            sensor->setAttacchiPerTurno(updatedSensore->getAttacchiPerTurno());
            sensor->setRecordDanniPerTurno(updatedSensore->getRecordDanniPerTurno());

            // Update the QListWidget display
            sensoreListLabel->clear();
            for (const auto& s : *sensoreList) {
                sensoreListLabel->addItem(QString::fromStdString(s->getNome()));
            }
            break;
        }
    }
}