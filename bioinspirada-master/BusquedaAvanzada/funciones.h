#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <bits/stdc++.h>
#include <time.h>
#include <utility>
using namespace std;

string int_to_bits(int numero)
{
    int dividendo = numero, resto, divisor = 2, maxBits = 4, cociente;
    string binario = "";
    while(dividendo > 1)
    {
        cociente = dividendo / divisor;
        resto = dividendo % 2;
        if(resto == 1)
            binario += "1";
        else
            binario += "0";
        dividendo = cociente;
    }
    if(dividendo == 1)     binario += "1";
    else binario += "0";
    while((int)binario.size()<maxBits) binario += "0";
    string aux="";
    for (int i=maxBits-1;i>-1;i--)
        aux+=binario[i];
    //cout << "En sistema binario " << numero<< " se escribe " <<aux<<endl ;
    return aux;
}

int bit_to_int (string bin)
{
    int num=0;
    for (int i=bin.size()-1,j=0;i>-1;i--,j++)
    {
        if (bin[i] == '1') num += pow(2,j);
    }
    //cout<<endl<<"Este es el numero: "<<num<<endl;
    return num;
}

int Probabilidad (int tam, int valores[], double T)
{
    double valoresExp[tam];
    int i;
    double total = 0.0;
    /*Se halla el total y los nuevos valores con la funcion exponecial*/
    for (i = 0; i<tam; i++)
    {
        valoresExp[i] = exp(valores[i]/T);
        total += valoresExp[i];
    }
    /*Probabilidad de cada valor*/
    for (i = 0; i<tam; i++) valoresExp[i] = valoresExp[i]/total;
    /*Encontrar la posicion del mayor*/
    i = 0;
    double mayor = valoresExp[i];
    for (int j = 1; j<tam;j++)
    {
        if (mayor < valoresExp[j])
        {
            mayor = valoresExp[j];
            i = j;
        }
    }
    return i;
}
#endif // FUNCIONES_H_INCLUDED
