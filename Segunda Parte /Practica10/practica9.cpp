#include <iostream>

using namespace std;
#include "ASN.h"
int main()
{
	cout<<"**********************************************************"<<endl;
	cout<<"**************            PRACTICA 9           ***********"<<endl;
	cout<<"************  Algoritmo de seleccion Negativa   **********"<<endl;
	cout<<"**********************************************************"<<endl;

	//color  rosado(2,3,5);
	AlgSelecNegativa  SN(50,10);
	SN.FuncGeneraDetectores();
	
	/*cout <<"detectados..............."<<endl;
	for(int i=0;i<13;i++)
	{
		SN.DetectorR[i].printColor();
	}
	cout <<"Proyeccion..............."<<endl;*/
	SN.AplicacionDetectores(17);
	//GeneratorColor().printColor(); 



	return 0;
}