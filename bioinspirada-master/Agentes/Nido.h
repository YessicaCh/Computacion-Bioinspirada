#ifndef NIDO_H_INCLUDED
#define NIDO_H_INCLUDED
#include <vector>
#include <iostream>
using namespace std;
struct Nido
{
    char name;
    int posx,posy;
    int comida;
    Nido(int x, int y)
    {
        posx=x;
        posy=y;
        name='N';
        comida=0;
    }
    void print()
    {
        cout<<endl<<"Cantidad de comida en el nido: "<<comida<<endl;
    }
};
#endif // NIDO_H_INCLUDED
