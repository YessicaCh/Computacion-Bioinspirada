#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>
#include <bits/stdc++.h>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

string int_to_string(int n)
{
	stringstream ss;
	ss<<n;
	return ss.str();
}

string double_to_str(double a)
{
    ostringstream sstream;
    sstream << a;
    string varAsString = sstream.str();
    return varAsString;
}

int str_to_int(string s)
{

    string str = s;
    istringstream buffer(str);
    int value;
    buffer >> value;
    return value;
}

int str_to_int2(string a)
{
    int valor = 0;
    for (int i = a.size()-1, aux = 1; i>-1;i--,aux*=10)
        valor += (a[i]-'0')*aux;
    return valor;
}

string to_string(int n)
{
	stringstream ss;
	ss<<n;
	return ss.str();
}

char str_to_char(string s)
{
	return s[0];
}

string char_to_string(char a)
{
	string aux="";
	aux+=a;
	return aux;
}

/*Funcion para escribir un string en un vector*/
bool str_to_txt(string ficher, string escribir)
{
    fstream fichero;
    escribir += "\n";
    fichero.open(ficher.c_str(), ios::out |ios::app);
    if (fichero.is_open())
    {
        fichero << escribir;
        fichero.close();
    }
    else
    {
        return 0;
        cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
    }
    return 1;
}

int Find (vector<double> aux, double value)
{
    for (int i = 0 ; i< (int)aux.size();i++)
    {
        if (aux[i]==value) return i;
    }
    return -1;
}


#endif // FUNCIONES_H_INCLUDED
