#ifndef CONTENT_H
#define CONTENT_H

#include "viewlib.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QPointF>

class content : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* center;
    QLabel* grafichino;
    QLabel* sim;
    QString selectedSensore; // Memorizza il sensore selezionato
public:
    explicit content(QWidget* parent = nullptr);
    void avviaSimulazione();
    void eliminaSensore(const QString& sensoreName);
    QString getSelectedSensore() const;
    void mostraGrafico(const QVector<QPointF>& data);
public slots:
    void aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore);
};

#endif
