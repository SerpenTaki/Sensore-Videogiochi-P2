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

    aggiungiSensore* dialog = new aggiungiSensore(parent);
    content* contenuto = new content(parent);
    QObject::connect(dialog, &aggiungiSensore::sensoreAggiuntoStats, contenuto, &content::aggiungiSensoreAlContenuto);

}
