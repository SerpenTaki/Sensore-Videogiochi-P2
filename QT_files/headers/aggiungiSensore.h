#ifndef AGGIUNGISENSORE_H
#define AGGIUNGISENSORE_H

#include<QDialog>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QCheckBox>
#include<QRadioButton>
#include<QDebug>
#include <QSpinBox>

class aggiungiSensore: public QDialog{
    Q_OBJECT
private:
    QVBoxLayout* nuovoSens;
    QRadioButton *checkBoxFisico;
    QRadioButton *checkBoxMagico;
    QRadioButton *checkBoxSacro;
    QSpinBox *DannoBase;
    QSpinBox *NumeroDiTurni;
    QPushButton* annulla;
    QWidget *dynamicWidget;
    QVBoxLayout *dynamicLayout;
public:
    QPushButton* conferma;
    QLineEdit* nomeSensoreInserimento;

    aggiungiSensore(QWidget* parent = nullptr);

    void changeUIForOption1();
    void changeUIForOption2();
    void changeUIForOption3();
    void clearDynamicWidget();

public slots:
    void onRadioButtonToggled();
    void confermaClicked();
signals:
    void sensoreAggiunto(const QString& sensoreName); 
};



#endif