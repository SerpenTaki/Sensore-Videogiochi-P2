#include "headers/mainWindow.h"

MainW::MainW(QWidget* parent = nullptr)
 :QWidget(parent){
    mainWindow = new QHBoxLayout(this);
        //splitter = new QSplitter(Qt::Horizontal, this);
        //leftSideBarWidget = new leftSideBar(this);
        //mainWindow->addLayout(leftSideBarWidget->getLeftLayout());
        
        //splitter->addWidget(leftSidebarWidget);
    splitter = new QSplitter(Qt::Horizontal, this);

    leftSideBarWidget = new leftSideBar(this);
    contentWidget = new content(this);
    rightSideBarWidget = new rightSideBar(contentWidget, this);

    splitter->addWidget(leftSideBarWidget);
    splitter->addWidget(contentWidget);
    splitter->addWidget(rightSideBarWidget);

    mainWindow->addWidget(splitter);

    setLayout(mainWindow);
}