#ifndef CONTENT_H
#define CONTENT_H

#include "viewlib.h"

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
public slots:
    void aggiungiSensoreAlContenuto(sensoreDanno* nuovoSensore);

};

#endif