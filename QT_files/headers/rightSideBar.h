#ifndef RIGHTSIDEBAR_H
#define RIGHTSIDEBAR_H

#include "viewlib.h"
#include "content.h"
#include "leftSideBar.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class rightSideBar : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* right;
    QPushButton* avviaSimulaButt;
    QPushButton* modificaSensButt;
    QPushButton* eliminaSensButt;
    content* cont;
    leftSideBar* leftSide;
public:
    explicit rightSideBar(content* c, leftSideBar* l, QWidget* parent = nullptr);

public slots:
    void modificaSensore();
    void eliminaSensore();
    void avviaSimulazione();  // Nuovo slot per avviare la simulazione e mostrare il grafico
};

#endif
