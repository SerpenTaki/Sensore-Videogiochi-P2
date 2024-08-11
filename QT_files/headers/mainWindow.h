#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewlib.h"
#include "leftSideBar.h"
#include "content.h"
#include "rightSideBar.h"

class MainW : public QWidget {
private:
    QHBoxLayout* mainWindow;
    QSplitter* splitter;
    leftSideBar* leftSideBarWidget;
    content* contentWidget;
    rightSideBar* rightSideBarWidget;

public:
    explicit MainW(QWidget* parent = nullptr);
};

#endif
