#include"gestoreSensori.h"

sensoreDanno* GestoreSensori::creaSensore(const QString& tipo, double danno, int probHit, int probCrit, std::vector<int> tpt, int extra1, int extra2, bool status, const QString& statusStr) {
    if (tipo == "Fisico") {
        return new fisico(danno, probHit, probCrit, tpt, extra1); // extra1 è affilatura
    } else if (tipo == "Magico") {
        return new magico(danno, probHit, probCrit, tpt, extra1, statusStr.toStdString(), status); // extra1 è livello di magia
    } else if (tipo == "Sacro") {
        std::vector<int> limitBar = { 0 }; // Supponiamo un valore di default per limitBar
        return new sacro(danno, probHit, probCrit, tpt, extra1, extra2, limitBar); // extra1 è livello fede, extra2 è limitbreak
    } else {
        // Tipo di sensore non riconosciuto
        return nullptr;
    }
}