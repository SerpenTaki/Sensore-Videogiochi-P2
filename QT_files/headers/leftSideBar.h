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
    QListWidget* sensoreList;
    QStringList sensori;
    content* contentWidget;
public:
    leftSideBar(content* contentWidget ,QWidget* parent = nullptr);

public slots:
    void stampaSelSensore();
    void eseguiRicerca(const QString& text);
    void aggiungiSensoreToList(const QString& sensoreName);
    void eliminaSensore(const QString& sensoreName);
    void salvaSensori(); // Funzione per salvare in XML
    void salvaSensoriJson(); // Funzione per salvare in JSON
signals:
    void sensoreSelezionato(const QString& sensoreName);
};

#endif // LEFTSIDEBAR_H
