#include "headers/mainWindow.h"

MainW::MainW(QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("Sensore Danni Gioco");
    mainWindow = new QHBoxLayout(this);
    splitter = new QSplitter(Qt::Horizontal, this);

    contentWidget = new content(this);
    leftSideBarWidget = new leftSideBar(contentWidget ,this);
    rightSideBarWidget = new rightSideBar(contentWidget, leftSideBarWidget, this); // Passa leftSideBarWidget

    splitter->addWidget(leftSideBarWidget);
    splitter->addWidget(contentWidget);
    splitter->addWidget(rightSideBarWidget);

    QList<int> sizes;
    sizes << 175 << 500 << 150; // Dimensione leftSideBarWidget, contentWidget, rightSideBarWidget
    splitter->setSizes(sizes);

    mainWindow->addWidget(splitter);
    setLayout(mainWindow);

    connect(leftSideBarWidget, &leftSideBar::sensoreSelezionato, contentWidget, &content::aggiungiSensoreAlContenuto);

    //aggiungiSensore* dialog = new aggiungiSensore(this);
}
