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
        cout << "è stato eliminato:\t" << sensore->getNome() << endl;
    }
    QLayoutItem* item; //pulisci la visualizzazione alla selezione del sensore
    while ((item = layout()->takeAt(0)) != 0) {
        delete item->widget();
        delete item;
    }
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
    
    if(sensore != nullptr){
        //inizializzaChart();
        displayVector(sensore);
    }
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
/*
void content::updateSensore(sensoreDanno* updatedSensore) {
        if (!updatedSensore) return;

        for (sensoreDanno* sensor : sensors) {
            if (sensor->getNome() == updatedSensore->getNome()) {
                // Update attributes
                sensor->setNome(updatedSensore->getNome());
                sensor->setDanno(updatedSensore->getDanno());
                sensor->setNTurni(updatedSensore->getNTurni());
                sensor->setAttacchiPerTurno(updatedSensore->getAttacchiPerTurno());
                sensor->setRecordDanniPerTurno(updatedSensore->getRecordDanniPerTurno());

                // Optionally, refresh the display or other necessary actions
                break;
            }
        }
}

void content::addSensore(sensoreDanno* sensor) {
    sensors.push_back(sensor);
}*/

// sensoreDanno* getsensoreByName(nomeSensore string){
//      mapSensore[nomeSensore];
//}