#ifndef AGGIUNGISENSORE_H
#define AGGIUNGISENSORE_H

#include"viewlib.h"
#include<map>

class aggiungiSensore : public QDialog {
    Q_OBJECT
    friend class modificaSensore;
private:
    QVBoxLayout* nuovoSens;
    QRadioButton *checkBoxFisico;
    QRadioButton *checkBoxMagico;
    QRadioButton *checkBoxSacro;
    QLabel* insNome;
    QLabel* selezionaTipo;
    QSpinBox *DannoBase;
    QSpinBox *NumeroDiTurni;
    QSpinBox *AttPerTurno;
    QPushButton* annulla;
    QWidget *dynamicWidget;
    QVBoxLayout *dynamicLayout;
    QCheckBox* StatusApp;
    QSpinBox* PAffilatura;
    QSpinBox* SLvMagia;
    QSpinBox* SLvFede;
    std::map<string, sensoreDanno*> existingSensors;
public:
    QPushButton* conferma;
    QLineEdit* nomeSensoreInserimento;

    aggiungiSensore(QWidget* parent = nullptr, std::map<string, sensoreDanno*> existingSensors = std::map<string, sensoreDanno*>());

    void changeUIForOption1();  // Fisico
    void changeUIForOption2();  // Magico
    void changeUIForOption3();  // Sacro
    void clearDynamicWidget();

public slots:
    void onRadioButtonToggled();
    void confermaClicked();
signals:
    void sensoreAggiunto(const QString& sensoreName);
    void sensoreAggiuntoStats(sensoreDanno* nuovoSensore);
};

#endif // AGGIUNGISENSORE_H
