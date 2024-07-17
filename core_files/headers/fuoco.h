#ifndef FUOCO_H
#define FUOCO_H

#include "magico.h"

class fuoco : public magico {
public:
  static const std::string tipo;
  // per implementazione grafica
  void accept(visitor &) override;

  fuoco();
  ~fuoco();

  string setStatus() override;
  double calcolaDanno() override;
  double getHit() override;
};

#endif
