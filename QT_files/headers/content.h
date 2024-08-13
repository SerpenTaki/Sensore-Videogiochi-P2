#ifndef CONTENT_H
#define CONTENT_H

#include "viewlib.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

//QT_CHARTS_USE_NAMESPACE

#include "core_files/headers/sensoreDanno.h" 

class content : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* center;
    QLabel* welcome;
    QLabel* sim;
    sensoreDanno* sensore;
    //per grafico
    /*QLineSeries::*/QLineSeries* series; //per inserire i dati
    /*QChart::*/QChart* chart; //crea chart per interagire con la serie
    /*QChartView::*/QChartView* chartView; //per proiettare il grafico
public:
    explicit content(QWidget* parent = nullptr);
    void eliminaSensore(sensoreDanno* sensore);
    sensoreDanno* getSelectedSensore() const;
    void inizializzaChart();

public slots:
    void aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore);

};

#endif
