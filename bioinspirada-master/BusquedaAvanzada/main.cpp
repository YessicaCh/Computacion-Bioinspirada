#include <iostream>
#include "genetico.h"
#include "hillClimbing.h"
#include "simulatedAnnealing.h"
using namespace std;
inline int maximizar(int num)
{
    return (int)pow(num,2);
}

int main()
{
    vector < pair<double,double> > datG,datA,datC;
    int sol1 = aGenetico(maximizar,datG);
    int sol2 = sAnnealing(maximizar,datA);
    int sol3 = hClimbing(maximizar,datC);
    cout<<"Solucion con algoritmo genetico "<<sol1<<endl;
    cout<<"Solucion con simulated annealing "<<sol2<<endl;
    cout<<"Solucion con hill climbing "<<sol3<<endl;
    cout << "Hello world!" <<endl;
    return 0;
}
