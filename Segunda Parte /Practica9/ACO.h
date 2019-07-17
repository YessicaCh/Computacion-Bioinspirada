#ifndef ACO_H_INCLUDED
#define ACO_H_INCLUDED
#include "Randoms.h"
class ACO
{
    public:
    ACO(int maxit, double alpha, double beta, double ro, int nAnts, int nCiudades, int b, double taumin, int q);
    double distancia(int ciudadA, int ciudadB);
    double length(int ant); //Calcular el total de camino recorrido
    bool cPosicion(int ciudad, double x, double y); //Poner posicion a cada ciudad
    bool conectarCiudades(int ciudadA, int ciudadB);
    bool valido(int ant, int siguienteCiudad);
    bool existeConeccion(int caminoA, int caminoB);
    bool inicializar();
    bool trazarRuta(int ant); //Traza rutas por cada hormiga
    bool actulizarFeromonas();
    void printDistancias();
    void printCamino(int ant);
    void printBest();
    void printFeromonas();
    double probabilidadSiguiente (int ant, int ciudadA, int ciudadB);
    int maxVector(double* vec,int tam);
    int minVector(double* vec,int tam);
    int nCiudades, nAnts , b , maxIt,Q;
    double alpha,beta,ro,minTau;
    int ** ruta;
    int * best;
    double lBest;
    double** ciudades, ** graph,**feromonas,**deltaFeromonas,**deltaBFeromonas;
    Randoms *randoms;

};

ACO::ACO(int mi, double al, double be, double r, int nA, int nC, int elitismo, double tm, int q)
{
    nCiudades = nC;
    nAnts = nA;
    b = elitismo;
    maxIt = mi;
    alpha = al;
    beta = be;
    ro = r;
    Q = q;
    minTau = tm; //minimo de feromonas

    ciudades = new double*[nCiudades];
    graph = new double*[nCiudades];
    feromonas = new double*[nCiudades];
    deltaBFeromonas = new double*[nCiudades];
    deltaFeromonas = new double*[nCiudades];
    best = new int[nCiudades];
    for (int i=0;i<nCiudades;i++)
    {
        ciudades[i] = new double[2];
        for (int j=0;j<2;j++)
            ciudades[i][j]=0.0;
        graph[i] = new double[nCiudades];
        feromonas[i] = new double[nCiudades];
        deltaBFeromonas[i] = new double[nCiudades];
        deltaFeromonas[i] = new double[nCiudades];
        for (int j=0;j<nCiudades;j++)
        {
            graph[i][j]=-1;
            feromonas[i][j] = -1;
            deltaBFeromonas[i][j] = 0;
            deltaFeromonas[i][j] = 0;
        }
    }
    ruta = new int*[nAnts];
    for (int i=0;i<nAnts;i++)
    {
        ruta[i] = new int[nCiudades];
        for (int j=0;j<nCiudades;j++)
            ruta[i][j]=-1;
    }
    randoms = new Randoms (21);
}

double ACO::distancia(int ciudadA, int ciudadB)
{
	double x = pow(ciudades[ciudadB][0] - ciudades[ciudadA][0],2.0);
	double y = pow (ciudades[ciudadB][1] - ciudades[ciudadA][1],2.0);
	double dis =  sqrt (x + y );
	//cout<<"Esta es la idistancia"<<dis<<endl;
	return dis;
}

double ACO::length(int ant)
{
    double len = 0.0;
    for (int i=0;i<nCiudades-1;i++)
        len += graph[ruta[ant][i]][ruta[ant][i+1]];
    len += graph[ruta[ant][nCiudades-1]][ruta[ant][0]];
    return len;
}

bool ACO::cPosicion(int ciudad, double x, double y)
{
    ciudades[ciudad][0] = x;
    ciudades[ciudad][1] = y;
    return 1;
}

bool ACO::conectarCiudades(int ciudadA, int ciudadB)
{
    graph[ciudadA][ciudadB] = graph[ciudadB][ciudadA] = distancia(ciudadA,ciudadB);
    return 1;
}

bool ACO::valido(int ant, int siguienteCiudad)
{
    for (int i = 0;i<nCiudades;i++)
        if (ruta[ant][i] == siguienteCiudad)
        {
            //cout<<endl<<"Error, la hormiga "<<ant<<" ya paso por "<<siguienteCiudad<<endl;
            return 0;
        }
    return 1;
}

bool ACO::existeConeccion(int ciudadA,int ciudadB)
{
    if (graph[ciudadA][ciudadB] == -1)
    {
        //cout<<endl<<"Error, no existe camino entre "<<ciudadA<<" y "<<ciudadB<<endl;
        return 0;
    }
    return 1;
}

double ACO::probabilidadSiguiente(int cityi, int cityj, int antk)
{
	double etaij = (double) pow (1 / graph[cityi][cityj], beta);
	double tauij = (double) pow (feromonas[cityi][cityj],   alpha);

	double sum = 0.0;
	for (int c=0; c<nCiudades; c++) {
		if (existeConeccion(cityi, c)) {
			if (valido(antk, c)) {
				double eta = (double) pow (1 / graph[cityi][cityj], beta);
				double tau = (double) pow (feromonas[cityi][cityj],   alpha);
				sum += eta * tau;
			}
		}
	}
	return (etaij * tauij) / sum;
}

bool ACO::trazarRuta(int ant)
{
    //cout<<endl<<"La hormiga "<<ant<<endl;
    for (int i = 0;i<nCiudades-1;i++)
    {
        double *prob;
        prob = new double[nCiudades];
        //cout<<endl<<"Quiere ir de "<<ruta[ant][i];
        for (int j = 0;j<nCiudades;j++)
        {
            //cout<<" a "<<j<<endl;
            if (existeConeccion(ruta[ant][i],j) && valido(ant,j))
            {
                //cout<<endl<<"Si entra" <<endl;
                prob[j] = probabilidadSiguiente(ruta[ant][i],j,ant);
            }

            else
            {
                prob[j] = 0.0;
            }

        }
        ruta[ant][i+1] = maxVector(prob,nCiudades);
    }
    return 1;
}
//Hallar el mayor de un vector
int ACO::maxVector(double* vec,int tam)
{
    double mayor = 0.0;
    int mayorIt = -1;
    for (int i=0;i<tam;i++)
        if (vec[i]>mayor) mayorIt = i;
    return mayorIt;
}

int ACO::minVector(double* vec,int tam)
{
    double menor = 100000000;
    int menorIt = -1;
    for (int i=0;i<tam;i++)
        if (vec[i]< menor) menorIt = i;
    return menorIt;
}

//Actulizar fermonas
bool ACO::actulizarFeromonas()
{
    //para deltaFeromona
    for (int k=0; k<nAnts; k++)
    {
        double rlength = length(k);
        int ciudadA,ciudadB;
		for (int r=0; r<nCiudades-1; r++)
        {
			ciudadA = ruta[k][r];
			ciudadB = ruta[k][r+1];
			deltaFeromonas[ciudadA][ciudadB] += Q / rlength;
			deltaFeromonas[ciudadB][ciudadA] += Q / rlength;

			deltaBFeromonas[best[r]][best[r+1]] += Q / lBest;
			deltaBFeromonas[best[r]][best[r+1]] += Q / lBest;
		}
        ciudadA = ruta[k][nCiudades-1];
        ciudadB = ruta[k][0];
        deltaFeromonas[ciudadA][ciudadB] += Q / rlength;
        deltaFeromonas[ciudadB][ciudadA] += Q / rlength;
        deltaBFeromonas[nCiudades-1][0] += Q / lBest;
        deltaBFeromonas[0][nCiudades-1] += Q / lBest;
	}

	for (int i=0; i<nCiudades; i++)
    {
		for (int j=0; j<nCiudades; j++)
        {
			feromonas[i][j] = (1 - ro) * feromonas[i][j] + deltaFeromonas[i][j] + b*deltaBFeromonas[i][j];
			deltaFeromonas[i][j] = 0.0;
			deltaBFeromonas[i][j] = 0.0;
		}
    }
	return 1;
}

void ACO::printDistancias()
{
    for (int i=0;i<nCiudades;i++)
    {
        cout<<endl;
        for (int j=0;j<nCiudades;j++)
            cout<<graph[i][j]<<" ";
    }
}

void ACO::printCamino(int ant)
{
    cout <<endl<<"El recorrido de "<<ant<<" es ";
    for (int i = 0;i<nCiudades;i++)
        cout<<ruta[ant][i]<<" ";
    cout<<endl;
}

void ACO::printBest()
{
    cout<<"El mejor camino es"<<endl;
    for (int i=0;i<nCiudades;i++)
        cout<<best[i]<<" ";
    cout<<endl;
}

void ACO::printFeromonas () {
	cout << " Feromonas: " << endl;
	cout << "  | ";
	for (int i=0; i<nCiudades; i++) {
		printf("%5d   ", i);
	}
	cout << endl << "- | ";
	for (int i=0; i<nCiudades; i++) {
		cout << "--------";
	}
	cout << endl;
	for (int i=0; i<nCiudades; i++) {
		cout << i << " | ";
		for (int j=0; j<nCiudades; j++) {
			if (i == j) {
				printf ("%5s   ", "x");
				continue;
			}
			if (existeConeccion(i, j)) {
				printf ("%7.3f ", feromonas[i][j]);
			}
			else {
				if(feromonas[i][j] == 0.0) {
					printf ("%5.0f   ", feromonas[i][j]);
				}
				else {
					printf ("%7.3f ", feromonas[i][j]);
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool ACO::inicializar()
{
    lBest = 100000;//INT_MAX;
    //Conectar grafo
    cout<<endl<<"Conectando los nodos de los grafos"<<endl;
    //////////////////////////
    for (int i = 0;i<nCiudades-1;i++)
    {
        for (int j = i+1;j<nCiudades;j++)
            conectarCiudades(i,j);
    }
    printDistancias();
    //////////////////////////
    //Colocar cada hormiga en una ciudad aleatoriamente
    cout<<endl;
    cout<<endl<<"Colocar cada hormiga en una ciudad aleatoriamente"<<endl;
    for (int i = 0;i<nAnts;i++)
    {
//        srand (time(NULL));
//        int ciudad = rand() % nCiudades;
        int ran = randoms -> sorte(nCiudades);
        if (ran<0)
            ran = ran*(-1);
        ruta[i][0] = ran;
        cout<<endl<<"La ciudad escogida es "<<ran<<" ";//nAnts-1-i<<endl;
    }
    cout<<endl;

    int iterador = 0;

    while (iterador < maxIt)
    {
        cout<<endl<<"Hacer que las hormigas recorran todos los nodos, iteracion "<<iterador<<endl;
        //Hacer que las hormigas recorran todos los nodos
        for (int i=0;i<nAnts;i++)
        {
            trazarRuta(i);
        }
        cout<<endl<<"Evaluar lenghts de cada hormiga, iteracion "<<iterador<<endl;
        //Evaluar lenghts de cada hormiga
        double * lenghts;
        lenghts = new double [nAnts];
        for (int i=0;i<nAnts;i++)
        {
            lenghts[i]=length(i);
            //printCamino(i);
            //cout<<endl<< "Con length = "<< lenghts[i];
        }

        int hormiga = minVector(lenghts,nAnts);
        double newLenght = length(hormiga);
        if (newLenght<lBest)
        {
            //cout<<" Im her"<<hormiga<<endl;
            for (int k = 0;k<nCiudades;k++)
                best[k] = ruta[hormiga][k];
            lBest = newLenght;
            //printBest();
        }
        cout<<endl<<"Actualizar feromonas, iteracion "<<iterador<<endl;
        //Actualizar feromonas
        actulizarFeromonas();
        printFeromonas();
        //Inicializar las rutas
		for (int i=0; i<nAnts; i++)
		{
            int ran = randoms -> sorte(nCiudades);
            if (ran<0)
                ran = ran*(-1);
            ruta[i][0] = ran;
            //ruta[i][0] = nAnts-1-i;
			for (int j=1; j<nCiudades; j++) {
				ruta[i][j] = -1;
			}
		}
		cout<<endl<<"Nuevos inicios"<<endl;
		for (int i=0; i<nAnts; i++)
		{
            cout<<ruta[i][0]<<" ";
		}
		cout<<endl;
        iterador ++;

    }
    printBest();
    return 1;
}

#endif // ACO_H_INCLUDED
