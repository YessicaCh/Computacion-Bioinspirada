#ifndef REDESINMUNES_H_INCLUDED
#define REDESINMUNES_H_INCLUDED
#include "Randoms.h"
/*float rand_num(int a,int b)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(a,b);
    return dis(gen);
}*/

int rand2(int a, int b)
{
    srand(time(0));
    return a+(rand()%(b-a+1));
}

struct redes
{
    int x,y;
    double valorAfinidadRed,valorAfinidadPatron; //valor de afinidad con una red y un patron
    redes *afinidadR;//afinidad con una red
    int * afinidadP;//afinidad con un patron
    redes(int i,int j)
    {
        x = i;
        y = j;
        valorAfinidadPatron = valorAfinidadRed = 0.0;
        afinidadP = 0;
        afinidadR = 0;
    }
    void print()
    {
        cout<<"("<<x<<","<<y<<")"<<endl;
        if (afinidadP!=0)
            cout<<"Afinidad Patron: "<<valorAfinidadPatron<<" Patron: ("<<afinidadP[0]<<","<<afinidadP[1]<<")"<<endl;
        if (afinidadR!=0)
        {
            cout<<"Afinidad Red: "<<valorAfinidadRed<<" Red: ";
            cout<<"("<<afinidadR->x<<","<<afinidadR->y<<")"<<endl;
        }
    }
};
//Funcion que calcula si un anticuerpo es menor a otro tomando en cuenta su afinidad con respecto
//a los patrones
bool mayorRedesPatron (redes i,redes j)
{
    return (i.valorAfinidadPatron>j.valorAfinidadPatron);
}
bool mayorRedesRed (redes i,redes j)
{
    return (i.valorAfinidadRed>j.valorAfinidadRed);
}
class redesInmunes
{
    public:
    vector<int*> patrones;//Conjunto de patrones a ser reconocido
    vector<redes> anticuerpos;
    double umbralRedes;//Umbral para la afinidad entre anticuerpos
    double umbralClones;//umbral para la afinidad entre anticuerpos y entradas
    int nClones;//numero de clones a generar
    int nClonesAfines;//numero de clones que deben ser afines
    redesInmunes(vector<int*>conjunto,double uRedes, double uClones,
                 int numeroClones, int nClonesA);
    int rand3(int a, int b);
    double afinidad(redes r1, int *patron);
    double afinidadRedes(redes r1,redes r2);
    bool crearAnticuerpo(vector<redes> &anticuerpo,int numero);
    bool calcularAfinidadPatrones(vector<redes>&anticuer,int *patron);
    bool calcularAfinidadRedes(vector<redes>&anticuer);
    bool inicio();
    bool generarClones(vector<redes> &clones);
    bool mutacion(vector<redes> &clones);
    void Print();
    Randoms *randoms;
};

redesInmunes::redesInmunes(vector<int*>conjunto,double uRedes, double uClones,
                 int numeroClones, int nClonesA)
{
    patrones = conjunto;
    umbralRedes = uRedes;
    umbralClones = uClones;
    nClones = numeroClones;
    nClonesAfines = nClonesA;
    randoms = new Randoms (21);
}

int redesInmunes::rand3(int a, int b)
{
    int ran = randoms -> sorte(b);
    if (ran<0)
        ran = ran*(-1);
    if (ran>a)
        ran = b-ran;
    return ran;
}

double redesInmunes::afinidad(redes r1, int* patron)
{
    if (r1.x == patron[0] && r1.y==patron[1]) return 1.0;
    return 1/(sqrt(pow(r1.x-patron[0],2)+pow(r1.y-patron[1],2)));
}

bool redesInmunes::crearAnticuerpo(vector<redes> &anticuerpo,int nClones)
{
    for (int i=0;i<nClones;i++)
    {
        int x = randoms -> sorte(10);//(0,10);
        int y = randoms -> sorte(10);//rand3(0,10);
        //cout <<x<<" "<<y<<endl;
        redes a(x,y);
        anticuerpo.push_back(a);
    }
    return 1;
}


bool redesInmunes::calcularAfinidadPatrones(vector<redes>&anticuer,int *patron)
{
    for (int i=0;i<(int)anticuer.size();i++)
    {
        double afin = afinidad(anticuer[i],patron);
        if (anticuer[i].valorAfinidadPatron<afin)
        {
            anticuer[i].valorAfinidadPatron = afin;
            anticuer[i].afinidadP = patron;
        }
    }
    return 1;
}

double redesInmunes::afinidadRedes(redes r1,redes r2)
{
    if (r1.x==r2.x && r1.y==r2.y) return 1.0;
    return 1/(sqrt(pow(r1.x-r2.x,2)+pow(r1.y-r2.y,2)));
}

bool redesInmunes::calcularAfinidadRedes(vector<redes>&anticuer)
{
    for (int i=0;i<(int)anticuer.size()-1;i++)
    {
        for (int j=i+1;j<(int)anticuer.size();j++)
        {
            double afin = afinidadRedes(anticuer[i],anticuer[j]);
            if (anticuer[i].valorAfinidadRed<afin)
            {
                anticuer[i].valorAfinidadRed = afin;
                anticuer[i].afinidadR = &anticuer[j];
            }
            if (anticuer[j].valorAfinidadRed<afin)
            {
                anticuer[j].valorAfinidadRed = afin;
                anticuer[j].afinidadR = &anticuer[i];
            }
        }
    }
    return 1;
}
bool redesInmunes::generarClones(vector<redes> &clones)
{
    //Copiar los anticuarpos para ordenarlos
    vector<redes> mayorAfinidad = anticuerpos;
    sort(mayorAfinidad.begin(),mayorAfinidad.end(),mayorRedesPatron);
    //Escoger la cantidad de anticuerpos que son los mas afines
    int nAnticuerposAfinidad = mayorAfinidad.size()/3;
    for (int i=0;i<nAnticuerposAfinidad;i++)
    {
        //calcular la cantidad de clones proporcional afinidad*10
        int cantidadClones = ceil(mayorAfinidad[i].valorAfinidadPatron * 10);
        //cout<<"Cantidadde que se clonara "<<cantidadClones<<endl;
        for (int j=0;j<cantidadClones;j++) clones.push_back(mayorAfinidad[i]);
    }
    return 1;
}

//La mutacion es sumar a x y restar a y la diferencia entre x y y
bool redesInmunes::mutacion(vector<redes> &clones)
{
    for (int i = 0;i<(int)clones.size();i++)
    {
        int ran = randoms -> sorte(10);
        int ran2 = randoms ->sorte(10);
        //cout<<endl<<ran<<" "<<ran2<<endl;
        //if (ran<0) ran = ran*(-1);
        //if (ran>0) ran = 10-ran;
        clones[i].x +=ran;//+= rand3(0,5)/2;
        clones[i].y +=ran2;//-= rand3(0,5)/2;
        clones[i].valorAfinidadPatron = 0;
    }
    return 1;
}
bool redesInmunes::inicio()
{
    crearAnticuerpo(anticuerpos,nClones);
    cout<<"Primeros anticuerpos"<<endl;
    for (int j=0;j<(int)anticuerpos.size();j++)
    {
        anticuerpos[j].print();
    }
    int criterio = 1;
    while (criterio>0)
    {
        for (int i=0; i<(int)patrones.size();i++)
        {
            cout<<"Trabajando con "<<patrones[i][0]<<","<<patrones[i][1]<<endl;
            //Calculando la afinidad de cada anticuerpo con un patron
            cout<<"Calcular afinidad patrones "<<calcularAfinidadPatrones(anticuerpos,patrones[i])<<endl;
            /*cout<<"Primeros anticuerpos con afinidad"<<endl<<"size anticuerpos "<<anticuerpos.size()<<endl;
            for (int j=0;j<(int)anticuerpos.size();j++)
            {
                anticuerpos[j].print();
            }*/
            vector<redes> clones;
            cout<<"Generando clones "<<generarClones(clones)<<endl;
            /*cout<<"Clones"<<endl<<"size clones "<<clones.size()<<endl;
            for (int j=0;j<(int)clones.size();j++)
            {
                clones[j].print();
            }*/
            cout<<"Mutando "<<mutacion(clones)<<endl;
            calcularAfinidadPatrones(clones,patrones[i]);
            /*cout<<"Mutacion"<<endl<<"size clones "<<clones.size()<<endl;
            for (int j=0;j<(int)clones.size();j++)
            {
                clones[j].print();
            }*/
            cout<<"Umbral con patrones"<<endl;
            for (int j=0;j<(int)clones.size();j++)
            {
                if (clones[j].valorAfinidadPatron>umbralClones)
                {
                    anticuerpos.push_back(clones[j]);
                }
            }
            /*cout<<"Filtro del umbral"<<endl<<"size anticuerpos "<<anticuerpos.size()<<endl;
            for (int j=0;j<(int)anticuerpos.size();j++)
            {
                anticuerpos[j].print();
            }*/
        }
        cout<<"Se calculo afinidad con las demas redes: "<<calcularAfinidadRedes(anticuerpos)<<endl;
        vector<redes> aux;
        for (int k=0;k<(int)anticuerpos.size();k++)
        {
            if(anticuerpos[k].valorAfinidadRed>umbralRedes)
            {
                aux.push_back(anticuerpos[k]);
            }
        }
        anticuerpos.clear();
        anticuerpos = aux;
        /*cout<<"Filtro del umbral red"<<endl<<"size anticuerpos "<<anticuerpos.size()<<endl;
        for (int j=0;j<(int)anticuerpos.size();j++)
        {
            anticuerpos[j].print();
        }*/
        int nuevosAnticuerpos = rand3(1,5);
        //cout <<"Cantidad de nuevos anticuerpos "<<nuevosAnticuerpos<<endl;
        cout<<"Nuevos anticuerpos agregados "<<crearAnticuerpo(anticuerpos,nuevosAnticuerpos);
        /*cout<<"Nuevas redes"<<endl<<"size anticuerpos "<<anticuerpos.size()<<endl;
        for (int j=0;j<(int)anticuerpos.size();j++)
        {
            anticuerpos[j].print();
        }*/
        criterio--;
    }
    for(int i=0;i<(int)patrones.size();i++) calcularAfinidadPatrones(anticuerpos,patrones[i]);
    //cout<<"Calculo de afinidad final"<<endl;
    //cout<<"Final"<<endl<<"size anticuerpos "<<anticuerpos.size()<<endl;
    /*for (int j=0;j<(int)anticuerpos.size();j++)
    {
            anticuerpos[j].print();
    }*/
    return 1;
}

void redesInmunes::Print()
{
    cout<<endl<<"--------------Resultado-----------------"<<endl;
    cout<<"Cantidad de anticuerpos: "<<anticuerpos.size()<<endl;
    for (int i=0;i<(int)patrones.size();i++)
    {
        cout<<"Patron ("<<patrones[i][0]<<" , "<<patrones[i][1]<<")"<<endl<<"Redes afines:"<<endl;
        for (int j=0;j<(int)anticuerpos.size();j++)
        {
            if(anticuerpos[j].afinidadP == patrones[i])
                anticuerpos[j].print();
        }
    }
}


#endif // REDESINMUNES_H_INCLUDED
