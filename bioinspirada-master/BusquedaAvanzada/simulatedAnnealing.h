#ifndef SIMULATEDANNEALING_H_INCLUDED
#define SIMULATEDANNEALING_H_INCLUDED
#include "funciones.h"
/*Transición*/

int generar(int sol,int T)
{
    int distribucion [] = {4,3,2,1};
    int j = Probabilidad(4,distribucion,T);
    //cout<<"El bit que muta es: "<<j<<endl;
    string ind = int_to_bits(sol);
    //cout <<"individuo antes de la mutacion" <<ind<<endl;
    if (ind[j] == '0') ind[j] = '1';
    else ind[j] = '0';
    //cout <<"este es el individuo" <<ind<<endl;
    return bit_to_int(ind);
}

bool aceptar(int lastValue,int newValue, int T, int(*eval)(int))
{
    int valor1 = eval(lastValue) / (eval(lastValue) + eval(newValue));
    int valor2 = (eval(newValue) + T*eval(newValue)) / (eval(lastValue) + eval(newValue));
    return valor1<valor2;
}

int sAnnealing(int(*eval)(int),vector< pair<double,double> > &data)
{
    vector <pair<double,double> > datos;
    double it = 0;
    double T=0.5;
    int paso = 0;
    srand(time(NULL));
    int sol = rand() % 16;
    int valor = eval(sol);
   // double tiempo = 1.0;
    do
    {
        do
        {
            paso++;
            int nuevaSol = generar (sol,T);
            int nuevoValor = eval(nuevaSol);
            if (aceptar(valor,nuevoValor,T,eval))
            {
                sol = nuevaSol;
                valor = nuevoValor;
            }
        }while(paso < 10);
        pair<double,double> aux;
        aux.first = eval(sol);
        aux.second = it;
        datos.push_back(aux);
        it++;
        paso = 0;
        T-=0.01;
    }while( T>0.01 );
    data=datos;
    return sol;
}


#endif // SIMULATEDANNEALING_H_INCLUDED
