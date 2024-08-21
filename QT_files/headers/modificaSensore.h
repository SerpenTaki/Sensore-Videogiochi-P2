#ifndef MODIFICASENSORE_H
#define MODIFICASENSORE_H

#include "aggiungiSensore.h"
#include "core_files/headers/sensoreDanno.h"

class modificaSensore : public aggiungiSensore {
    Q_OBJECT
private:
    sensoreDanno* sensoreDaModificare;

public:
    modificaSensore(QWidget* parent = nullptr, sensoreDanno* sensoreDaModificare = nullptr);

    void caricaDatiSensore();  // Funzione per caricare i dati del sensore esistente
    void confermaClicked();

signals:
    void sensoreModificato(const QString& sensoreName);
    void sensoreModificatoStats(sensoreDanno* sensoreModificato);
};

#endif // MODIFICASENSORE_H
