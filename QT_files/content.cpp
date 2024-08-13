#include "headers/content.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

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

void content::aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore) {
    if (!nuovoSensore) {
        return;
    }

    QLayoutItem* item; //resetta la visualizzazione alla selezione del sensore
    while ((item = layout()->takeAt(0)) != 0) {
        delete item->widget();
        delete item;
    }

    QLabel* nuovoSensoreLabel = new QLabel("Sensore creato: " + QString::fromStdString(nuovoSensore->getNome()), this);

    ContentVisitor* visitor = new ContentVisitor();
    nuovoSensore->accept(visitor);

    QWidget* visitorWidget = visitor->returnQWidget();
    if (visitorWidget) {
        center->addWidget(visitorWidget);
    }

    inizializzaChart();

    sensore = nuovoSensore; 
}

void content::inizializzaChart() {
    series = new /*QLineSeries::*/QLineSeries();

    chart = new /*QChart::*/QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Danni per numero di turni");
    chart->axes(Qt::Horizontal).first()->setRange(0, 30);

    chartView = new /*QtChartsView::*/QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    center->addWidget(chartView);  // Aggiungere il chartView al layout
}

void content::displayVector(sensoreDanno *sensore){
    if (!series) {
        inizializzaChart();
    }
    series->clear();
    if (sensore) {
        auto valori = /*dynamic_cast<fisico*>*/(sensore)->getValoriGrafico(); //non so perchè non mi displaya i valori giusti debug da fare....
        for (size_t it = 0; it < valori.size(); ++it) {
            series->append((it), valori[it]);
        }
        chart->update();
    } else {
        QMessageBox::warning(this, "Errore", "Sensore non valido.");
    }
}
