#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "leftSideBar.h"
#include<QHBoxLayout>


class MainW: public QWidget{
private:
  QHBoxLayout* mainWindow;
  leftSideBar* leftSideBarWidget;
public:
    MainW(QWidget* parent = nullptr):QWidget(parent){
        mainWindow = new QHBoxLayout(this);
        leftSideBarWidget = new leftSideBar(this);
        mainWindow->addLayout(leftSideBarWidget->getLeftLayout());
    }
};


#endif