#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int dias=6;//se realizara para 6 dias L,M,M,J,V,S
const int C=5;
//*********************SIMULATING ANNEALING*************
float rand_FloatRange(float a, float b){
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}
float Balance[C]={30/100,25/100,20/100,15/100,10/100};
class PlatoC{

		public:
			float P[C];
			
			PlatoC(){
				P[0]=0;//Carbohidratos
				P[1]=0;//Frutas y verduras
				P[2]=0;//Carnes
				P[3]=0; //Grasas
				P[4]=0; //Dulces
				Init();
			}
			PlatoC(float a[]){
				for(int i=0;i<C;i++)
				{
					P[i]=a[i];
				}
			}
			void Init(){
				float total=5;//el total de platos 
			    float tmp;
				for(int i=1;i<4;++i){
					tmp=rand_FloatRange(0.01,total);
					while(tmp>2.3){
						tmp=rand_FloatRange(0.01,tmp);
					}
					P[i]=tmp;
					total=total-P[i];
				}
				P[4]=rand_FloatRange(0.01,0.9);
				total=total-P[4];
				P[0]=total;
				if(P[3]<P[4]){
					float t;
					t=P[3];
					P[3]=P[4];
					P[4]=t;}

			}
			void print(){
				//float sum=0;
				for(int i=0;i<C;i++){
					cout<<" "<<P[i];
				//	sum=sum+P[i];
				}
				cout<<endl;
				//cout<<"suma "<<sum<<endl;
			}
};
vector<PlatoC> PLatosSemanal(){
	vector<PlatoC> ListPlatos;
	ListPlatos.resize(dias);

	for(int i=0;i<dias;++i){
		ListPlatos[i]=PlatoC();
		///tmp->print();//para observar los platos 
	}
	return ListPlatos;
}
vector<PlatoC> initSol(){
	return PLatosSemanal();
}
PlatoC mutar(PlatoC a){
          
				PlatoC tmp(a.P);

				int index1,index2;
				index1=rand_FloatRange(0,2);
				index2=rand_FloatRange(3,4);
				while(index2==index1){
					index2=rand_FloatRange(0,4);
				}
				float t=tmp.P[index1];
				tmp.P[index1]=tmp.P[index2];
				tmp.P[index2]=t;
				return tmp;
			}
vector<PlatoC> NeighborSolution(vector<PlatoC> SolCurrent){
	vector<PlatoC> SolNeighbor;
	for(int i=0;i<SolCurrent.size();i++){
		SolNeighbor.push_back(mutar(SolCurrent[i]));
	}
  return SolNeighbor;
}
void printList(vector<PlatoC> listSol){
	for(int i=0;i<listSol.size();i++)
	{
		listSol[i].print();
	}
}
float CalculateTemperature(float T,float time){
	///return T-3;
	return T-1/log(1+time);
}
float distanceEucledian(float a[],float b[]){
	 float sum=0;
	 for(int i=0;i<C;i++){
	 	sum=sum+pow(b[i]-a[i],2);
	 }
	 return sum;
}
float Balanceado(vector<PlatoC> a){
	//cout<<"fitness "<<a.size()<<endl;
	 float sumatoria[C]={0,0,0,0,0};
   
	 for(int i=0;i<a.size();i++){
	 	 for(int j=0;j<C;j++){
	 	 	sumatoria[j]=sumatoria[j]+a[i].P[j];
	 	 }
	 }
	 float sum=0;
	 for(int i=0;i<C;i++){sum=sum+sumatoria[i];}
	 
	 float BalancePlato[C];
	 for(int i=0;i<C;++i){
	 	BalancePlato[i]=(sumatoria[i]*100)/sum;
	 }
	 float distance=distanceEucledian(Balance,BalancePlato);
	 return 1/sqrt(distance);
}
float repeticion(vector<PlatoC> a){
	float VPlate[dias]={10,10,10,10,10,10};
	int cantidad[dias]={1,1,1,1,1,1};
	 float distance;
	for(int i=0;i<dias;i++){
		for(int j=i;j<dias;j++){
           distance=distanceEucledian(a[i].P,a[j].P);
           if((distance*distance)<0.5 and (distance*distance)>0)
           {
           	cantidad[i]=cantidad[i]+1;
           	VPlate[i]=VPlate[i]-VPlate[i]/cantidad[i];
           }
		}
	}
	float sum;
	for(int i=0;i<dias;i++){
		sum=sum+VPlate[i];
	}
	return sum;


}
float fitness(vector<PlatoC> a){
   float tmp=Balanceado(a)*repeticion(a);
 return tmp;
}
float probability(vector<PlatoC> a,float suma,float T){
  return (fitness(a)/T)/suma;
}
vector<PlatoC> Simulating_Annealing(int nIter,float T){
		vector<PlatoC> SolCurrent=initSol();
		vector<PlatoC> SolBest=SolCurrent;
		vector<PlatoC> SolNeighbor;
		float Tcurrent=T;
		float t=0;
		int MaxI=1000;

		while(Tcurrent>0 and MaxI--){
			SolNeighbor=NeighborSolution(SolCurrent);
			Tcurrent=CalculateTemperature(Tcurrent,t);
		
			/*cout<<" Sol SolCurrent"<<endl;
			printList(SolCurrent);
			cout<<" Sol SolNeighbor"<<endl;
			printList(SolNeighbor);*/
			if(fitness(SolNeighbor)>=fitness(SolCurrent)){
				SolCurrent=SolNeighbor;
				if(fitness(SolCurrent)>=fitness(SolBest)){
					SolBest=SolCurrent;
				}
			}
			else{
				float Sum=fitness(SolNeighbor)/Tcurrent+fitness(SolCurrent)/Tcurrent;
				if(probability(SolNeighbor,Sum,Tcurrent)>probability(SolCurrent,Sum,Tcurrent))
                   SolCurrent=SolNeighbor;
                   if(fitness(SolCurrent)>fitness(SolBest)){
                   	SolBest=SolCurrent;
                   }
			}
			t=t+1;
		}

		
		return SolBest;
}
void showPorcentaje(vector<PlatoC> a){
	float sumatoria[C]={0,0,0,0,0};
   
	 for(int i=0;i<a.size();i++){
	 	 for(int j=0;j<C;j++){
	 	 	sumatoria[j]=sumatoria[j]+a[i].P[j];
	 	 }
	 }
	 float sum=0;
	 for(int i=0;i<C;i++){sum=sum+sumatoria[i];}
	 float BalancePlatoSemanal[C];
	cout<<endl;
	 for(int i=0;i<C;++i){
	 	BalancePlatoSemanal[i]=(sumatoria[i]*100)/sum;
	 	cout<<" I "<<BalancePlatoSemanal[i];
	 }
	 cout<<endl;

	 char Semanal[6]={'L','M','M','J','V','S'};
	 char Componente[5]={'C','P','C','G','D'};
	 for(int i=0;i<a.size();i++){
	 	cout<<" "<<Semanal[i] <<"  ";
	 	 for(int j=0;j<C;j++){
	 	 	float tmp=(a[i].P[j]*1000);
	 		 a[i].P[j]=tmp/1000;
	 	 	cout<<" "<<Componente[j]<<" :"<<a[i].P[j]*(BalancePlatoSemanal[j]/100);
	 	 }
	 	 cout<<endl;
	 }

}

int main()
{
	for(int i=0;i<5;i++){
		vector<PlatoC> Optimo;
		Optimo=Simulating_Annealing(10,100.0);
		cout<<" SEMANA "<<i+1<<endl;
		printList(Optimo);

		showPorcentaje(Optimo);
	}

	
	return 0;
}
