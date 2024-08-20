#include"sensoreRepository.h"
/*
sensoreDanno SensoreRepository::getSensoreByName(string name){
    for(auto i = listaSensoriDanno.begin(); i == listaSensoriDanno.end(); ++i){
        if((i)->getNome() == name){
            return *i;
        }
    }
}*/

void SensoreRepository::addSensore(sensoreDanno* sensore){
    // il chiamante ha già verificato che non esiste un sensore avente lo stesso nome
   // listaSensoriDanno.push_back(*sensore);
}

void SensoreRepository::removeSensore(sensoreDanno* sensore){
    //il chiamante ha chiamato la GetSensoreByName, riceve il sensore per puntatore quindi posso provare a rimuoverlo direttamente
  //  listaSensoriDanno.remove(*sensore);
}