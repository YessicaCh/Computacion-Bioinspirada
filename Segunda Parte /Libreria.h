#ifndef LIBRERIA_H_INCLUDED
#define LIBRERIA_H_INCLUDED
#include <iostream>
#include <math.h>
using namespace std;

//****************Rand*******************
float RandFloatBetween(float a, float b){
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

#endif // LIBRERIA_H_INCLUDED
