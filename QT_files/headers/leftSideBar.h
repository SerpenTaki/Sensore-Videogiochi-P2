#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include "viewlib.h"
#include"aggiungiSensore.h"
#include"content.h"
#include"core_files/headers/sensoreDanno.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QString>
#include <QStringList>
#include <QVector>
#include <iostream>

class leftSideBar : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* left;
    QPushButton* aggiungiSensoreBottone;
    QPushButton* importaSensoreBottone;
    QPushButton* salvaSensoreBottone;
    QLineEdit* searchBox;
    QListWidget* sensoreListLabel;
    content* contentWidget;
public:
    leftSideBar(content* contentWidget ,QWidget* parent = nullptr);

public slots:
    void stampaSelSensore();
    void eseguiRicerca(const QString& text);
    void aggiungiSensoreToList(sensoreDanno* sensore);
    void eliminaSensore(string sensorName);
    void salvaSensoreXML();
    std::vector<double> convertQListToStdVector(const QList<double>& list);
    std::vector<int> convertQListToStdVector(const QList<int>& list);
    void importaSensore();
    void updateSensore(sensoreDanno* updatedSensore);

signals:
    void sensoreSelezionato(string sensorName);
};

#endif // LEFTSIDEBAR_H
