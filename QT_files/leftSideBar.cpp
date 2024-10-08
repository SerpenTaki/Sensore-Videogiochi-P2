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
    connect(importaSensoreBottone, &QPushButton::clicked, this, &leftSideBar::importaSensore);

    /* Per scorciatoia non più implementata
    QAction *saveAction = new QAction(tr("&Salva"), this);
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    connect(saveAction, &QAction::triggered, this, &leftSideBar::salvaSensoreXML);
    */
}

void leftSideBar::stampaSelSensore() { //fa apparire la selezione del sensore
    aggiungiSensore* dialog = new aggiungiSensore(this, contentWidget->getMapSensor());

    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, this, &leftSideBar::aggiungiSensoreToList);
    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, contentWidget, &content::aggiungiSensoreAMappa);

    dialog->exec(); // Mostra il dialogo come modale
    delete dialog;
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

void leftSideBar::eliminaSensore(string sensorName) {//in content e left
    for (int i = 0; i < sensoreListLabel->count(); ++i) {
        QListWidgetItem* item = sensoreListLabel->item(i);
        if (item && item->text() == QString::fromStdString(sensorName)) {
            delete sensoreListLabel->takeItem(i);
        }
    }
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

// Funzioni di utilità per conversioni
std::vector<double> leftSideBar::convertQListToStdVector(const QList<double>& list) {
    return std::vector<double>(list.begin(), list.end());
}

std::vector<int> leftSideBar::convertQListToStdVector(const QList<int>& list) {
    return std::vector<int>(list.begin(), list.end());
}


void leftSideBar::importaSensore() {
    // Chiedi all'utente di selezionare un file XML
    QString fileName = QFileDialog::getOpenFileName(this, tr("Importa Sensore"), "",
                                                    tr("XML Files (*.xml);;All Files (*)"));
    if (fileName.isEmpty()) {
        // L'utente ha annullato la selezione del file
        return;
    }

    // Apri il file XML
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Errore", "Impossibile aprire il file XML.");
        return;
    }

    // Leggi il file XML
    QXmlStreamReader xml(&file);
    sensoreDanno* sensore = nullptr;

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement) {
            QString elementName = xml.name().toString();  // Converti QStringView in QString

            if (elementName == QStringLiteral("fisico")) {
                // Variabili per memorizzare i dati del sensore
                QString nome;
                double danno = 0.0;
                int nTurni = 0, nAtt = 0, affilatura = 0;
                QList<double> rDPT;
                int hit = 0, miss = 0;

                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("fisico"))) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        QString name = xml.name().toString();  // Converti QStringView in QString
                        xml.readNext();  // Move to text
                        QString value = xml.text().toString();

                        if (name == QStringLiteral("nome")) nome = value;
                        else if (name == QStringLiteral("danno_base")) danno = value.toDouble();
                        else if (name == QStringLiteral("numero_turni")) nTurni = value.toInt();
                        else if (name == QStringLiteral("attacchi_per_turno")) nAtt = value.toInt();
                        else if (name == QStringLiteral("affilatura")) affilatura = value.toInt();
                        else if (name == QStringLiteral("hit")) hit = value.toInt();
                        else if (name == QStringLiteral("miss")) miss = value.toInt();
                        else if (name == QStringLiteral("danni_per_turno")) {
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("danni_per_turno"))) {
                                if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QStringLiteral("danno")) {
                                xml.readNext();
                                rDPT.push_back(xml.text().toDouble());
                            }
                            xml.readNext();  // Move to next element or text
                            }
                        }
                    }
                    xml.readNext();
                }
                // Confronto con gli elementi della QListWidget (sensoreListLabel)
                for (int i = 0; i < sensoreListLabel->count(); ++i) {
                    QListWidgetItem* item = sensoreListLabel->item(i);
                    if (item && item->text() == nome) {  // Confronto della QString con il testo dell'elemento
                        QMessageBox::warning(this, "Errore", "Sensore con lo stesso nome già presente!");
                        return;
                    }
                }

                // Crea l'oggetto fisico con i dati letti
                sensore = new fisico(nome.toStdString(), danno, nTurni, nAtt, convertQListToStdVector(rDPT), affilatura);
                sensore->setHit(hit);
                sensore->setMiss(miss);
            } 
            else if (elementName == QStringLiteral("magico")) {
                // Variabili per memorizzare i dati del sensore
                QString nome;
                double danno = 0.0;
                int nTurni = 0, nAtt = 0, lvMagia = 0;
                bool isInStatus = false;
                QList<double> rDPT;
                int hit = 0, miss = 0;

                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("magico"))) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                    QString name = xml.name().toString();  // Converti QStringView in QString
                    xml.readNext();  // Move to text
                    QString value = xml.text().toString();

                     if (name == QStringLiteral("nome")) {
                        nome = value;
                    } else if (name == QStringLiteral("danno_base")) {
                        danno = value.toDouble();
                    } else if (name == QStringLiteral("numero_turni")) {
                        nTurni = value.toInt();
                    } else if (name == QStringLiteral("attacchi_per_turno")) {
                        nAtt = value.toInt();
                    } else if (name == QStringLiteral("livello_magia")) {
                        lvMagia = value.toInt();
                    } else if (name == QStringLiteral("status")) {
                        isInStatus = (value == QStringLiteral("1"));
                    }
                    else if (name == QStringLiteral("hit")){
                        hit = value.toInt();
                    }
                    else if (name == QStringLiteral("miss")){
                        miss = value.toInt();
                    }
                    else if (name == QStringLiteral("danni_per_turno")) {
                        while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("danni_per_turno"))) {
                        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QStringLiteral("danno")) {
                            xml.readNext();
                            rDPT.push_back(xml.text().toDouble());
                        }
                        xml.readNext();  // Move to next element or text
                        }
                    }
                }
                xml.readNext();
                }
                // Confronto con gli elementi della QListWidget (sensoreListLabel)
                for (int i = 0; i < sensoreListLabel->count(); ++i) {
                    QListWidgetItem* item = sensoreListLabel->item(i);
                    if (item && item->text() == nome) {  // Confronto della QString con il testo dell'elemento
                        QMessageBox::warning(this, "Errore", "Sensore con lo stesso nome già presente!");
                        return;
                    }
                }
                // Crea l'oggetto magico con i dati letti
                sensore = new magico(nome.toStdString(), danno, nTurni, nAtt, convertQListToStdVector(rDPT), lvMagia, isInStatus);
                sensore->setHit(hit);
                sensore->setMiss(miss);
            } 
            else if (elementName == QStringLiteral("sacro")) {
                // Variabili per memorizzare i dati del sensore
                QString nome;
                double danno = 0.0;
                int nTurni = 0, nAtt = 0, lvFede = 0;
                QList<int> limitBar;
                QList<double> rDPT;
                int hit = 0, miss = 0, limitbreak = 0;

                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("sacro"))) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        QString name = xml.name().toString();  // Converti QStringView in QString
                        xml.readNext();  // Move to text
                        QString value = xml.text().toString();

                        if (name == QStringLiteral("nome")) nome = value;
                        else if (name == QStringLiteral("danno_base")) danno = value.toDouble();
                        else if (name == QStringLiteral("numero_turni")) nTurni = value.toInt();
                        else if (name == QStringLiteral("attacchi_per_turno")) nAtt = value.toInt();
                        else if (name == QStringLiteral("lvFede")) lvFede = value.toInt();
                        else if (name == QStringLiteral("limitbreak")) limitbreak = value.toInt();
                        else if (name == QStringLiteral("hit")) hit = value.toInt();
                        else if (name == QStringLiteral("miss")) miss = value.toInt();
                        else if (name == QStringLiteral("limitBar")) {
                        // Aggiungi i valori del limite della barra al QList
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("limitBar"))) {
                                if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QStringLiteral("limit")) {
                                    xml.readNext();  // Sposta al testo dell'elemento <limit>
                                    limitBar.push_back(xml.text().toInt());
                                    //cout << "Valore limit:" << (xml.text().toInt()) << endl;
                                    xml.readNext();  // Sposta al prossimo elemento o al prossimo EndElement
                                } else {
                                    xml.readNext();  // Continua al prossimo token se non è un elemento <limit>
                                }
                            }
                        }
                        else if (name == QStringLiteral("danni_per_turno")) {
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("danni_per_turno"))) {
                                if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QStringLiteral("danno")) {
                                    xml.readNext();
                                    rDPT.push_back(xml.text().toDouble());
                                }
                            xml.readNext();
                            }
                        }
                    }
                    xml.readNext();
                }
                // Confronto con gli elementi della QListWidget (sensoreListLabel)
                for (int i = 0; i < sensoreListLabel->count(); ++i) {
                    QListWidgetItem* item = sensoreListLabel->item(i);
                    if (item && item->text() == nome) {  // Confronto della QString con il testo dell'elemento
                        QMessageBox::warning(this, "Errore", "Sensore con lo stesso nome già presente!");
                        return;
                    }
                }
                // Crea l'oggetto sacro con i dati letti
                sensore = new sacro(nome.toStdString(), danno, nTurni, nAtt, convertQListToStdVector(rDPT), lvFede, convertQListToStdVector(limitBar));
                sensore->setHit(hit);
                sensore->setMiss(miss);
                dynamic_cast<sacro*>(sensore)->setLimitBreak(limitbreak);
            }
        }
    }

    if (xml.hasError()) {
        QMessageBox::warning(this, "Errore", "Errore nella lettura del file XML.");
    }

    file.close();

    if (sensore) {
        cout << "Nome sensore importato: " << sensore->getNome() << endl;
        aggiungiSensoreToList(sensore);
        contentWidget->aggiungiSensoreAMappa(sensore);
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
