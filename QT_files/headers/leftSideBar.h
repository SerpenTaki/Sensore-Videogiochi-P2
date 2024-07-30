#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QDebug>

#include"aggiungiSensore.h"

class leftSideBar: public QWidget{
private:
    QVBoxLayout* left;
    QPushButton* aggiungiSensoreBottone;
    QLineEdit* searchBox;
    aggiungiSensore* sensoreWidget;
public:
    leftSideBar(QWidget* parent = nullptr);

public slots:
    void stampaSelSensore();

    void eseguiRicerca(const QString& text);
};


#endif