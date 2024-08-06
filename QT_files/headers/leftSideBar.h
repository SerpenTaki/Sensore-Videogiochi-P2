#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QDebug>
#include <QListWidget>

#include"aggiungiSensore.h"

class leftSideBar: public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* left;
    QPushButton* aggiungiSensoreBottone;
    QLineEdit* searchBox;
    QListWidget* sensoreList;
    QStringList sensori; 
public:
    leftSideBar(QWidget* parent = nullptr);

public slots:
    void stampaSelSensore();
    void eseguiRicerca(const QString& text);
    void aggiungiSensoreToList(const QString& sensoreName);
signals:
    void sensoreSelezionato(const QString& sensoreName);
};


#endif