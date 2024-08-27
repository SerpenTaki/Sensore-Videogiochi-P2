#include "QT_files/headers/mainWindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QIcon>

int main(int argv, char** argc){
  QApplication SensoreGioco(argv, argc);
  MainW finestra;
  finestra.setWindowIcon(QIcon("assets/icon.jpg")); 
  finestra.resize(900,600);
  finestra.show();
  return SensoreGioco.exec();
}
