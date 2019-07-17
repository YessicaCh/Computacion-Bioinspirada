#include <iostream>
#include "Perceptron.h"
using namespace std;
int main()
{
    double  Andsalidas []= {0.0,0.0,0.0,1.0};
    double  Orsalidas []= {0.0,1.0,1.0,1.0};
    double  Xorsalidas []= {0.0,1.0,1.0,0.0};
    pair <int,int> entrada1 (0,0);
    pair <int,int> entrada2 (0,1);
    pair <int,int> entrada3 (1,0);
    pair <int,int> entrada4 (1,1);
    vector < pair<int,int> > entradas;
    entradas.push_back(entrada1);
    entradas.push_back(entrada2);
    entradas.push_back(entrada3);
    entradas.push_back(entrada4);
    /*Perceptron*/
    cout<<"Resultado And"<<endl;
    perceptron(entradas,Andsalidas);
    cout<<"Resultado Or"<<endl;
    perceptron(entradas,Orsalidas);
    cout<<"-------------------------------------------"<<endl;
    /* MLP */
    cout<<"Resultado Xor MLP"<<endl;
    cout << "Hello world!" << endl;
    return 0;
}
