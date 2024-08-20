#ifndef SENSOREREPOSITORY_H
#define SENSOREREPOSITORY_H
//una sorta di dependecy injection
#include<list>

#include"core_files/headers/sensoreDanno.h"

using std::list;

class SensoreRepository{
private:
    list<sensoreDanno> listaSensoriDanno;
public:
    //sensoreDanno getSensoreByName(string name);
    void addSensore(sensoreDanno* sensore);
    void removeSensore(sensoreDanno* sensore);
};


#endif