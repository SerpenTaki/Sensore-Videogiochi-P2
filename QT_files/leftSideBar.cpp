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
    sensoreListLabel = new QListWidget();


    left->addWidget(searchBox);
    left->addWidget(aggiungiSensoreBottone);
    left->addWidget(importaSensoreBottone);
    left->addWidget(sensoreListLabel);
    left->addWidget(salvaSensoreBottone);

    connect(aggiungiSensoreBottone, &QPushButton::clicked, this, &leftSideBar::stampaSelSensore);
    connect(searchBox, &QLineEdit::textChanged, this, &leftSideBar::eseguiRicerca);
    connect(sensoreListLabel, &QListWidget::itemClicked, [=](QListWidgetItem* item) {
        emit sensoreSelezionato(item->text().toStdString());
    });

    connect(salvaSensoreBottone, &QPushButton::clicked, this, &leftSideBar::salvaSensoreXML);
    
}

void leftSideBar::stampaSelSensore() { //fa apparire la selezione del sensore
    aggiungiSensore* dialog = new aggiungiSensore(this);

    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, this, &leftSideBar::aggiungiSensoreToList);
    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, contentWidget, &content::aggiungiSensoreAMappa);

    dialog->exec(); // Mostra il dialogo come modale
}

void leftSideBar::aggiungiSensoreToList(sensoreDanno* sensore) {
    sensoreListLabel->addItem(QString::fromStdString(sensore->getNome()));

}

void leftSideBar::eseguiRicerca(const QString& text) {
    for (int i = 0; i < sensoreListLabel->count(); ++i) {
        QListWidgetItem* item = sensoreListLabel->item(i);
        item->setHidden(!item->text().contains(text, Qt::CaseInsensitive));
    }
}

void leftSideBar::eliminaSensore(sensoreDanno* sensore) {//in content e left
  /*  QList<QListWidgetItem*> items = sensoreListLabel->findItems(QString::fromStdString(sensore->getNome()), Qt::MatchExactly);
    if (!items.empty()) {
        delete items.first();  // Rimuovi l'elemento dalla QListWidget
        for(vector<sensoreDanno*>::iterator i = sensoreList->begin(); i != sensoreList->end(); ++i){
            if((*i)->getNome() == sensore->getNome()){
                sensoreList->erase(i);
                i--;
            }
        }
    }*/
}

void leftSideBar::salvaSensoreXML() {
    // Verifica se c'è un sensore selezionato
    QListWidgetItem* selectedItem = sensoreListLabel->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Attenzione", "Nessun sensore selezionato!");
        return;
    }

    QString nomeSensore = selectedItem->text();
    
    // Trova il sensore corrispondente nella mappa degli sensori nel widget 'content'
    sensoreDanno* sensore = nullptr;
    for (const auto& pair : contentWidget->getMapSensor()) {
        if (QString::fromStdString(pair.first) == nomeSensore) {
            sensore = pair.second;
            break;
        }
    }

    if (!sensore) {
        QMessageBox::warning(this, "Errore", "Sensore non trovato.");
        return;
    }

    // Chiedi all'utente dove salvare il file
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva Sensore"), "",
                                                    tr("XML Files (*.xml);;All Files (*)"));
    if (fileName.isEmpty()) {
        // L'utente ha annullato la selezione del file
        return;
    }

    // Salva il sensore in XML e controlla il successo dell'operazione
    if (sensore->toXML(fileName.toStdString())) {
        QMessageBox::information(this, "Salvataggio", "Sensore salvato con successo!");
    } else {
        QMessageBox::warning(this, "Errore", "Impossibile salvare il sensore!");
    }
}


void leftSideBar::updateSensore(sensoreDanno* updatedSensore) {
    if (!updatedSensore) {
        QMessageBox::warning(this, "Errore", "Sensore non valido.");
        return;
    }
    QListWidgetItem* itemToUpdate = nullptr;
    // Trova l'elemento
    for (int i = 0; i < sensoreListLabel->count(); ++i) {
        QListWidgetItem* item = sensoreListLabel->item(i);
        if (item->text().toStdString() == updatedSensore->getNome()) {
            itemToUpdate = item;
            break;
        }
    }

    if (itemToUpdate) {
        // Rimuovi l'elemento esistente
        delete itemToUpdate;
        // Aggiungi l'elemento aggiornato
        sensoreListLabel->addItem(QString::fromStdString(updatedSensore->getNome()));
        cout << "Sensore aggiornato nella lista: " << updatedSensore->getNome() << endl;
    } else {
        QMessageBox::warning(this, "Errore", "Sensore non trovato nella lista.");
    }
}
