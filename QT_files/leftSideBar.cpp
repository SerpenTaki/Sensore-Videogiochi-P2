#include "headers/leftSideBar.h"

leftSideBar::leftSideBar(QWidget* parent)
    : QWidget(parent) {
    left = new QVBoxLayout(this);

    aggiungiSensoreBottone = new QPushButton("Aggiungi Sensore");
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Cerca sensore...");
    sensoreList = new QListWidget(); // Inizializza la lista dei sensori
    salvaSensoriBottone = new QPushButton("Salva Sensori");
    salvaJsonBottone = new QPushButton("Salva in JSON"); // Nuovo pulsante

    left->addWidget(searchBox);
    left->addWidget(aggiungiSensoreBottone);
    left->addWidget(salvaSensoriBottone); // Aggiungi il pulsante "Salva Sensori"
    left->addWidget(salvaJsonBottone); // Aggiungi il pulsante "Salva in JSON"
    left->addWidget(sensoreList); // Aggiungi la lista al layout

    connect(aggiungiSensoreBottone, &QPushButton::clicked, this, &leftSideBar::stampaSelSensore);
    connect(searchBox, &QLineEdit::textChanged, this, &leftSideBar::eseguiRicerca);
    connect(sensoreList, &QListWidget::itemClicked, [=](QListWidgetItem* item) {
        emit sensoreSelezionato(item->text());
    });
    connect(salvaSensoriBottone, &QPushButton::clicked, this, &leftSideBar::salvaSensori); // Connetti il pulsante "Salva Sensori"
    connect(salvaJsonBottone, &QPushButton::clicked, this, &leftSideBar::salvaSensoriJson); // Connetti il pulsante "Salva in JSON"
}

void leftSideBar::stampaSelSensore() {
    aggiungiSensore* dialog = new aggiungiSensore(this);

    connect(dialog, &aggiungiSensore::sensoreAggiunto, this, &leftSideBar::aggiungiSensoreToList);

    dialog->exec(); // Mostra il dialogo come modale
}

void leftSideBar::aggiungiSensoreToList(const QString& sensoreName) {
    sensoreList->addItem(sensoreName);
    sensori.append(sensoreName); // Aggiungi il sensore alla lista per la ricerca
}

void leftSideBar::eseguiRicerca(const QString& text) {
    for (int i = 0; i < sensoreList->count(); ++i) {
        QListWidgetItem* item = sensoreList->item(i);
        item->setHidden(!item->text().contains(text, Qt::CaseInsensitive));
    }
}

void leftSideBar::eliminaSensore(const QString& sensoreName) {
    QList<QListWidgetItem*> items = sensoreList->findItems(sensoreName, Qt::MatchExactly);
    for (QListWidgetItem* item : items) {
        delete item;
        sensori.removeOne(sensoreName);
    }
}

void leftSideBar::salvaSensori() {
    QString fileName = QFileDialog::getSaveFileName(this, "Salva Sensori", "", "XML Files (*.xml)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Errore", "Non è stato possibile salvare il file.");
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Sensori");

    for (const QString& sensoreName : sensori) {
        xmlWriter.writeStartElement("Sensore");
        xmlWriter.writeTextElement("Nome", sensoreName);
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}

void leftSideBar::salvaSensoriJson() {
    QJsonArray sensoriArray;
    for (const QString& sensoreName : sensori) {
        QJsonObject sensoreObject;
        sensoreObject["nome"] = sensoreName;
        sensoriArray.append(sensoreObject);
    }

    QJsonObject root;
    root["Sensori"] = sensoriArray;

    QJsonDocument doc(root);

    QString fileName = QFileDialog::getSaveFileName(this, "Salva Sensori in JSON", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Errore", "Non è stato possibile salvare il file.");
        return;
    }

    QTextStream stream(&file);
    stream << doc.toJson(QJsonDocument::Indented); // Indenta con spazi
    file.close();
}
