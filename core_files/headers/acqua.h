#ifndef ACQUA_H
#define ACQUA_H
#include "magico.h"
class visitor;

class acqua : public magico {
public:
  // per implementazione grafica
  void accept(visitor &) override;
  static const std::string tipo;

  acqua();
  ~acqua();

  std::string setStatus() override;
  double calcolaDanno() override;
  double getHit() override;
};

#endif
