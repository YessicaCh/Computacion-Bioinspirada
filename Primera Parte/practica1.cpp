#include <iostream>
#include <string>
#include <utility> 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <vector>    /* time */

using namespace std;


class  Pasto{
public:
	 int IteracionP;
	 string idp;
	 std::pair<int,int> pos; 

	 Pasto(int posx,int posY,int time){
    	pos.first=posx;
    	pos.second=posY;
    	IteracionP=time;
    }
    void grow();
    void died();
    void updateTime();
	
};
void Pasto::updateTime(){

     IteracionP=IteracionP-1;
     if(IteracionP==0){

     	Pasto*tmp=new Pasto(pos.first,pos.second-1,IteracionP);
     	tmp->idp="p";
     }
}





//******************************************
class Conejo{
public:
     string idc;
	 std::pair<int,int> position;  
	 int InteracionC;

    Conejo(int posx,int posY){
    	position.first=posx;
    	position.second=posY;
    }
	void moverse(string dir,int n);
	void comer(string p);// aun no se come come 
};
void Conejo::moverse(string dir,int n){
	if(dir=="L" or dir=="l"){// hacia la izquierda
	   position.second=position.second+1;
	    if((position.second>=n)or(position.second>0) ){
         position.second=position.second%n;
	   }
	}else if ( dir =="R" or dir =="r"){// hacia la derecha
	   position.second=position.second-1; 
	    if((position.second>=n)or(position.second>0) ){
         position.second=position.second%n;
	   } 
	}else if ( dir =="T" or dir =="t"){// hacia arriba
	     position.first=position.first-1;
	    if((position.first>=n)or(position.first>0) ){
         position.first=position.first%n;
	   }
	}else if ( dir =="D" or dir =="d"){// hacia abajo
	   position.first=position.first+1;
	    if((position.first>=n)or(position.first>0) ){
         position.first=position.first%n;
	   }
	}
}


class Zorro{

public:
     string idz;
	 std::pair<int,int> position;  
	 int InteracionC;

    Zorro(int posx,int posY){
    	position.first=posx;
    	position.second=posY;
    }
	void moverse(string dir,int n);
	void comer(string p);// aun no se come come 
};
void Zorro::moverse(string dir,int n){
	if(dir=="L" or dir=="l"){// hacia la izquierda
	   position.second=position.second+1;
	   if((position.second>=n)or(position.second>0) ){
         position.second=position.second%n;
	   }
	}else if ( dir =="R" or dir =="r"){// hacia la derecha
	   position.second=position.second-1; 
	   if((position.second>=n)or(position.second>0) ){
         position.second=position.second%n;
	   } 
	}else if ( dir =="T" or dir =="t"){// hacia arriba
	   position.first=position.first-1;
	    if((position.first>=n)or(position.first>0) ){
         position.first=position.first%n;
	   }
	}else if ( dir =="D" or dir =="d"){// hacia abajo
	   position.first=position.first+1;
	    if((position.first>=n)or(position.first>0) ){
         position.first=position.first%n;
	   }
	}
}


class mundoGrilla
{
	
    private:
    vector< vector<string> > Grill;
    vector<Pasto*> P;
    vector<Conejo*> C;
    vector<Zorro*> Z;

    int size;

    public:
    mundoGrilla(int n_);
    void comportamientoAleatorio();
    void movConejoAleatorio();
    void movZorroAleatorio();
    void diedPasto(int x,int y);
    void diedConejo(int x,int y);
    void printWorld();

};
mundoGrilla::mundoGrilla(int n_){
	
    this->size=n_;
    Grill.resize(size);

     for(int i=0;i<size;i++)
     {
     	Grill[i].resize(size);
     }


     for(int i=0;i<size;i++)
     {
     	for(int j=0;j<size;j++)
     	{
     		Grill[i][j]="* ";
     		
     	}
     }
     Pasto *pas=new Pasto(size/2,size/2,size/2);
      pas->idp="p";
     Grill[size/2][size/2]="p";
      P.push_back(pas);

     Zorro *zor=new Zorro(size-1,size-1);
     zor->idz="z";
     Grill[size-1][size-1]="z";
     Z.push_back(zor);

     Conejo *conj=new Conejo(size-1,0);
     conj->idc="c";
     Grill[size-1][0]="c";
     C.push_back(conj);

}
void mundoGrilla::printWorld(){

	 for(int i=0;i<size;i++)
	 {
	 	for(int j=0;j<size;j++)
	 		{
	 		  cout<<"   "<<Grill[i][j]<<"   ";
	 		}
	 	cout<<"      "<<endl;
	 }

}
void mundoGrilla::diedPasto(int x,int y)
{
   for(int i=0;i<P.size();i++)
   {
     if(P[i]->pos.first==x and P[i]->pos.second==y)
     {
     	Grill[x][y]="*";
     	P.erase (P.begin()+i);
     }
   }
}
void mundoGrilla::diedConejo(int x,int y)
{
   for(int i=0;i<C.size();i++)
   {
     if(C[i]->position.first==x and C[i]->position.second==y)
     {
     	Grill[x][y]="*";
     	C.erase(C.begin()+i);
     }
   }
}
void mundoGrilla::movConejoAleatorio()
{
	cout<<endl;
	cout<<"   mov Conejo   ";
    srand(time(NULL));
    vector<string> direction={"l","r","t","d"};
    int index=rand()%C.size();
    int indexDir=rand()%direction.size();

    Grill[C[index]->position.first][C[index]->position.second]="*";
    C[index]->moverse(direction[indexDir],size);
    cout<<" "<<C[index]->idc<<"  "<<direction[indexDir]<<endl;
    if(Grill[C[index]->position.first][C[index]->position.second]=="p")
      {
        diedPasto(C[index]->position.first,C[index]->position.second);
      }
    Grill[C[index]->position.first][C[index]->position.second]=C[index]->idc;  
    cout<<endl;
    printWorld();
}
void mundoGrilla::movZorroAleatorio()
{
	cout<<endl;
	cout<<"   mov Zorro   ";
    srand(time(0));
    vector<string> direction={"l","r","t","d"};
    int index=rand()%Z.size();
    int indexDir=rand()%direction.size();

    Grill[Z[index]->position.first][Z[index]->position.second]="*";
    Z[index]->moverse(direction[indexDir],size);
    cout<<" "<<Z[index]->idz<<"  "<<direction[indexDir]<<endl;
     if(Grill[C[index]->position.first][C[index]->position.second]=="c")
      {
        diedPasto(Z[index]->position.first,Z[index]->position.second);
      }
    Grill[Z[index]->position.first][Z[index]->position.second]=Z[index]->idz;
    //controlar el tiempo;
    cout<<endl;
    printWorld();
}
void mundoGrilla::comportamientoAleatorio()
{
    printWorld();
    for(int i=0;i<3;i++){

        movConejoAleatorio();
        movZorroAleatorio();
    }
}


int main()
{
	cout<<"***********Practica1*********"<<endl;
	int nMundo;
	cout<<"Ingrese la grilla de n :"<<endl;
	cin>>nMundo;
	mundoGrilla  world(nMundo);
	world.comportamientoAleatorio();
	
	
	return 0;
}