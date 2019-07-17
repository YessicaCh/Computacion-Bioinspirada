#ifndef PERCEPTRON_H_INCLUDED
#define PERCEPTRON_H_INCLUDED
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
double respuesta (vector< pair<int,int> > entradas, int vias, vector<double> &pesos, int i)
{
    if ((vias * pesos[0] + entradas[i].first * pesos[1] + entradas[i].second * pesos[2]) > 0.0)
        return 1.0;
    return 0.0;

}
bool actualizar_pesos(vector<double> &pesos, double c_aprendizaje, double error, int valor_esperado,vector< pair<int,int> > entradas, int it, int vias)
{
    pesos[0]+= c_aprendizaje*error*vias;
    pesos[1]+= c_aprendizaje*error*entradas[it].first;
    pesos[2]+= c_aprendizaje*error*entradas[it].second;
    return 1;
}
bool perceptron(vector < pair<int,int> > entradas, double salidas [])
{
    int vias = 1;
    double constante_aprendizaje = 0.5;
    vector<double>  pesos = {0.0,0.0,0.0};
    bool existe_error = 1;
    double error;
    int cont = 0;
    while (existe_error && cont<5)
    {
        existe_error = 0;
        for (int i=0;i<4;i++)
        {
            error = salidas[i] - respuesta(entradas,vias,pesos,i);
            //cout<<"error "<<error<<endl;
            if (error!=0.0)
            {
                actualizar_pesos(pesos,constante_aprendizaje,error,salidas[i],entradas,i,vias);
                existe_error = 1;
                //cout<<"here";
            }
        }
        cont ++ ;
        if (existe_error == 0) break;
    }
    cout <<" peso vias "<<pesos[0]<<endl;
    cout <<" Peso 1  "<<pesos[1]<<endl;
    cout <<" Peso 2 "<<pesos[2]<<endl;
    return 1;
}
#endif // PERCEPTRON_H_INCLUDED
