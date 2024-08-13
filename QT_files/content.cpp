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
       /* delete sensore;  // Chiama il distruttore del sensore
        sensore = nullptr;

        // Aggiungi qui codice per aggiornare l'interfaccia se necessario
        grafichino->clear();
        sim->clear();*/
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

    sensore = nuovoSensore; 
}
/*
void content::mostraGrafico(const QVector<QPointF>& data) {
    QLayoutItem* item;
    while ((item = center->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QLineSeries *series = new QLineSeries();
    for (const QPointF &point : data) {
        series->append(point);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Danno per Turno");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    center->addWidget(chartView);
}

void content::mostraGraficoSensore() {
    if (!sensore) {
        return; 
    }

    vector<double> valoriGrafico = sensore->getValoriGrafico();
    QVector<QPointF> puntiGrafico;

    for (size_t i = 0; i < valoriGrafico.size(); ++i) {
        puntiGrafico.append(QPointF(static_cast<qreal>(i), static_cast<qreal>(valoriGrafico[i])));
    }

    mostraGrafico(puntiGrafico);
}
*/