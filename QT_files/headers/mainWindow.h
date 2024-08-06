#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "leftSideBar.h"
#include "content.h"
#include "rightSideBar.h"
#include <QSplitter>

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
