#include "headers/content.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include<algorithm>

content::content(QWidget* parent)
    : QWidget(parent), sensore(nullptr) {
    center = new QVBoxLayout(this);
    welcome = new QLabel("Benvenuto nel programma di sensori", this);
    center->addWidget(welcome);
}

void content::eliminaSensore(sensoreDanno* sensore) {
    if (sensore) {
        cout << "È stato eliminato:\t" << sensore->getNome() << endl;

        // Pulire la visualizzazione alla selezione del sensore
        QLayoutItem* item;
        while ((item = layout()->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();  // Elimina il widget
            }
            delete item;  // Elimina l'elemento di layout
        }
        // Rimuovi il sensore dalla mappa
        auto it = mapSensor.find(sensore->getNome());
        if (it != mapSensor.end()) {
            delete it->second;  // Distruggi l'oggetto sensore
            mapSensor.erase(it);  // Rimuovi il sensore dalla mappa
        }
    }
    return;
}



sensoreDanno* content::getSelectedSensore() const {
    return sensore;
}

void content::aggiungiSensoreAMappa(sensoreDanno* sensore){
    cout << sensore->getNome() << " Aggiunto in memoria" << endl;
    mapSensor[sensore->getNome()] = sensore;
}

void content::aggiungiSensoreAlContenuto(string sensoreName) {
    cout << sensoreName << "debug2" << endl;
    sensore = mapSensor[sensoreName];
    if(!sensore){
        return;
    }
    displayVector(sensore);
}

void content::inizializzaChart() {
    series = new /*QLineSeries::*/QLineSeries();

    chart = new /*QChart::*/QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Danni per numero di turni");
    
    axisX = new QValueAxis();
    axisX->setRange(0, 5);
    axisX->setLabelFormat("%d");        
    axisX->setTitleText("Turni");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX); 

    axisY = new QValueAxis();
    axisY->setRange(0, 100);      
    axisY->setLabelFormat("%d");      
    axisY->setTitleText("Danni");
    chart->addAxis(axisY, Qt::AlignLeft);  
    series->attachAxis(axisY); 


    chartView = new /*QtChartsView::*/QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    center->addWidget(chartView);  // Aggiungere il chartView al layout
}

void content::displayVector(sensoreDanno *sensore){
    QLayoutItem* item; //resetta la visualizzazione alla selezione del sensore
    while ((item = layout()->takeAt(0)) != nullptr) {
        if(item->widget()){
            delete item->widget();
        }
        delete item;
    }
    
    ContentVisitor* visitor = new ContentVisitor();
    sensore->accept(visitor);
    cout << "Debug";
    QWidget* visitorWidget = visitor->returnQWidget();
    if (visitorWidget) {
       center->addWidget(visitorWidget);
    }
    
    
    inizializzaChart();
    series->clear();
    if (sensore) {
        auto valori = (sensore)->getRecordDanniPerTurno();
        for (size_t it = 0; it <= valori.size(); ++it) {
            series->append((it), valori[it]);
        }
        cout << "log1" << endl;
        auto max_danno = std::max_element(valori.begin(), valori.end());
        cout << "il valore massimo è: " << *max_danno << endl;
        axisY->setRange(0, static_cast<double>(*max_danno));
        axisX->setRange(0, static_cast<double>(valori.size()));
        chart->update();
        if(dynamic_cast<sacro*>(sensore)){
            auto valoriLimit = dynamic_cast<sacro*>(sensore)->getValoriLimitBar();
            serieLimit = new QLineSeries();
            for(size_t it = 0; it <= valoriLimit.size(); ++it){
                serieLimit->append((it), valoriLimit[it]);
            }
            chartLimit = new QChart();
            chartLimit->legend()->hide();
            chartLimit->addSeries(serieLimit);
            chartLimit->setTitle("Valori Limit");

            QValueAxis* axisTurni = new QValueAxis();
            axisTurni->setRange(0, 5);
            axisTurni->setLabelFormat("%d");        
            axisTurni->setTitleText("Turni");
            chartLimit->addAxis(axisTurni, Qt::AlignBottom);
            serieLimit->attachAxis(axisTurni); 

            QValueAxis* axisLimit = new QValueAxis();
            axisLimit->setRange(0, 100);      
            axisLimit->setLabelFormat("%d");      
            axisLimit->setTitleText("Limit");
            chartLimit->addAxis(axisLimit, Qt::AlignLeft);  
            serieLimit->attachAxis(axisLimit); 


            chartViewLimit = new QChartView(chartLimit);
            chartViewLimit->setRenderHint(QPainter::Antialiasing);
            //QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding); // Adjust spacing here
            //center->addWidget(spacer);
            chartView->setMinimumSize(400, 300); // Imposta le dimensioni minime a 400x300
            chartView->setMaximumSize(600, 400); // Imposta le dimensioni massime a 800x600
            chartViewLimit->setMinimumSize(400, 300); // Imposta le dimensioni minime a 400x300
            chartViewLimit->setMaximumSize(600, 400); // Imposta le dimensioni massime a 800x600

            auto max_Limit = std::max_element(valoriLimit.begin(), valoriLimit.end());
            axisLimit->setRange(0, static_cast<int>(*max_Limit));
            axisTurni->setRange(0, static_cast<int>(valoriLimit.size()));
            chart->update();
            center->addWidget(chartViewLimit);
            valoriLimit.clear();
        }
    } else {
        QMessageBox::warning(this, "Errore", "Sensore non valido.");
    }
}

void content::avviaSimulazione(sensoreDanno* sensore){
    if(sensore)
        sensore->generaValoriRandomGrafico();
    else
        QMessageBox::warning(this, "Errore", "Sensore non valido.");
}

void content::updateSensore(sensoreDanno* updatedSensore) {
    if (!updatedSensore) {
        QMessageBox::warning(this, "Errore", "Sensore non valido.");
        return;
    }

    auto it = mapSensor.find(updatedSensore->getNome());
    if (it != mapSensor.end()) {
        // Aggiorna l'oggetto sensore esistente nella mappa
        sensoreDanno* existingSensore = it->second;
        existingSensore->setNome(updatedSensore->getNome());
        existingSensore->setDanno(updatedSensore->getDanno());
        existingSensore->setNTurni(updatedSensore->getNTurni());
        existingSensore->setAttacchiPerTurno(updatedSensore->getAttacchiPerTurno());
        existingSensore->setRecordDanniPerTurno(updatedSensore->getRecordDanniPerTurno());

        // Opzionalmente, aggiorna la visualizzazione del sensore se è quello attualmente selezionato
        if (sensore && sensore->getNome() == updatedSensore->getNome()) {
            displayVector(existingSensore);
        }
        
        cout << "Sensore aggiornato: " << updatedSensore->getNome() << endl;
    } else {
        QMessageBox::warning(this, "Errore", "Sensore non trovato nella mappa.");
    }
}

/*
void content::addSensore(sensoreDanno* sensor) {
    sensors.push_back(sensor);
}*/

// sensoreDanno* getsensoreByName(nomeSensore string){
//      mapSensore[nomeSensore];
//}

//void leftSideBar::salvaSensoreXML() {
   /* // Verifica se c'è un sensore selezionato
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
    }*/
//}

//void leftSideBar::updateSensore(sensoreDanno* updatedSensore) {//sia in left che in right
   /* if (!updatedSensore) return;

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
    }*/
//}

std::map<string, sensoreDanno*> content::getMapSensor(){
    return mapSensor;
}