#ifndef CO_H_INCLUDED
#define CO_H_INCLUDED
#include <iostream>
#include <string>
#include "Libreria.h"
using namespace std;

class CO
{
    
    private:
        int nCiudades;// ciudades A,B,C,D,E,F,G
        int nAnts,maxIt;//numero de hormigas y maxIt;
        ///int nAnts , b , maxIt,Q;
        double alpha,beta,ro,minTau;
        int ** ruta;
        int * best;
        double CBest;
        double** ciudades, ** graph,**feromonas,**deltaFeromonas,**deltaBFeromonas;
        bool *rutasValida;
   public:
        CO(int maxit,int nAntES,string Tabla);
        double distancia(int ciudadA, int ciudadB);
        double length(int ant); //Calcular el total de camino recorrido
        bool cPosicion(int ciudad, double x, double y); //Poner posicion a cada ciudad
        //bool conectarCiudades(int ciudadA, int ciudadB);
        bool valido(int ant, int siguienteCiudad);
        bool existeConeccion(int caminoA, int caminoB);
        bool inicializar();
        bool trazarRuta(int ant); //Traza rutas por cada hormiga
        bool actulizarFeromonas();
        void printDistancias();
        void printCamino(int ant);
        void printBest();
        void printFeromonas();

        void InitAnts();
        int  EleccionIndex(vector<float> Prob);
        double probabilidadSiguiente (int ciudadA, int ciudadB,int ant);
        void conectarCiudades(string Tabla_);
        float hallarCosto(int Ant);
        void UpdateFerormona(double *CostoRuta);
        void CaminoHamiltoniano(int i);

        void ejecutar();
        void printGraph();
        void PrintBest();
        void printCosto(double *C);
    
};
CO::CO(int maxit,int nAntES,string Tabla){
    nCiudades=10;
    maxIt=maxit;
    nAnts=nAntES;
    nCiudades=10;

    conectarCiudades(Tabla);
    ruta = new int*[nAnts];
    best = new int[nCiudades];
    rutasValida=new bool[nAnts];
    for (int i=0;i<nAnts;i++)
    {
        ruta[i] = new int[nCiudades];
        for (int j=0;j<nCiudades;j++)
            ruta[i][j]=-1;
    }
    feromonas=new double*[nCiudades];
    deltaFeromonas=new double*[nCiudades];
   for(int i=0;i<nCiudades;++i){
        feromonas[i]=new double[nCiudades];
        deltaFeromonas[i]=new double[nCiudades];
        for (int j=0;j<nCiudades;j++){
            feromonas[i][j]=0.001;
            deltaFeromonas[i][j]=0;
        }
    }
}
void CO::conectarCiudades(string Tabla_)
{
        float OT[nCiudades][nCiudades]={
                                        {0,8,99,5,99,99,99,99,99,99},// A
                                        {8,0,8,99,99,8,99,99,99,99,99},// B
                                        {99,8,0,8,99,9,2,99,99,99}, // C
                                        {5,99,8,0,99,5,99,9,99,99},//D
                                        {99,99,99,99,0,99,10,4,8,10},//e
                                        {99,8,9,5,99,0,2,8,1,99}, //F
                                        {99,99,2,99,10,2,0,10,9,99},//G
                                        {99,99,99,9,4,8,10,0,6,1},//H
                                        {99,99,99,99,8,1,9,6,0,99},//I
                                        {99,99,99,99,10,99,99,1,99,0}//j
                                       };
        float IN[nCiudades][nCiudades]={
                                        {0,4,99,7,99,99,99,99,99,99},// A
                                        {4,0,7,99,99,8,99,99,99,99,99},// B
                                        {99,7,0,4,99,6,4,99,99,99}, // C
                                        {7,99,4,0,99,4,99,5,99,99},//D
                                        {99,99,99,99,0,99,6,2,8,9},//e
                                        {99,8,6,4,99,0,9,1,1,99}, //F
                                        {99,99,4,99,6,9,0,9,10,99},//G
                                        {99,99,99,5,2,1,9,0,7,4},//H
                                        {99,99,99,99,8,1,10,7,0,99},//I
                                        {99,99,99,99,9,99,99,4,99,0}//j
                                       };
        float PV[nCiudades][nCiudades]={
                                        {0,1,99,4,99,99,99,99,99,99},// A
                                        {1,0,9,99,99,9,99,99,99,99,99},// B
                                        {99,9,0,4,99,3,3,99,99,99}, // C
                                        {4,99,4,0,99,3,99,5,99,99},//D
                                        {99,99,99,99,0,99,10,10,5,9},//e
                                        {99,9,3,3,99,0,9,1,9,99}, //F
                                        {99,99,3,99,10,6,0,8,10,99},//G
                                        {99,99,99,5,10,1,8,0,1,10},//H
                                        {99,99,99,99,5,9,10,1,0,99},//I
                                        {99,99,99,99,9,99,99,10,99,0}//j
                                       };
    graph=new double*[nCiudades];
    for (int i=0;i<nCiudades;i++){
        graph[i] = new double[nCiudades];
        for(int j=0;j<nCiudades;j++)
            graph[i][j]=-1;
    }
           
    if(Tabla_=="OT")
        cout<<"Debug OT "<<endl;
        for(int i=0;i<nCiudades;i++)
            for(int j=i+1;j<nCiudades;j++)
                if(OT[i][j]>0 and OT[i][j]<11){
                    graph[i][j]=OT[i][j];
                    graph[j][i]=OT[i][j];
                }

    else if(Tabla_=="IN")
        //cout<<"Debug IN "<<endl;
        for(int i=0;i<nCiudades;i++)
            for(int j=i+1;j<nCiudades;j++)
                if(IN[i][j]>0 and IN[i][j]<11){
                    graph[i][j]=IN[i][j];
                    graph[j][i]=IN[i][j];
                }
    else
        for(int i=0;i<nCiudades;i++)
            for(int j=i+1;j<nCiudades;j++)
                if(PV[i][j]>0 and PV[i][j]<11){
                    graph[i][j]=PV[i][j];
                    graph[j][i]=PV[i][j];
                }
       
    

}
void CO::printGraph(){
    char Nodos[10]={'A','B','C','D','E','F','G','H','I','J'};
    for(int i=0;i<nCiudades;i++){
        for (int j=i+1;j<nCiudades;j++){
            if(graph[i][j]!=-1)
                cout<<"("<<Nodos[i]<<","<<Nodos[j]<<")->"<<graph[i][j]<<endl;
        }
    }
}
double CO::probabilidadSiguiente (int ciudadA, int ciudadB,int ant){

  float sum=0;
  int t=ciudadA;
  for(int i=0;i<nCiudades;++i){
     if (graph[t][i]!=-1 and valido(ant,i))//conecction del nodo actual a i hay coneccion
        {   float visibilidad=1/graph[t][i];  
            sum=sum+visibilidad*feromonas[t][i];
        }
    }
  return ((1/graph[ciudadA][ciudadB])*feromonas[ciudadA][ciudadB])/sum;
}
int CO::EleccionIndex(vector<float> Prob){
    double mayor = 0.0;
    int mayorIt = -1;
    float rand=RandFloatBetween(0,1);
    float rango[Prob.size()];
    float sum=0;
    for(int i=0;i<Prob.size();++i)
    {
       sum=sum+Prob[i];
       rango[i]=sum;
    }
    for(int i=0;i<Prob.size();++i)
    {
       if (i==0)
       {
           if (rand<rango[i])
           {
               mayorIt=i;
           }
       }
       else{
             if (rand<rango[i] and rand>rango[i-1])
           {
               mayorIt=i;
           }

       }
    }

    /*for (int i=0;i<Prob.size();i++)
        if (Prob[i]>mayor) mayorIt = i;*/
    return mayorIt;
}
bool CO::valido(int ant,int NextNod){

    for(int i=0;i<nCiudades;++i){
        if(ruta[ant][i]==NextNod)
            return 0;
    }
    return 1;
}
void CO::CaminoHamiltoniano(int Ant_i)
{  
    int cont=1;
    int tNodActual=ruta[Ant_i][0];
    bool TMP=1;
    while(cont<10 and TMP==1){
        vector<int> index;
        vector<float> Prob;
        for (int i = 0; i <nCiudades; ++i)
        {
            if (graph[tNodActual][i]!=-1 and valido(Ant_i,i))//conecction del nodo actual a i hay coneccion
            {     
                Prob.push_back(probabilidadSiguiente(tNodActual,i,Ant_i));
                index.push_back(i);
              //  cout<<"index "<<i<<endl;
            }
        }
        if(Prob.size()!=0){
            int idx=EleccionIndex(Prob);
            //cout <<"->"<<idx<<endl;
            //cout<<" nextNodo :"<<index[idx];
            //cout<<endl;
            ruta[Ant_i][cont]=index[idx];
            tNodActual=ruta[Ant_i][cont];
        }
        else{
            TMP==0;
        }
        cont++;
    }
    if(ruta[Ant_i][9]==-1){
         rutasValida[Ant_i]=0;
     }
   else if(graph[ruta[Ant_i][0]][ruta[Ant_i][9]]==-1)
    {
        rutasValida[Ant_i]=0;
        //cout<<"ingreso "<<Ant_i<<endl;
    }
    else{
        rutasValida[Ant_i]=1;
    }


}
void CO::printCamino(int Ant){
    for(int i=0;i<nCiudades;i++){
        cout<<" "<<ruta[Ant][i]<<" - ";
    }
    cout<<endl;
}
float CO::hallarCosto(int Ant){
    float sum=0.0;
    for(int i=0;i<nCiudades-1;i++)
    {
     sum=sum+graph[ruta[Ant][i]][ruta[Ant][i+1]];
    }
    sum=sum+graph[ruta[Ant][nCiudades-1]][ruta[Ant][0]];
    return sum;
}
void CO::UpdateFerormona(double *CostoRuta){
    float Q=RandFloatBetween(0,1);//tasa de aprendizaje
    float P=RandFloatBetween(0,0.5);
    for(int i=0;i<nAnts;i++){
        if(rutasValida[i]==1){
            for(int j=0;j<nCiudades-1;j++){
                int ciudadA=ruta[i][j];
                int ciudadB=ruta[i][j+1];
                deltaFeromonas[i][j]+=Q/CostoRuta[i];
            }
        }
    }
    for(int i=0;i<nCiudades;i++){
        for(int j=0;j<nCiudades;j++){
            feromonas[i][j]=(1-P)*feromonas[i][j]+deltaFeromonas[i][j];
        }
    }
}
void CO::printCosto(double *C){
    for(int i=0 ; i<nAnts;++i){
        cout<<" hormiga "<<i<<"---> Costo "<<C[i]<<endl;
    }
}
void CO::InitAnts(){
    //cout<<endl<<"Colocar cada hormiga en una ciudad aleatoriamente"<<endl;
    for (int i = 0;i<nAnts;i++)
    {   int ran = RandFloatBetween(0,nCiudades-1);//randoms -> sorte(nCiudades);
        ruta[i][0] = ran;//vector[i];
       // cout<<endl<<"La ciudad escogida es "<<ran<<" ";//nAnts-1-i<<endl;

    }
}
void CO::PrintBest(){
    char Nodos[10]={'A','B','C','D','E','F','G','H','I','J'};
    
    for(int i=0;i<nCiudades-1;i++)
    {
      cout<<" "<<Nodos[best[i]]<<"->"<<Nodos[best[i+1]]<<"("<<graph[best[i]][best[i+1]]<<")"<<endl;
    }
    cout<<endl;

    cout<<"Costo:"<<CBest<<endl;
}
void CO::ejecutar(){

    printGraph();//OBSERVAR EL GRAPH CON EL QUE TRABAJAREMOS 
    //int vector[10]={1,7,3,2,4,0,8,5,6,9};
   // cout<<"estoy happy---------"<<endl;
    InitAnts();
    cout<<endl;
    int it=0;
    CBest=10000;
    while(it<maxIt){
        for (int i = 0; i < nAnts; ++i)
        {
            CaminoHamiltoniano(i);//Hallar el camino hamiltoniano para cada ormiga 
            /*if(rutasValida[i]==1){
                cout<<"hormiga "<<i<<endl;
                printCamino(i);
            }*/
        }
        //cout<<"debug Ini"<<endl;
        double CostoRuta[nAnts];
        for(int i=0 ; i< nAnts ; ++i){
            if(rutasValida[i]==1){
                CostoRuta[i]=hallarCosto(i);
                //cout<<"hello"<<endl;
                }
            else
                CostoRuta[i]=-1;
        }
       // printCosto(CostoRuta);
        // cout<<"debug fin"<<endl;
        for(int i=0 ; i<nAnts ; ++i){
            if(rutasValida[i]==1 and CostoRuta[i]<CBest ){
                CBest=CostoRuta[i];
                //cout<<" Best Costo -->"<<CBest<<endl;
                for(int j=0; j<nCiudades;j++){
                    best[j]=ruta[i][j];
                }
                PrintBest();
            }
        }
        cout<<endl;
       //cout<<"debug fin"<<endl;
        UpdateFerormona(CostoRuta);
        InitAnts();
        for (int i = 0; i < nAnts; ++i)
        {
            rutasValida[i]=0;
            for(int j=0;j<nCiudades;j++){
                ruta[i][j]=-1;
            }
        }
       it++;
    }

    PrintBest();


}
#endif // LIBRERIA_H_INCLUDED
