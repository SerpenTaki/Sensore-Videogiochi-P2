#ifndef CONTENT_H
#define CONTENT_H

#include "viewlib.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include<map>

using namespace QtCharts;  
//QT_CHARTS_USE_NAMESPACE

#include "core_files/headers/sensoreDanno.h" 

class content : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* center;
    QLabel* welcome;
    QLabel* sim;
    sensoreDanno* sensore;
    QValueAxis *axisX;
    QValueAxis *axisY;
    //per grafico
    /*QLineSeries::*/QLineSeries* series; //per inserire i dati
    QLineSeries* serieLimit;
    /*QChart::*/QChart* chart; //crea chart per interagire con la serie
    QChart* chartLimit;
    /*QChartView::*/QChartView* chartView; //per proiettare il grafico
    QChartView* chartViewLimit;
    std::map<string, sensoreDanno*> mapSensor;

public:
    explicit content(QWidget* parent = nullptr);
    void eliminaSensore(sensoreDanno* sensore);
    sensoreDanno* getSelectedSensore() const;
    void inizializzaChart();
    void displayVector(sensoreDanno* sensore);
    void avviaSimulazione(sensoreDanno* sensore);
    void aggiungiSensoreAMappa(sensoreDanno* sensore);
    void updateSensore(sensoreDanno* updatedSensore);
    std::map<string, sensoreDanno*> getMapSensor();
public slots:
    void aggiungiSensoreAlContenuto(string sensoreName);
};

#endif
