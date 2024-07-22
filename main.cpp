#include<QApplication>
#include<QLabel>

int main(int argv, char** argc){
  QApplication SensoreGioco(argv, argc);
  QLabel* finestra = new QLabel("Sensore Danno");
  finestra->show();
  return SensoreGioco.exec();
}