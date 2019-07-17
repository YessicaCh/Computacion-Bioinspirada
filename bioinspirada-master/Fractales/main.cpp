#include <iostream>
#include <string>
using namespace std;
bool reglas(string &regla)
{
    string newRegla;
    for (int i=0;i<(int)regla.size();i++)
    {
        char nuevo;
        if (i-1<0 && regla[i]=='0' && regla[i+1]=='0') nuevo='0';
        else if (i+1>=regla.size() && regla[i-1]=='0' && regla[i]=='0') nuevo='0';
        else if (regla[i-1]==regla[i]&&regla[i]==regla[i+1]) nuevo = '0';
        else nuevo = '1';
        newRegla+=nuevo;
    }
    regla=newRegla;
}
int main()
{
    string regla;
    int cantidadInicial = 50;
    for (int i = 0;i<cantidadInicial+1;i++)
    {
        regla+="0";
    }
    regla[cantidadInicial/2] ='1';
    int nIteraciones = cantidadInicial;
    for (int i =0;i<nIteraciones;i++)
    {
        cout<<regla<<endl;
        reglas(regla);
    }
    cout<<regla<<endl;
    cout << "Hello world!" << endl;
    return 0;
}
