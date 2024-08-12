#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include "viewlib.h"
#include"aggiungiSensore.h"
#include"content.h"

class leftSideBar : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* left;
    QPushButton* aggiungiSensoreBottone;
    QPushButton* salvaSensoriBottone; // Pulsante per XML
    QPushButton* salvaJsonBottone; // Nuovo pulsante per JSON
    QLineEdit* searchBox;
    vector<sensoreDanno*>* sensoreList;
    QListWidget* sensoreListLabel;
    content* contentWidget;
public:
    leftSideBar(content* contentWidget ,QWidget* parent = nullptr);

public slots:
    void stampaSelSensore();
    void eseguiRicerca(const QString& text);
    void aggiungiSensoreToList(sensoreDanno* sensore);
    void eliminaSensore(sensoreDanno* sensore);
signals:
    void sensoreSelezionato(sensoreDanno* sensore);
};

#endif // LEFTSIDEBAR_H
