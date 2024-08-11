#ifndef CONTENT_H
#define CONTENT_H

#include "viewlib.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QPointF>
#include "core_files/headers/sensoreDanno.h" 

class content : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* center;
    QLabel* grafichino;
    QLabel* sim;
    QString selectedSensore;
    sensoreDanno* sensore; 

public:
    explicit content(QWidget* parent = nullptr);
    void eliminaSensore(const QString& sensoreName);
    QString getSelectedSensore() const;
    void mostraGrafico(const QVector<QPointF>& data);

public slots:
    void aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore);
    void mostraGraficoSensore(); 
};

#endif
