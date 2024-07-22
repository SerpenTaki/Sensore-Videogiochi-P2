#include"headers/fisico.h"
#include"headers/magico.h"
#include"headers/sacro.h"

int main(){
    vector<int> p;
    //      sacro(double d, int ph, int pc, vector<int> tpt, int lvFede, int limitbreak,vector<int> limitBar);
    fisico a(2.2, 5, 3, p, 5);
    magico b(2.2, 2, 3, p, 5, "sesso", true);
    sacro c(2.2, 3, 20, p, 4, 9, p);

    std::cout << a.getAffilatura() << std::endl;
    
    
}