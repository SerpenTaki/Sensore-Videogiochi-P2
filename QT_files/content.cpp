#include "headers/content.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

content::content(QWidget* parent)
    : QWidget(parent), selectedSensore(""), sensore(nullptr) {
    center = new QVBoxLayout(this);
    grafichino = new QLabel("Mostra qui il grafico", this);
    center->addWidget(grafichino);
}

void content::eliminaSensore(const QString& sensoreName) {
    if (sensore && sensore->getNome() == sensoreName.toStdString()) {
        delete sensore;  // Chiama il distruttore del sensore
        sensore = nullptr;
        selectedSensore.clear();
        // Aggiungi qui codice per aggiornare l'interfaccia se necessario
        grafichino->clear();
        sim->clear();
    }
}


QString content::getSelectedSensore() const {
    return selectedSensore;
}

void content::aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore) {
    if (!nuovoSensore) {
        return;
    }

    QLabel* nuovoSensoreLabel = new QLabel("Sensore creato: " + QString::fromStdString(nuovoSensore->getNome()), this);
    center->addWidget(nuovoSensoreLabel);

    ContentVisitor* visitor = new ContentVisitor();
    nuovoSensore->accept(visitor);

    QWidget* visitorWidget = visitor->returnQWidget();
    if (visitorWidget) {
        center->addWidget(visitorWidget);
    }

    selectedSensore = QString::fromStdString(nuovoSensore->getNome());
    sensore = nuovoSensore; 
    delete visitor;
}

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
