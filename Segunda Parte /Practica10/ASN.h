#include <iostream>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <bitset> 
#include <stdlib.h>     /* abs */
#include "Utility.h"
using namespace std;

class AlgSelecNegativa{

	public:

	   AlgSelecNegativa(int N,int M);
	   bool DistColor(color x,vector<color>xr,int s);
       bool selfString(color x);
       void FuncGeneraDetectores();
       void generarRandomString();
       void ProtectedStrings();
       bool Hamming(color x ,color y,int nEmparejamiento);
       bool R_bits(color x ,color y,int nEmparejamiento);
       void AplicacionDetectores(int nEmparejamiento);
	   /*GeneracionDetectores();
	   AplicacionDetectores();*/
	public:
		int n;				//generacion de n colores (n>=100;)
		int m; 
		int nRand;             //generaccion de M Detectores
		vector<color> randColor;
		vector<color> ProtectedStr;
		vector<color> DetectorR;

};
AlgSelecNegativa::AlgSelecNegativa(int N,int M){
	n=110;
	m=M;
	nRand=N;
	randColor.resize(n);
	DetectorR.resize(m);
	ProtectedStr.resize(nRand);
	generarRandomString();
}
bool AlgSelecNegativa::DistColor(color x,vector<color>xr,int s){
   for(int i=0;i<s+1;i++){
       if(xr[i].r ==x.r and xr[i].g==x.g and xr[i].b==x.b){
       	  return 0;
       	  break;
       }
   }   
   return 1;
}
void AlgSelecNegativa::generarRandomString(){
	for(int i=0;i<n;i++){
		color tmp=GeneratorColor();
		while(DistColor(tmp,randColor,i)==0)
			tmp=GeneratorColor();
		randColor[i]=tmp;
	}
}    
bool AlgSelecNegativa::selfString(color x){
    bitset<8> N128(128);
    bitset<8> N85(85);
	if(x.r.to_ulong()>x.g.to_ulong()){
		if(x.b.to_ulong()>=N128.to_ulong()){
			int tmp=x.r.to_ulong()-x.g.to_ulong();
			if(abs(tmp)<N85.to_ulong() and (x.r.to_ulong()*x.r.to_ulong()+x.g.to_ulong())/2<=N85.to_ulong())
			    return 1;
			else 
				return 0;
		    }
	    else
	    	return 0;}
	else{
			if(x.b.to_ulong()>=N128.to_ulong()){
				int tmp=x.r.to_ulong()-x.g.to_ulong();
				if(abs(tmp)<N85.to_ulong() and (x.r.to_ulong()+x.g.to_ulong())/2<=N128.to_ulong())
				    return 1;
				else
					return 0;
			     }
		    else
		    	return 0;
	   }
}
void AlgSelecNegativa::FuncGeneraDetectores(){
    int cont=0;
	for(int i=0;i<n;i++){
		if(selfString(randColor[i])==0 and cont<m){
			DetectorR[cont]=randColor[i];
			cont++;
		}
	}
	cout<<"aqui tengo n Detectores :"<<cont<<endl;
	while(cont<m){
	  	color x=GeneratorColor();
	  	if(selfString(x)==0 and DistColor(x,randColor,cont)==0 ){
	  		DetectorR[cont]=x;
	  		randColor[cont]=x;
			cont++;
			n++;
		}
	  }	
}
void AlgSelecNegativa::ProtectedStrings(){
	for(int i=0;i<nRand;i++){
		/*color tmp=GeneratorColor();
        while(DistColor(tmp,ProtectedStr,i)==0)
			tmp=GeneratorColor();*/
		ProtectedStr[i]=GeneratorColor();
	}

}
bool AlgSelecNegativa::Hamming(color x ,color y,int nEmparejamiento){
     int cont=0;
	 //R
	 for(int i=0;i<8;i++){
	     if(x.r[i]==y.r[i]){
	         cont++;
	     }
	 }
	 //G
	 for(int i=0;i<8;i++){
	     if(x.g[i]==y.g[i]){
	         cont++;
	     }
	 }
	 //b
	 for(int i=0;i<8;i++){
	     if(x.b[i]==y.b[i]){
	         cont++;
	     }
	 }
	 if (cont>=nEmparejamiento)
	 	return 1;
	 else
	 	return 0;
}
bool AlgSelecNegativa::R_bits(color x ,color y,int nEmparejamiento){
     int cont=0;
     bool band=1;
	 //R
	 for(int i=0;i<8 ;i++){
	     if(x.r[i]==y.r[i])
	         cont++;
	     else
	     	cont=0;
	 }
	 //G
	 for(int i=0;i<8;i++){
	     if(x.g[i]==y.g[i])
	         cont++;
	     else
	     	cont=0;
	     if (cont>=nEmparejamiento)
	     	return 1;
	 }
	 //b
	 for(int i=0;i<8;i++){
	     if(x.b[i]==y.b[i])
	         cont++;
	      else
	     	cont=0;
	     if (cont>=nEmparejamiento)
	     	return 1;
	 }
	 return 0;
	
}
void AlgSelecNegativa::AplicacionDetectores(int nEmparejamiento){
	int contPredic=0;
	bool flag=0;
	int contPredicExit=0;
	ProtectedStrings();
	for(int i=0;i<nRand;++i){
		flag=0;
		ProtectedStr[i].printColor();
		cout<<"-->";
		for(int j=0;j<m and flag==0;j++){
			if(R_bits(DetectorR[j],ProtectedStr[i],nEmparejamiento)==1){
				cout<<" SN:T ";
				contPredic+=1;
				if(selfString(ProtectedStr[i])==1){
					contPredicExit+=1;
					cout<<" SF:T ";
				}
				else
					cout<<" SF:F ";

				flag=1;
			}
		}
		if(flag==0)
			cout<<" SN:F ";
		cout<<endl;

	}
	cout<<" Prediccion "<<contPredic<<endl;
	cout<<" Prediccion Exitosa "<<contPredicExit<<endl;
	float porc=(contPredicExit*100.0)/contPredic;
	cout<<" Porcentaje de Prediccion  "<<porc<<" % "<<endl;
	cout<<endl;
}