#include "headers/content.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

content::content(QWidget* parent)
    : QWidget(parent), selectedSensore("") {
    center = new QVBoxLayout(this);
    grafichino = new QLabel("Mostra qui il grafico", this);
    center->addWidget(grafichino);
}

void content::avviaSimulazione() {
    sim = new QLabel("Simulazione Avviata", this);
    center->addWidget(sim);
}

void content::eliminaSensore(const QString& sensoreName) {
    QLayoutItem* item;
    while ((item = center->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    if (selectedSensore == sensoreName) {
        selectedSensore = "";
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
    chart->setTitle("Attacchi per Turno & Numero di Turni");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    center->addWidget(chartView);
}
