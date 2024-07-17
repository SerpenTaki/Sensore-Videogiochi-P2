#ifndef SACRO_H
#define SACRO_H

#include "sensoreDanno.h"

class sensoreDanno;

class sacro : public sensoreDanno {
private:
  int lvFede;     /* 0 , 1, 2 */
  int limitbreak; // quando il parametro raggiunge 10 hai vinto la partita,
                  // mostra nuovo grafico del limit break
  enum { fedeBassa, fedeMedia, fedeAlta };

public:
  static const std::string tipo;

  sacro();
  sacro(double d, int ph, int pc, vector<int> tpt, int lvFede, int limitbreak);

  ~sacro();

  int getLvFede() const;
  int getlimitBreak() const;

  double getHit() override;
  bool checkLimit();
  void updateLimitbreak();
  double calcolaDanno() override;

  // per implementazione grafica
  void accept(visitor &) override;
  vector<int> limitBar;

  sacro(double d, int ph, int pc, vector<int> tpt, int lvFede, int limitbreak,
        vector<int> limitBar);

  vector<int> getValoriLimitBar();
};

#endif
