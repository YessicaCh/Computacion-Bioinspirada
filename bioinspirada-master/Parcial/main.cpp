#include <iostream>
#include <map>
#include <vector>
#include <bits/stdc++.h>
#include <time.h>
#include <random>
#include "Funciones.h"
using namespace std;
map<double,string> books;
vector <double> lista_valores;

bool llenar_bd()
{
    /*Base de datos de libros*/
    books[1.0005] = "Harry Potter y la orden del fenix";
    books[1.0006] = "Harry Potter y el misterio del principe";
    books[1.0101] = "Festival de la blasfemia";
    books[2.0001] = "Les doy una buena noticia 2013";
    books[2.0002] = "Les doy una buena noticia 2014";
    books[2.0003] = "Les doy una buena noticia 2015";
    books[2.0004] = "Les doy una buena noticia 2016";
    books[2.0005] = "Les doy una buena noticia 2017";
    books[4.0001] = "Diccionario";
    books[2.0101] = "Para confirmar la fe y la vida. Curso de confirmacion";
    books[2.0201] = "Dinamicas para jovenes, personajes y valores";
    books[2.0301] = "Papel y lapiz para dinamicas para grupos";
    books[2.0401] = "El secreto de la liturgia";
    books[2.0501] = "Manual de los sacramentos";
    books[2.0601] = "Orar sin desfallecer";
    books[2.0702] = "YOUCAT";
    books[2.0701] = "Catecismo de la Iglesia Catolica";
    books[3.0001] = "Yo, Juan Bautista de la Salle";
    books[3.0101] = "De la Salle";
    books[2.0801] = "Cancionero";
    books[2.0901] = "Biblia de Jerusalen";
    books[2.0902] = "Santa Biblia";
    books[4.0101] = "El perro. Su adiestramiento y entrenamiento";
    books[2.0903] = "ABC de la Biblia";
    books[2.1001] = "Queridos catequistas";
    books[1.0201] = "Comentarios reales de los Incas";
    books[1.0202] = "Poesias completas";
    books[1.0203] = "Jorge, el hijo del pueblo";
    books[1.0204] = "Peregrinaciones en una paria";
    books[1.0205] = "Antologia poetica";
    books[1.0206] = "Arequipa y los viajeros";
    books[1.0207] = "Repertorio poetico arequipeño";
    books[1.0208] = "Meditaciones arequipeñas";
    books[1.0209] = "Tradiciones y leyendas arequipeñas";
    books[1.0210] = "Cuentos arequipeños";

    for (map<double,string>::iterator it=books.begin(); it!=books.end(); ++it)
        lista_valores.push_back(it->first);
    return 1;
}

bool generar_aleatorio (vector <double> &sol1)//, vector<double> &sol2)
{
    int cantidad = (int)lista_valores.size();
    vector <bool> aux;
    for (int i=0;i<cantidad;i++)
        aux.push_back(0);

    for (int i = 0;i < cantidad; i++)
    {
        srand(time(NULL));
        int ind1 = rand() % cantidad;
        if (aux[ind1] != 0)
        {
            while (aux[ind1] != 0)
            {
                srand(time(NULL));
                ind1 = rand() % cantidad;
            }
        }
        aux[ind1] = 1;
        sol1.push_back(lista_valores[ind1]);
        /*srand(time(NULL));
        double ind2 = rand() % 20;
        if (ind2 < 10 ) ind2 = 0;
        else ind2 = 1;
        cout<<" el boleano es " <<ind2<<endl;
        aux[ind1] == 1;
        if (ind2 == 0) sol1.push_back(lista_valores[ind1]);
        else sol2.push_back(lista_valores[ind1]);*/
    }
    return 1;
}

inline bool consecutivos(int a, int b)
{
    return (a+1 == b);
}

double eval (double a1,double a2)
{
    double valor = 0;
    string a = double_to_str(a1);
    string b = double_to_str(a2);
    int genero_a = str_to_int(char_to_string(a[0]));
    int genero_b = str_to_int(char_to_string(b[0]));

    if (genero_a != genero_b)
    {
        if (consecutivos(genero_a,genero_b)) return valor+0.5;
        else return valor;
    }

    valor +=1;
    //cout <<"level 1"<<endl;
    string aux1 = "", aux2 = "";
    aux1 += a[2];
    aux1 += a[3];
    aux2 += b[2];
    aux2 += b[3];
    int libro_a = str_to_int2(aux1);
    int libro_b = str_to_int2(aux2);
    if (libro_a != libro_b)
    {
        if (consecutivos(libro_a , libro_b)) return valor+0.5;
        else return valor;
    }
    valor +=1;
    //cout <<"level 2"<<endl;
    aux1 = aux2 = "";
    aux1 += a[4];
    aux1 += a[5];
    aux2 += b[4];
    aux2 += b[5];
    int volumen_a = str_to_int2(aux1);
    int volumen_b = str_to_int2(aux2);
    //cout<<"vola "<<volumen_a<<" volb "<<volumen_b<<endl;
    if (!consecutivos(volumen_a,volumen_b)) return valor;
    valor += 1;
    //cout <<"level 3"<<endl;
    //cout<<"genero "<<genero<<" libro "<<libro<<" volumen "<<volumen<<endl;
    return valor;
}

double fitness(vector <double> &sol1, vector<bool> &critic)
{
    double fit = 0;
    double aux;
    critic.push_back(0);
    for (int i = 0, j = 1; j < (int)sol1.size();j++,i++)
    {
        aux = eval(sol1[i],sol1[j]);
        if (aux == 0) critic.push_back(1);
        else critic.push_back(0);
        fit += aux;
    }
    return fit;
}

vector <int> where_is_critic(vector<bool> critico)
{
    vector<int> aux;
    for (int i=0;i<(int)critico.size();i++)
        if (critico[i]==1) aux.push_back(i);
    return aux;
}

vector<double> reproduccion(vector<double> sol1, vector<double> sol2, vector <bool> critic1)
{
    vector<int> puntos_cambiantes = where_is_critic(critic1),posiciones;
    vector<double> new_individuo = sol1;
    for (int i=0;i<(int)puntos_cambiantes.size();i++)
    {
        posiciones.push_back(Find(sol2,sol1[(puntos_cambiantes[i])]));
    }
    for (int i=0;i<(int)puntos_cambiantes.size();i++)
        swap(new_individuo[(puntos_cambiantes[i])],new_individuo[posiciones[i]]);
    return new_individuo;
}

vector <double> mutacion (vector<double> sol1, vector<bool>critic)
{
    vector <double> new_individuo=sol1;
    vector<int> puntos_criticos = where_is_critic(critic);
    if (puntos_criticos.size()%2==0)
    {
        for (int i=0,j=puntos_criticos.size()-1;i<j;i++,j--)
            swap(new_individuo[puntos_criticos[i]],new_individuo[puntos_criticos[j]]);
    }
    else
    {
        for (int i=0,j=puntos_criticos.size()-1;i!=(int)(puntos_criticos.size()-1)/2;i++,j--)
            swap(new_individuo[puntos_criticos[i]],new_individuo[puntos_criticos[j]]);
    }
    return new_individuo;
}

int main()
{
    vector <double> sol1, sol2,solucion;
    llenar_bd();
    generar_aleatorio(sol1);
    generar_aleatorio(sol2);
    string documento = "valores.txt";
    string datos = "";

    double time = 1.0;
    int iteracion = 0;
    do
    {
        vector <bool> critic1,critic2,cric;
        vector <double> aux1,aux2;
        int eval1 = fitness(sol1,critic1);
        int eval2 = fitness(sol2,critic2);
        solucion.clear();
        if (eval1 > eval2)
        {

            solucion = sol1;
            aux2 = mutacion(sol2,critic2);
            aux1 = reproduccion(sol1,sol2,critic1);
            //sol 2 = mutacion sol2
        }
        else
        {
            solucion = sol2;
            aux2 = mutacion(sol1,critic1);
            aux1 = reproduccion(sol2,sol1,critic2);
            //sol 2 = mutacion sol1
        }

        sol1.clear();
        sol2.clear();
        sol1 = aux1;
        sol2 = aux2;
        // sol1 = reproduccion
        /*Escribir los datos obtenidos en un txt*/
        string x = int_to_string(iteracion);
        string y = double_to_str(fitness(solucion,cric));
        datos = y;//x + " " + y;
        str_to_txt(documento,datos);
        datos = "";
        /*Incremento*/
        iteracion++;
        time -= 0.1;
    }while (time > 0.0);
    cout<<"----El orden es-----"<<endl;
    string documento2="orden.txt";
    string write = "";
    for (int i=0;i<(int)solucion.size();i++)
    {
        string codigo = double_to_str(solucion[i]);
        write = codigo + " " + books[(solucion[i])];
        str_to_txt(documento2,write);
        write = "";
        cout <<solucion[i]<<" "<<books[(solucion[i])]<<endl;
    }
    cout << "Hello world!" << endl;
    return 0;
}
    /* test 1
    for (int i=0;i<(int)sol1.size();i++)
        cout <<sol1[i]<<" "<<sol2[i]<<endl;
    cout<< "El fitness es "<<fitness(sol1,critic1)<<endl;
    cout<< "El fitness es "<<fitness(sol2,critic2)<<endl;
    cout<<"-------Critico-------------"<<endl;
    for (int i=0;i<(int)critic1.size();i++)
        cout <<critic1[i]<<" "<<critic2[i]<<endl;*/

    /* test 2
        vector <double> test = {0.2,0.8,0.3,0.5,0.9,0.5,1.2};
    vector <bool> tes2 = {0,1,1,0,0,1,1};
    vector <double> aux = mutacion(test,tes2);
    for ( int i=0;i<test.size();i++)
        cout<<test[i]<<" ";
    cout <<endl;
    for ( int i=0;i<aux.size();i++)
        cout<<aux[i]<<" ";
    cout <<endl;
    vector <double> aux2 = reproduccion(test,aux,tes2);
    for ( int i=0;i<aux2.size();i++)
        cout<<aux2[i]<<" ";
    cout <<endl;*/
