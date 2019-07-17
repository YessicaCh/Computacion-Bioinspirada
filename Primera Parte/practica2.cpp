#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <vector>
#include <math.h>
#include <bitset>         // std::bitset
//#include <time>
using namespace std;

vector<float> probabilidad;
vector<pair<float,int>> aptitud;

//**********************************TOOLS*****************************
float funcionObjetivo(float x);
float rand_FloatRange(float a, float b){return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}
int  indexInepto(vector<pair<float,float>> Po){
	int inepto=0;
    for(int i=1;i<probabilidad.size();i++)
    {	
       if(probabilidad[i]<=probabilidad[inepto]){
    		 inepto=i;}
    }
    //myvector.erase (myvector.begin()+5);
    return inepto;
}
void imprimirVector(vector<pair<float,float> > Poblacion){
	cout<<endl;
	for(int i=0;i<Poblacion.size();i++)
	{
		cout<<"		"<<Poblacion[i].first << "   "<< Poblacion[i].second <<endl;
	}
}
void hallandoProbabilidad(vector<pair<float,float>> Po){
	float sumaTotal=0.0;
	probabilidad.resize(Po.size());
	for(int i=0;i<Po.size();i++)
	{
      sumaTotal=sumaTotal+funcionObjetivo(Po[i].first);
	}
	//cout<<"suma Total: ....."<<sumaTotal<<endl;
	//hallando la probalidad para cada valor;
	cout<<endl;
	for(int i=0;i<Po.size();i++)
	{
        probabilidad[i]=funcionObjetivo(Po[i].first)/sumaTotal;
        //cout<<Po[i].first << "   "<< Po[i].second <<"   ->>probabilidad: "<<probabilidad[i]<<endl;
       // cout<<"-->  "<<funcionObjetivo(Po[i].first)/sumaTotal<<endl;
	}
}
/*void bubblesort(vector<pair<float,int>> apt){
	for (int i = 0;i < apt.size();i++) {
		for (int j = 0;j<apt.size()-1-i;j++)
		{
			if (apt[j].first > apt[j + 1].first)
			   {swap(Po[j], Po[j + 1]);}
		}
	}
}*/

//*************ALGORITMO GENETICO*********************


//0) EL CROMOSOMA ESTA FORMADO POR PARES ORDENADOS :   "PAIR<FLOAT,FLOAT>"



//1)FUNCION A EVALUAR
float funcionObjetivo(float x){
	float pi=3.1415;
	return (sin(pi*x)/(pi*x))*(sin(pi*x)/(pi*x));
}



//2)GENERADOR DE POBLACION INICIAL
vector<pair<float,float>> generacionIndividuos(int n){

	vector<pair<float,float> > Poblacion;
    Poblacion.resize(n);
    srand (static_cast <unsigned> (time(0)));
    float aux;
	for(int i=0;i<n;i++){
		aux=rand_FloatRange(-4.0,4.0);//static_cast <float> (rand()%5) / (static_cast <float> (4));
		while(aux==0)
		{
			//aux=static_cast <float> (rand()%5) / (static_cast <float> (4));
			aux=rand_FloatRange(-4.0,4.0);
		}
		Poblacion[i].first=aux;
		Poblacion[i].second=funcionObjetivo(Poblacion[i].first);//aqui hay que remplazar en la funcion 
	}
	return Poblacion;
}



//3)FUNCION FITNESS 
void evaluacion(vector<pair<float,float>> Po){
	aptitud.resize(Po.size());					//la evaluacion o fitnes es la evaluacion de x en el la funcion si y alcanza a 	1 seria la mayor aptitud 
	for(int i=0;i<Po.size();i++)
	{
		aptitud[i].first=funcionObjetivo(Po[i].first);
		aptitud[i].second=i;
	}
}



//4)FUNCION DE SELECCION
vector<pair<float,float>> seleccion(vector<pair<float,float>> Po){

    hallandoProbabilidad(Po);
     
    vector<pair<float,float>> PadresAptos;

    int indexApto1=0,indexApto2=0;
    for(int i=1;i<probabilidad.size();i++)
    {	
       if(probabilidad[i]>=probabilidad[indexApto1]){
    		 indexApto1=i;}
    }
   
    for(int i=1;i<probabilidad.size();i++)
    {	
       if(probabilidad[i]>=probabilidad[indexApto2] and probabilidad[i]!=probabilidad[indexApto1] ){
    		 indexApto2=i;
    		}
    }
    
    PadresAptos.push_back(Po[indexApto1]);
    PadresAptos.push_back(Po[indexApto2]);
    //retorno a los dos padres mas aptos para el cruzamiento
    return  PadresAptos;

}


//5)OPERADOR DE CRUZAMIENTO
pair<float,float> OperadorCruzamiento(pair<float,float> PadreA,pair<float,float> PadreB){
	// el promedio entre los dos los padres mas aptos
    pair<float,float> newGeneration;
	newGeneration.first=(PadreA.first + PadreB.first)/2;
   	newGeneration.second=(PadreA.second + PadreB.second)/2;
	return newGeneration;

}




//6)OPERADOR DE MUTACION
void mutacion(vector<pair<float,float>> Po){
                                 //actualizo la probabilidad y escoge los dos mas aptos para la mutacion 
	hallandoProbabilidad(Po);
 
    int indexApto1=0,indexApto2=0;
    for(int i=1;i<probabilidad.size();i++)
    {	
       if(probabilidad[i]>=probabilidad[indexApto1]){
    		 indexApto1=i;}
    }
   +
    for(int i=1;i<probabilidad.size();i++)
    {	
       if(probabilidad[i]>=probabilidad[indexApto2] and probabilidad[i]!=probabilidad[indexApto1] ){
    		 indexApto2=i;
    		}
    }
        

        std::bitset<16> tmpx(Po[indexApto1].first*10000);
        std::bitset<16> tmpy(Po[indexApto1].second*10000);

        std::bitset<16> tmp1x(Po[indexApto2].first*10000);
        std::bitset<16> tmp1y(Po[indexApto2].second*10000);

        pair<bitset<16>,bitset<16>>PadreABin,PadreBBin;
        PadreABin.first=tmpx;
		PadreABin.second=tmpy;

		PadreBBin.first=tmp1x;
		PadreBBin.second=tmp1y;

       srand(time(0));
       int aux=rand()%8;
       srand (static_cast <unsigned> (time(0)));
       for(int i=rand()%2;i<aux;i++)
       {
            float probabilidadChambio=static_cast <float> (rand()%5) / (static_cast <float> (4));
			while(probabilidadChambio==0)
			{
				probabilidadChambio=static_cast <float> (rand()%5) / (static_cast <float> (4));
			}
          	//cout<<" probabilidad "<<probabilidadChambio<<endl;
	        if(probabilidadChambio>0.5){
	          	  PadreABin.first[i]=0;
	          	  PadreBBin.first[i+1]=0;}
	        else{
	          	  PadreABin.first[i]=1;
	          	  PadreBBin.first[i+1]=1;}       	  
       }
     
		Po[indexApto1].first=(PadreABin.first.to_ulong()/10000.0); 
		Po[indexApto1].second=funcionObjetivo(Po[indexApto1].first);//PadreABin.second.to_ulong()/10000.0; 

        Po[indexApto2].first=PadreBBin.first.to_ulong()/10000.0; 
		Po[indexApto2].second=funcionObjetivo(Po[indexApto2].first);//PadreBBin.second.to_ulong()/10000.0; 

        cout<<"Padres Mutados"<<endl;

        cout<<" 	"<<Po[indexApto1].first <<" "<<Po[indexApto1].second<<endl;
        cout<<" 	"<<Po[indexApto2].first <<" "<<Po[indexApto2].second<<endl;

}

int main()
{
	cout<<"*********** ALGORITMOS GENETICOS ********"<<endl;
	vector<pair<float,float> > Poblacion,PadresAptos;
     
    cout<<"Ingrese numero de individuos : "<<endl;					//Cantidad de poblacion inicial
	int n;
	cin>>n;
	Poblacion=generacionIndividuos(n);  							//En la variable Poblacion se guarda la poblacion individual
		    cout<<"		_________Poblacion inicial________________"<<endl<<endl;
		imprimirVector(Poblacion);
	while(n*2>0){
		cout<<endl;cout<<endl;cout<<endl;
       evaluacion(Poblacion);

		PadresAptos=seleccion(Poblacion);cout<<endl;                //Se escoge dos individuos de la poblacion para hacer cruzamiento y se elimina al menos apto
        	cout<<"		_________Padres mas Aptos_________________"<<endl<<endl;
    		imprimirVector(PadresAptos);
    	int inepto=indexInepto(Poblacion);							//Se escoge al individuo con menor aptitud
    	Poblacion[inepto]=OperadorCruzamiento(PadresAptos[0],PadresAptos[1]);// Se realiz cruzamiento y se guarda a la nueva generacion y se elimina al menos apto
        	cout<<endl;
        	cout<<"  _________Mutacion______________________"<<endl<<endl;
    	mutacion(Poblacion);										//operacion de mutacion 
    		cout<<"  	_________Nueva Poblacion__________________"<<endl<<endl;
    			imprimirVector(Poblacion);
         n=n-1;
	}
	return 0;
}

