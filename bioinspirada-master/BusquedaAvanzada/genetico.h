#ifndef GENETICO_H_INCLUDED
#define GENETICO_H_INCLUDED
#include "funciones.h"
double TR = 10, TM = 10;
string reproduccion (string ind1, string ind2, int (*fitness)(int))
{
    string nuevo="";
    int aux1 = bit_to_int(ind1), aux2 = bit_to_int(ind2);
    int valores [] = {fitness(aux1), fitness(aux2)};
    int i = Probabilidad(2,valores,TR);
    TR-=0.1;
    //cout<<"El individuo que da sus valores altos es: "<<i<<endl;
    if (i == 0)
    {
        swap(ind1[2],ind2[2]);
        swap(ind1[3],ind2[3]);
    }
    else
    {
        swap(ind1[0],ind2[0]);
        swap(ind1[1],ind2[1]);
    }
    //cout <<"El hijo es" <<ind1<<endl;
    return ind1;
}

string mutacion(string ind)
{
    int distribucion [] = {4,3,2,1};
    int j = Probabilidad(4,distribucion,TM);
    TM-=0.1;
    //cout<<"El bit que muta es: "<<j<<endl;
    //cout <<"individuo antes de la mutacion" <<ind<<endl;
    if (ind[j] == '0') ind[j] = '1';
    else ind[j] = '0';
   //cout <<"este es el individuo" <<ind<<endl;
    return ind;
}

int aGenetico(int(*fitness)(int), vector< pair<double,double> > &data)
{
    string bit1,bit2;
    int solucion = 0;
    double tiempo = 1.0;
    vector < pair<double,double> > datos;
    double it = 0;
    /*Seleccion de individuos random dentro del espacio de soluciones*/
    srand(time(NULL));
    int ind1 = rand() % 16 , ind2= rand() % 16;
    bit1 = int_to_bits(ind1);
    bit2 = int_to_bits(ind2);
    do
    {
        ind1 = bit_to_int(bit1);
        ind2 = bit_to_int(bit2);
        pair<double,int> dat;
        dat.first =(fitness(ind1)+fitness(ind2))/2;
        dat.second = it;
        datos.push_back(dat);
        it++;
        string aux1,aux2;
        //cout << "Individuos! " <<ind1 <<" "<<ind2<< endl;
        if (fitness(ind1) > fitness(ind2))
        {
            solucion = ind1;
            aux2 = mutacion(bit2);
        }
        else
        {
            solucion = ind2;
            aux2 = mutacion(bit1); //Seleccion
        }
        aux1 = reproduccion(bit1,bit2,fitness);
        bit1 = aux1;
        bit2 = aux2;
        tiempo -= 0.01;
    }while (tiempo > 0.0 );
    //cout <<"La solucion es: "<<solucion<<endl;
    data=datos;
    return solucion;
}



#endif // GENETICO_H_INCLUDED
