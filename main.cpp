#include "QT_files/headers/mainWindow.h"

int main(int argv, char** argc){
  QApplication SensoreGioco(argv, argc);
  MainW finestra;
  //finestra.resize(800,600);
  finestra.show();
  return SensoreGioco.exec();
}
