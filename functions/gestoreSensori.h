#ifndef GESTORESENSORI_H
#define GESTORESENSORI_H


#include <QString>
#include <vector>
#include"core_files/headers/sensoreDanno.h"
#include"core_files/headers/fisico.h"
#include"core_files/headers/magico.h"
#include"core_files/headers/sacro.h"

class sensoreDanno;  // Dichiarazione forward delle classi sensoreDanno e derivate
class fisico;
class magico;
class sacro;

class GestoreSensori {
public:
    // Metodo per creare sensori
    sensoreDanno* creaSensore(const QString& tipo, double danno, int probHit, int probCrit, std::vector<int> tpt, int extra1 = 0, int extra2 = 0, bool status = false, const QString& statusStr = "");
};

#endif
