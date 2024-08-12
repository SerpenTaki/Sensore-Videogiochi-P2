#include "headers/mainWindow.h"

MainW::MainW(QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("Sensore Danni Gioco");

    mainWindow = new QHBoxLayout(this);
    splitter = new QSplitter(Qt::Horizontal, this);

    leftSideBarWidget = new leftSideBar(this);
    contentWidget = new content(this);
    rightSideBarWidget = new rightSideBar(contentWidget, leftSideBarWidget, this); // Passa leftSideBarWidget

    splitter->addWidget(leftSideBarWidget);
    splitter->addWidget(contentWidget);
    splitter->addWidget(rightSideBarWidget);

    mainWindow->addWidget(splitter);
    setLayout(mainWindow);

    connect(leftSideBarWidget, &leftSideBar::sensoreSelezionato, contentWidget, &content::eliminaSensore);

    aggiungiSensore* dialog = new aggiungiSensore(this);
    connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, contentWidget, &content::aggiungiSensoreAlContenuto);
}
