#ifndef CONTENT_H   
#define CONTENT_H

#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QApplication>

class content: public QWidget{
private:
    QVBoxLayout* center;
    QLabel* grafichino;
public:
    content(QWidget* parent = nullptr);
public slots:
    void avviaSimulazione();

    void eliminaSensore();
};


#endif