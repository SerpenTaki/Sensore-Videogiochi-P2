#ifndef RIGHTSIDEBAR_H
#define RIGHTSIDEBAR_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>

#include"content.h"

class rightSideBar: public QWidget{
private:
    QVBoxLayout* right;
    QPushButton* avviaSimulaButt;
    QPushButton* modificaSensButt;
    QPushButton* eliminaSensButt;
    content* cont;
public:
    rightSideBar(content* c,QWidget* parent = nullptr);
public slots:
    void modificaSensore();
};

#endif