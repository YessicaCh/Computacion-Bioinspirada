#include <iostream>
#include <time.h>
#include <stdio.h>
#include <bitset>         // std::bitset
using namespace std;
//El   color esta formado por 
class color
{
	public:
		bitset<8> r;
		bitset<8> g;
		bitset<8> b;
   
	color(int R,int G, int B){
		r=R;
		g=G;
		b=B;
	}
	color(){
		r=0;
		g=0;
		b=0;
	}
	void printColor()
	{
		cout<<"( "<<r.to_ulong()<<","<<g.to_ulong()<<","<<b.to_ulong()<<") ";
	}
};
float RandFloatBetween(float a, float b){
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}
color GeneratorColor(){
	int tr,tg,tb;
		tr=RandFloatBetween(0,254);
		tg=RandFloatBetween(0,254);
		while(tr==tg){
			tg=RandFloatBetween(0,254);
		}
		tb=RandFloatBetween(0,254);
		while(tb==tg)
		{
			tb=RandFloatBetween(0,254);
		}
	    color tmpcolor(tr,tg,tb);
	 return tmpcolor;
}