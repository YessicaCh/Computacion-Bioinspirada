#include <iostream>
#include <string>
#include <utility> 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <vector>    /* time */
#include "CO.h"

using namespace std;

int main()
{
	cout<<"----------------------------------------"<<endl;
    cout<<"-----------Practica 8 --------------"<<endl;
    cout<<"----------------------------------------"<<endl;
    CO Hamilton(20,8,"PV");
    Hamilton.ejecutar();
	
	//cout<<"Rand "<<RandFloatBetween(1,3)<<endl;
	
	return 0;
}