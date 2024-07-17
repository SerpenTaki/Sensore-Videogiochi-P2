#include<QApplication>
#include<QLabel>

int main(int argv, char** argc){
  QApplication ciao(argv, argc);
  QLabel* porcodio = new QLabel("Sesso");
  porcodio->show();
  return ciao.exec();
}