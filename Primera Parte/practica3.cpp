#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <vector>
#include <math.h>
#include <bitset>  
float pi=3.14159265358979323846264338327950288419716939937510;       // std::bitset
//#include <time>
using namespace std;

/*float probabilidad(int i,int j){
	float total=0;
	for(int j=0;i<total:j++)
	{
       total=total+exp(f(j)/Temperatura)  //(i)=e()
	}

	return exp(f(j)/Temperatura)/total;}*/
float random(float value){

	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10));
    if(r2>value){
    	r2=r2-value/2.0;
        while(r2>4){
        	r2=static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10));
        }
    }
    return r2;
}
void printPair(pair<float,float> paire){

	 cout<<endl;
	 cout<<"		"<<paire.first<<" : "<<paire.second<<endl;
	 cout<<endl;
}
float f(pair<float,float> x){
   
   float tmp=sin(pi*sqrt(pow(x.first,2.0)+pow(x.second,2.0)))/(pi*sqrt(pow(x.first,2.0)+pow(x.second,2.0)));
   return tmp*tmp;
}
float T(int t)
{
	return 2/log(1+t);
}

pair<float,float> InitialSolution(){
     pair<float,float> InitialP;
     InitialP.first=random(4.0);
     InitialP.second=random(4.0); 
	return InitialP;
}
pair<float,float> NeighborSolution(pair<float,float> current){//aqui hay que hacer mutacion
     //srand(time(0));
    float tmpfir=random(3.0);
    float tmpsecond=random(3.0);
     current.first=random(3.0);
     current.second=random(3.0);
     if(current.first>tmpfir)
        current.first=tmpfir;
    if(current.first>tmpsecond)
        current.first=tmpsecond;

	return current;

}
pair<float,float> asig(pair<float,float> current){//aqui hay que hacer mutacion
     pair<float,float> asig;
     asig.first=current.first;
     asig.second=current.second;
	return asig;

}
float CalculaTemperature(int i,float Tactual){
	 return Tactual-T(i);
}
float evaluate(pair<float,float> Sol){
	return f(Sol);
}
float fProbabi(pair<float,float> i,float temperature){
	  return exp(f(i)/temperature);
}

float probability(pair<float,float> Scurrent,pair<float,float> Sneighbor,float temperature,int index){
	 float summation=fProbabi(Scurrent,temperature)+fProbabi(Sneighbor,temperature);
     float elegir;
	 if(index==0){
	 	elegir=fProbabi(Scurrent,temperature)/summation;
	 	return elegir;
	 }
	 else{
	 	elegir=fProbabi(Sneighbor,temperature)/summation;
	 	return elegir;}

}
pair<float,float> SimulatedAnnealing(int nIter,float temperature)
{
	int t=1;//tiempo inicial 
	pair<float,float> Scurrent=InitialSolution();
    pair<float,float> Sbest=Scurrent;
    pair<float,float> Sneighbor;
    float Tcurrent=temperature;

    cout<<"	InitialSolution :";
    printPair(Scurrent);

    cout<<"	InitialTemperature :"<<endl;
    cout<<"			"<<Tcurrent<<endl;cout<<endl;
    cout<<"********************************"<<endl;

    while(Tcurrent>0){

    	Sneighbor=NeighborSolution(Scurrent);
    	Tcurrent=CalculaTemperature(t,Tcurrent);

    	cout<<"	SolCurrent:";
    	printPair(Scurrent);
    	cout<<"	SolNeighbord :";
    	printPair(Sneighbor);
    	cout<<"	temperature :   ---->"<<Tcurrent<<endl;
    	cout<<endl;



    	if(evaluate(Sneighbor)>=evaluate(Scurrent)){
	    		Scurrent=Sneighbor;
	    		if(evaluate(Scurrent)>=evaluate(Sbest)){
	    		 Sbest=Scurrent;
	    		}
    	    }
    	else {
    		  cout<<endl;
    		  cout<<"Probability neighbord:"<<probability(Scurrent,Sneighbor,Tcurrent,1)<<endl;
    		  cout<<"Probability current:"<<probability(Scurrent,Sneighbor,Tcurrent,0)<<endl;
    		  cout<<endl;

    		  if(probability(Scurrent,Sneighbor,Tcurrent,1)>probability(Scurrent,Sneighbor,Tcurrent,0))
    		     {  Scurrent=Sneighbor;
    		  		if(evaluate(Scurrent)>=evaluate(Sbest)){
    					Sbest=Scurrent;}
    			}
    		 
    		}
    	t+=1;
    }
    cout <<"    numero de iteraciones  "<<t<<endl;
    return Sbest;

}

int main()
{
	int iter=10;
	float temperature=40;
	pair<float,float> sol;
	cout<<"************Simulated Annealing ************"<<endl;
	sol=SimulatedAnnealing(iter,temperature);
	cout<<" LA MEJOR SOLUCION :"<<endl;
	cout<<"		"<<sol.first <<" :" <<sol.second<<endl;
	return 0;
}