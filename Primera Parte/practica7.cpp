#include <iostream>
#include <random>
#include <ctime>
using namespace std;
const int estados=6,acciones=6;

float R[estados][acciones]={{-1,-1,-1,-1,0,-1},   //posibles caminos 
			 			 {-1,-1,-1,0,-1,100},
			             {-1,-1,-1,0,-1,-1,},
			             {-1,0,0,-1,0,-1},
			             {0,-1,-1,0,-1,100},
			             {-1,0,-1,-1,0,100}};
float Q[estados][acciones];

int random(int b){
  random_device machine; // aqui esta la maquina y se invoca como machine() y te retorna un numero aleatorio
  mt19937 Rand(machine()+time(0)); 
  return Rand()%b+0;

}
void ReglaTransicionQlearning(float  r)
{//Q(estado, accion) = R(estado, accion) + Γ × max(Q(siguienteestado, todaslasacciones);
  for (int state = 0; state < estados; ++state)
  {
  	for (int action = 0; action < acciones; ++action)
  	{
  		Q[state][action]=R[state][action]+r;//* aquii falta 
  	}
  }
}
void printQ(){
	cout<<endl;
	for (int state = 0; state < estados; ++state){
		cout<<"		";
	  	for (int action = 0; action < acciones; ++action)
	  	{
	  		cout<<Q[state][action]<<" ";
	  	}
	  	cout<<endl;
    }
    cout<<endl;

}

void printR(){
	cout<<endl;
	for (int state = 0; state < estados; ++state){
		cout<<"		";
	  	for (int action = 0; action < acciones; ++action)
	  	{
	  		cout<<" "<< R[state][action]<<" ";
	  	}
	  	cout<<endl;
    }
    cout<<endl;

}
void initQZero(){
	for(int i=0;i<estados;++i)
    		for(int j=0;j<acciones;j++)
    			Q[i][j]= -2;
}

int main()
{   float r;
	cout<<" | 										|"<<endl;
	cout<<" |*************Q-Learning ************** |"<<endl;
    cout<<" | 										|"<<endl;

    cout<<endl;
    cout<<"Ingrese Γ  donde 0<Γ<1 :"<<endl;
    cin>>r;

    float stateObject=5;
    int episode=100;
    int actionPos;//accion posible;
    int stateNext;
    int stateCurrent;
    int stateIni;
    float maxValue;//el primero la accion  la segunda el valor maximo;
    int cont;
  

    //int stateIni=random(estados);
     initQZero();
    for(int i=0;i<episode;++i){

    	stateIni=random(estados);
    	cout<<"|----State initial  "<<stateIni<<endl;
    	stateCurrent=stateIni;
    	cont=0;
    	while(stateCurrent!=stateObject){
    		    
    		    //stateNext=actionPos;
    		    maxValue=R[stateCurrent][0];
	    		for(int i=1;i<acciones;++i){
	    			if(R[stateCurrent][i]>maxValue){
	    				maxValue=R[stateCurrent][i];
	    				actionPos=i;
	    				
	    			}
	    		}
	    		stateNext=actionPos;
	    		cout<<" --> "<<stateNext<<endl;
	    		Q[stateCurrent][actionPos]=R[stateCurrent][actionPos]+r*maxValue;
	    		stateCurrent=stateNext;  
	    		cont+=1;  		
    	}//end while 
        if(stateIni==stateObject){
	    	maxValue=R[stateCurrent][0];
		    for(int i=1;i<acciones;++i){
		    	if(R[stateCurrent][i]>maxValue){
		    		maxValue=R[stateCurrent][i];
		    		actionPos=i;
		    		}
		      }		
		    Q[stateCurrent][actionPos]=R[stateCurrent][actionPos]+r*maxValue;
		    stateCurrent=stateNext; 
		    cont+=1;
		 }
		cout<<" CONT  "<<cont<<endl;
        cout<<" 	MATRIZ R "<<endl;
    	printR();
    	cout<<" 	MATRIZ Q "<<endl;
    	printQ();
    }  //end for 
	return 0;
}