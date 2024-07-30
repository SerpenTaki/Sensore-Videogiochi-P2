#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QDebug>

class leftSideBar: public QWidget{
private:
    QVBoxLayout* left;
    QPushButton* aggiungiSensoreBottone;
    QLineEdit* searchBox;
public:
    leftSideBar(QWidget* parent = nullptr);

public slots:
    void stampaSelSensore();

    void eseguiRicerca(const QString& text);
};


#endif