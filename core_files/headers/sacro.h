#ifndef SACRO_H
#define SACRO_H

#include "sensoreDanno.h"

class sacro : public sensoreDanno {
private:
  int lvFede;     /* 0 , 1, 2 */
  int limitbreak; // quando il parametro raggiunge 10 hai vinto la partita,
  vector<int> limitBar; // mostra nuovo grafico del limit break
  enum { fedeBassa, fedeMedia, fedeAlta };
public:
  sacro(double d, int ph, int pc, vector<int> tpt, int lvFede, int limitbreak,vector<int> limitBar);


  int getLvFede() const;
  int getlimitBreak() const;

  double getHit() override;
  double calcolaDanno() override;
  
  bool checkLimit();
  void updateLimitbreak();
  vector<int> getValoriLimitBar();

  void accept(Visitor* v) override { v->visit(this); }
  
};

#endif
