#include<QApplication>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QHBoxLayout>

class test: public QWidget{
private:
  QVBoxLayout* nuovo;
  QHBoxLayout* nuovo2;
  QHBoxLayout* grande;
public:
  test(QWidget* parent = nullptr): QWidget(parent){
    nuovo = new QVBoxLayout;
    QLabel* n = new QLabel("Nus");
    nuovo->addWidget(n); 
    QPushButton* bottone = new QPushButton("clicca qui");
    nuovo->addWidget(bottone);
    connect(bottone, &QPushButton::clicked, this /*classe dove si trova lo slot*/, &test::stampaN);
    nuovo2 = new QHBoxLayout;
    QLabel* negroni = new QLabel("Voglio Bere");
    nuovo2->addWidget(negroni);
    grande = new QHBoxLayout(this);
    grande->addLayout(nuovo);
    grande->addLayout(nuovo2);
  }
public slots:
  void stampaN() {
    QLabel* testo = new QLabel("ciao");
    nuovo->addWidget(testo);
  }
};

int main(int argv, char** argc){
  QApplication SensoreGioco(argv, argc);
  test t;
  t.show();
  return SensoreGioco.exec();
}