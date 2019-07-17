#ifndef AGENTE_H_INCLUDED
#define AGENTE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include "Nido.h"
using namespace std;
int Contener(vector <vector<int>> aux, int x, int y) //funcion para saber si una cordenada esta contenido en un vector de vectores
{
    if (aux.empty()) return -1;
    int tam=aux.size(),i;
    for (i=0;i<tam;i++)
    {
        if (aux[i][0]==x && aux [i][1]==y)  return i;
    }
    return -1;
}
struct Agente
{
    int posx,posy; //posicion en la grilla del agente
    char name; //nombre del agente
    bool cargandoComida; // si esta cargando comida o no
    Agente(int x, int y, char nombre)
    {
        posx=x;
        posy=y;
        name=nombre;
        cargandoComida=0;
    }
    void Print()
    {
        cout<<endl<<"Agente :"<<name<<" carga "<<cargandoComida<<" de comida"<<endl;
    }

    void PonerFeromona (char **&tab,vector< vector<int>> &fero,vector <char> &fer,
                        int x , int y) //Funcion para poner la feromona al lugar al que va
    {
        int Iterador=Contener(fero,x,y);
        if (Iterador==-1)
        {
            vector<int>aux={x,y};
            fero.push_back(aux);
            fer.push_back('1');
            tab[y][x]=' ';
            return;
        }
        fer[Iterador]+=1;
        return;
    }
    //funcion para percibir si existe el nido o la comida cerca
    bool Percibir (char **&tab,int Size,vector< vector<int>> &fero, vector<char> &fer)
    {
        if (posx+1<Size && (tab[posy][posx+1]=='C' || tab[posy][posx+1]=='N')) //a la derecha
        {
            PonerFeromona(tab,fero,fer,posx,posy);
            posx+=1;
            return 1;
        }
        if (posx-1>-1 && (tab[posy][posx-1]=='C' || tab[posy][posx-1]=='N')) //a la izquierda
        {
            PonerFeromona(tab,fero,fer,posx,posy);
            posx-=1;
            return 1;
        }
        if (posy+1<Size && (tab[posy+1][posx]=='C' || tab[posy+1][posx]=='N')) // arriba
        {
            PonerFeromona(tab,fero,fer,posx,posy);
            posy+=1;
            return 1;
        }
        if (posy-1>-1 && (tab[posy-1][posx]=='C' || tab[posy-1][posx]=='N')) //abajo
        {
            PonerFeromona(tab,fero,fer,posx,posy);
            posy-=1;
            return 1;
        }
        return 0;
    }
    //Funcion probabilistica para moverse en base a las feromonas
    bool Pferomonas(char ** &tab,int Size,vector< vector<int>> &fero, vector<char> &fer)
    {
        bool moverse=0;
        int auxX=posx,auxY=posy;
        double Max=-1.0;
        double t=0.5;
        int derecha=(tab[auxY][auxX+1]-'0');
        int izquierda=(tab[auxY][auxX-1]-'0');
        int abajo=(tab[auxY+1][auxX]-'0');
        int arriba=(tab[auxY-1][auxX]-'0');
        double total =exp(derecha/t)+exp(izquierda/t)+exp(abajo/t)+exp(arriba/t);
        if (auxX+1<Size &&  (exp(derecha/t)/total)>Max) //a la derecha
        {
            Max=exp(derecha/t)/total;
            moverse=1;
            posx=auxX;
            posx+=1;
            if (tab[auxY][auxX+1]!=' ') moverse=0;
        }
        if (auxX-1>-1 &&  (exp(izquierda/t)/total)>Max) //a la izquierda
        {
            Max=exp(izquierda/t)/total;
            moverse=1;
            posx=auxX;
            posx-=1;
            if (tab[auxY][auxX-1]!=' ') moverse=0;
        }
        if (auxY+1<Size &&  (exp(abajo/t)/total)>Max) // arriba
        {
            Max=exp(abajo/t)/total;
            moverse=1;
            posy=auxY;
            posy+=1;
            if (tab[auxY+1][auxX]!=' ') moverse=0;
        }
        if (auxY-1>-1 && (exp(arriba/t)/total)>Max) //abajo
        {
            Max=exp(arriba/t)/total;
            moverse=1;
            posy-=1;
            if (tab[auxY-1][auxX]!=' ') moverse=0;
        }
        if (moverse)
        {
            PonerFeromona(tab,fero,fer,posx,posy);
            return moverse;
        }
        posx=auxX;
        posy=auxY;
        return moverse;
    }
//    bool Pferomonas(char ** &tab,int Size,vector< vector<int>> &fero, vector<char> &fer)
//    {
//        bool moverse=0;
//        int mayor=0, auxX=posx,auxY=posy;
//        if (posx+1<Size && tab[auxY][auxX+1]!=' ' && (tab[auxY][auxX+1]-'0')>mayor) //a la derecha
//        {
//            moverse=1;
//            mayor=tab[auxY][auxX+1]-'0';
//            posx=auxX;
//            posx+=1;
//        }
//        if (posx-1>-1 && tab[auxY][auxX-1]!=' ' && (tab[auxY][auxX-1]-'0')>mayor) //a la izquierda
//        {
//            moverse=1;
//            mayor=tab[auxY][auxX-1]-'0';
//            posx=auxX;
//            posx-=1;
//        }
//        if (posy+1<Size && tab[auxY+1][auxX]!=' ' && (tab[auxY+1][auxX]-'0')>mayor) // arriba
//        {
//            moverse=1;
//            mayor=tab[auxY+1][auxX]-'0';
//            posy=auxY;
//            posy+=1;
//        }
//        if (posy-1>-1 && tab[auxY-1][auxX]!=' ' && (tab[auxY-1][auxX]-'0')>mayor) //abajo
//        {
//            moverse=1;
//            mayor=tab[auxY-1][auxX];
//            posy-=1;
//        }
//        if (moverse)
//        {
//            PonerFeromona(tab,fero,fer,posx,posy);
//            return moverse;
//        }
//        return moverse;
//    }
    //Funcion para moverse
    void Move(char **& tab, int Size, Nido *&nido, vector< vector <int>> &comida,vector< vector <int>> &feromona,
              vector<char> &fer)
    {
        int auxX=posx, auxY=posy;
        if (Percibir(tab,Size,feromona,fer)) //movimiento en base al nido y la comida
        {
            if (tab[posy][posx]=='N'&& cargandoComida==1)
            {
                nido->comida+=1;
                cargandoComida=0;
                return;
            }
            if (tab[posy][posx]=='C'&& cargandoComida==0)
            {
                cargandoComida=1;
                int aux = Contener(comida,auxX,auxY);
                comida.erase (comida.begin()+(aux+1));
                return; //si retorna 1 se borra la posicion de la comida del vector
            }
            return;
        }
        else if (Pferomonas(tab,Size,feromona,fer)) return; //movimiento en base a la feromona
        else //movimiento aleatorio
        {
            PonerFeromona (tab,feromona,fer,auxX,auxY);
            int accion=rand() % 5;
 //           accion=0;
            if (accion==0 && posx+1<Size)//derecha
            {
                posx+=1;
                //cout<<endl<<"here"<<posx<<endl;
                return;
            }
            if (accion==1 && posx-1>-1)//izquierda
            {
                posx-=1;
                return;
            }
            if (accion==2 && posy+1<Size)//arriba
            {
                posy+=1;
                return;
            }
            if (accion==3 && posy-1>-1)//abajo
            {
                posy-=1;
                return;
            }
            return;
        }
    }
};

#endif // AGENTE_H_INCLUDED
