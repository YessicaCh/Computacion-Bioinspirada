#include <iostream>
#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <vector>    /* time */
#include <math.h>

using namespace std;
// abejas empleadas van explorando soluciones halladas en la vencidad de soluciones
class  AbejasEmpleadas
{
public:
	 AbejasEmpleadas();
	
};
//Abejas Expectadoras son las que van explotando las soluciones
class  AbejasExpectadoras
{
public:
	 AbejasExpectadoras();
	
};
//son las que eligen nuevas soluciones aleatoriamente
class AbejasBusqueda
{
public:
	 AbejasBusqueda();
};

//colonia
class CA
{
	public:
		CA(int tc,int d,int maxIter);
		float fitness(float x);//funcion fitness
		float f(float x,float y);
		float prob();
		float run();

	public:
		int TC;//# de abejas
		int LE;//# maximo de veces que puede explorar una solucion
		int D;//# de variables
		int MaxIter;
		//revisa unixABC EN GITHUB
};
CA::CA(int tc,int d,int mIter){
	TC=tc;
	D=d;
	MaxIter=mIter;
	LE=(TC*D)/2;
}
float CA::f(float x,float y){

}

float CA::fitness(float x){

}
int main()
{
	cout<<"----------------------------------------"<<endl;
    cout<<"-----------Practica 9--------------"<<endl;
    cout<<"----------------------------------------"<<endl;
   /* CO Hamilton(20,8,"PV");
    Hamilton.ejecutar();*/
	//cout<<"Rand "<<RandFloatBetween(1,3)<<endl;
	return 0;
}