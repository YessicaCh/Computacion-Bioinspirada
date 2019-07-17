#include <iostream>
#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class  nodo
{
public:
	int idNodo;
	string nombre;
	int edad;

	 nodo(){}
	 nodo(int _id,string name,int _edad){
	 	idNodo=_id;
	 	nombre=name;
	 	edad=_edad;
	 }
};


/*void Conexion(int matriXAdj[][],int cant){
   
   srand (time(NULL));
   for(int i=0;i<cant;i++)
   	   for(int j=0;j<cant;j++)
       		matriXAdj[i][j]=rand()%2;
   
}*/
int main(int argc, char const *argv[])
{
	
	return 0;
}