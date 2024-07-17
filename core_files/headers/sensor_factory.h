#include "acqua.h"
#include "erba.h"
#include "fisico.h"
#include "fuoco.h"
#include "sacro.h"
#include "sensoreDanno.h"
class SensoreFactory {
public:
  enum TipoSensore { FISICO, SACRO, ERBA, FUOCO, ACQUA };

  static sensoreDanno *creaSensore(int tipo) {
    switch (tipo) {
    case SACRO:
      return new sacro();
    case ACQUA:
      return new acqua();
    case ERBA:
      return new erba();
    case FUOCO:
      return new fuoco();
    case FISICO:
      return new fisico();
    default:
      return nullptr;
    }
  }
};
