#include "QT_files/mainWindow.h"

int main(int argv, char** argc){
  QApplication SensoreGioco(argv, argc);
  MainW finestra;
  finestra.show();
  return SensoreGioco.exec();
}