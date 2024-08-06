#ifndef CONTENT_H
#define CONTENT_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QApplication>

class content : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* center;
    QLabel* grafichino;
    QLabel* sim;
    QString selectedSensore; // Memorizza il sensore selezionato
public:
    explicit content(QWidget* parent = nullptr);
    void avviaSimulazione();
    void eliminaSensore(const QString& sensoreName);
    void aggiornaContenuto(const QString& sensoreName);
    void visualizzaSensore(const QString& sensoreName);
    QString getSelectedSensore() const; // Aggiungi questo metodo
};

#endif