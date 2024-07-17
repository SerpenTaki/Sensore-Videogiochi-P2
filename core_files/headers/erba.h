#ifndef ERBA_H
#define ERBA_H

#include "magico.h"

class erba : public magico {
public:
  static const std::string tipo;
  // per implementazione grafica
  void accept(visitor &) override;

  erba();
  ~erba();

  string setStatus() override;
  double calcolaDanno() override;
  double getHit() override;
};

#endif
