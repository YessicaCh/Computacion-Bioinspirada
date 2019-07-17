#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>    ///solo se usa para el recorrido en amplitud
#include <vector>
#include <stack>
#include <string>
#define pi acos(-1)

using namespace std;



typedef pair<int,int> position;
//typedef pair<double, squad> estate;

int largo=25;
int iteT=6;
int nNodos;
float Precio=200;
vector<string> listaNombre;
int  listEdad[10]={70,56,20,16,26,30,21,26,21,23};
float listSueldos[10]={1000,1400,1000,0,1200,1100,756,0,756,0};



class  nodo
{
public:
	int idNodo;
	string nombre;
	int edad;
	float sueldo;

	 nodo(){}
	 nodo(int _id,string name,int _edad){
	 	idNodo=_id;
	 	nombre=name;
	 	edad=_edad;
	 }
};
class  person
{
public:
	string nombre;
	int edad;
	float sueldo;
	float infl;

	 person(){}
	 person(string name,int _edad,float sueldo){
	 	nombre=name;
	 	edad=_edad;
	 }
};
float tiempo;
float edad(int i ,vector<nodo*> Grafo)
{    float resul=0,t=0;
    if(Grafo[i]->edad>=20 and Grafo[i]->edad<=40)
	{
		t=rand()%100+30;
		t=t/100;
        return t*(0.5);

	}
	else{
		t=rand()%30;
		t=t/100;
         return t*(0.5);

	}
}



float RPrecio(int i ,vector<nodo*> Grafo)
{    float resul=0,t=0;
    if(Precio<Grafo[i]->sueldo)
	{
		t=rand()%70;
		t=t/100;
        return t*(0.3);

	}
	else{
		t=rand()%30;
		t=t/100;
         return t*(0.3);

	}
}
float Rtiempo(int timeT)
{   if(timeT==1 ){
	         tiempo=100;
	     }
	tiempo=tiempo-0.075;

	return ((tiempo/100)*(0.2));
	//tiempo=tiempo-0.075;
}
float regla(int tmp,int i,vector<nodo*> Grafo,int timeT){
	float resul=0;
	//cout<<"i  ......"<<Grafo[i]->edad<<endl;
	float t;
	resul=resul+edad(i,Grafo);
	//cout<<"Regla de la edad "<<resul<<endl;
	resul=resul+RPrecio(i,Grafo);
	//cout<<"Regla del Precio"<<resul<<endl;
	resul=resul+Rtiempo(timeT);
	//cout<<"Regla del Precio"<<resul<<endl;
	return resul;
}
void ReglaGen(vector<vector<person*>> matrix,int i, int j,int timeT){
	  float resul=0,t=0;

	 //Por la edad 
	  cout<<" i "<<i <<"  j "<<j<<endl;
	  if (i>=0 and i<=(nNodos-1) and j<=(nNodos-1) and j>=0){
	  	    cout<<"entra aqui"<<endl;
		    if(matrix[i][j]->edad>=20 and matrix[i][j]->edad<=40){
				t=rand()%100+30;t=t/100;
		        resul=resul+t*(0.5);}
			else{
				  t=rand()%30;t=t/100;
		         resul=resul+t*(0.5);
		     }
		     //Por el precio 
		     if(Precio<1000){
				t=rand()%50; t=t/100;
		        resul=resul+t*(0.25);}
			else{
				t=rand()%10;t=t/100;
		        resul=resul+t*(0.25);
		        }
		    if(timeT==1 ){
			         tiempo=100;
			     }
			tiempo=tiempo-0.075;

			resul=resul+((tiempo/100)*(0.5));
			cout<<resul<<endl;
			matrix[i][j]->infl=resul;

     }
    
     

}
void AutomataCelular(){
	int timeT=0;
	vector<nodo*> Grafo;
	float SimulacionInfluencia[nNodos][nNodos];
    int matriXAdj[nNodos][nNodos];
	int PersonBuyCelphone=2;//rand()%nNodos-2;
	stack<int> recorrido;
	//recorrido.push_back(PersonBuyCelphone);
	if(PersonBuyCelphone<0){
		PersonBuyCelphone=0;
	}

	for(int i=0;i<nNodos;++i){
		nodo *tmp=new nodo(i,listaNombre[i],listEdad[i]);
		Grafo.push_back(tmp);
	}
	
    for(int i=0;i<nNodos;i++){
   	    for(int j=i;j<nNodos;j++){
   	    	if(i!=j)
   	    		matriXAdj[i][j]=rand()%2;
       		else
       			matriXAdj[i][j]=0;
       		cout<<matriXAdj[i][j];
   	    }
   	    cout<<endl;
   	}
    
    SimulacionInfluencia[nNodos][nNodos]=1;

   	for(int i=0;i<nNodos;i++)
   		for(int j=0;j<nNodos;j++)
   			{
   				 SimulacionInfluencia[i][j]=0;

   			}
   	//cout<<"aqui en While"<<endl;
   	while(timeT<iteT){
   		recorrido.push(PersonBuyCelphone);
   		 while (!recorrido.empty()) {
   		 		//cout<<"aqui en While 2"<<endl;
	   		 	int temp=recorrido.top();
	            recorrido.pop();
	            for(int i=0;i<nNodos;i++){
	            	if(matriXAdj[temp][i]==1){
	                    if(matriXAdj[i][temp]!=1)
	                        recorrido.push(i);
	                    //cout<<"hello "<<endl;
	            		SimulacionInfluencia[temp][i]=regla(temp,i,Grafo,timeT);
	            		//cout<<"regla-->("<<temp<<","<<i<<")"<<regla(temp,i,Grafo,timeT)<<endl;
	            	   }
	            }

   	     }
   	     timeT++;
        }

    cout<<" PersonBuyCelphone  "<<PersonBuyCelphone<<endl;
    cout<<"imprimiendo el SimulacionInfluencia"<<endl;
    SimulacionInfluencia[PersonBuyCelphone][PersonBuyCelphone]=1;
    cout<<"          ";
    for(int i=0;i<nNodos;i++)
    {
    	cout<<listaNombre[i]<<"     ";
    }
    cout<<endl;
    for(int i=0;i<nNodos;i++){
    	cout<<listaNombre[i]<<"        ";
   	    for(int j=0;j<nNodos;j++){
       		cout<<SimulacionInfluencia[i][j]<<"          ";
   	    }
   	    cout<<endl;
   	}


}
void AutomataCelularMatrix(){
	vector<vector<person*>> matrix;
	matrix.resize(nNodos);
	bool matrizVisitados[nNodos][nNodos];
	for(int i=0;i<matrix.size();i++){
		matrix[i].resize(nNodos);
	}
	int PBuyCelphone=rand()%nNodos;
	for(int i=0;i<nNodos;i++)
		for(int j=0;j<nNodos;j++){
			person *t=new person(listaNombre[i],listEdad[i],listSueldos[i]);
			matrix[i][j]=t;
			matrizVisitados[i][j]=0;
		}

   // cout<<"posicion "<<PBuyCelphone<<endl;
    stack<position> listaTemporal;
    //posit=make_pair(PBuyCelphone,PBuyCelphone);
    matrizVisitados[PBuyCelphone][PBuyCelphone]=1;
    listaTemporal.push(make_pair(PBuyCelphone,PBuyCelphone));
    int iteT=1;
    while(!listaTemporal.empty()) {
	   		 	position temp=listaTemporal.top();
	            listaTemporal.pop();
	            //cout<<"aqui ocurrio"<<endl;
	            if(temp.first<0){
	            	temp.first=0;
	            	break;
	            }

	            else if(temp.first>(nNodos-1)){
	            	  temp.first=nNodos-1;
	            	  break;
	            	}
	            else if(temp.second<0){
	            	temp.second=0;
	            	break;
	            }
	            else if(temp.second>(nNodos-1)){
	            	  temp.second=nNodos-1;
	            	  break;
	            	}
	            ReglaGen(matrix,temp.first,temp.second,iteT);
	            matrizVisitados[temp.first][temp.second]=1;
	            listaTemporal.push(make_pair(temp.first-1,temp.second));
	            listaTemporal.push(make_pair(temp.first+1,temp.second));
	            listaTemporal.push(make_pair(temp.first,temp.second+1));
	            listaTemporal.push(make_pair(temp.first,temp.second-1));
	            iteT++;
	        }

    for (int i = 0; i < nNodos; ++i)
    {   cout<<listaNombre[i]<< "  ";
    	for (int j = 0; j < nNodos; ++j)

		    {
		    	 cout<<matrix[i][j]->infl<<"       "; 
		    }
		   cout<<endl;
    }

}

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/ );
	glEnable(GL_DEPTH_TEST);
	AutomataCelular();
}
int main(int argc, char **argv){
	srand (time(NULL));
	cout<<"Ingrese la cantidad de Nodos que tendra"<<endl;
	cin>>nNodos;
	listaNombre.push_back("papa   ");
	listaNombre.push_back("mama   ");
	listaNombre.push_back("OliHerm");
	listaNombre.push_back("EmeHerm");
	listaNombre.push_back("RuthHer");
	listaNombre.push_back("Luzherm");
	listaNombre.push_back("Jhoel  ");
	listaNombre.push_back("Maria  ");
	listaNombre.push_back("Luzbeli");
	listaNombre.push_back("Anabel ");
	AutomataCelular();


	/*glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" Trabajo Final");
	glutDisplayFunc(myDisplay);
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-0.1,largo,-0.1,largo,-0.1,largo);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();*/
	return 0;
}
