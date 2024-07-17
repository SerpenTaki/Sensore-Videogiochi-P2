// #include "core_files/headers/sensoreDanno.h"
#include "qt_files/headers/mainw.h"
// #include <QApplication>
// #include <QBoxLayout>
// #include <QGroupBox>
// #include <QLabel>
// #include <QPushButton>

int main(int argc, char *argv[]) {
  std::list<sensoreDanno *> *lista_sensori;
  QApplication App(argc, argv);
  workspace w(lista_sensori);
  w.resize(800, 494);
  w.show();
  return App.exec();
}
