#include <iostream>
//#include <algorithm>
//#include <math.h>
#include <bits/stdc++.h>
using namespace std;
#include "redesInmunes.h"
int main()
{
    vector <int*> patrones;
    int * pat = new int[2];
    pat[0] = 3;
    pat[1] = 3;
    patrones.push_back(pat);
    int * pat2 = new int[2];
    pat2[0] = 1;
    pat2[1] = 1;
    patrones.push_back(pat2);
    int * pat3 = new int[2];
    pat3[0] = 2;
    pat3[1] = 4;
    patrones.push_back(pat3);
    redesInmunes ri(patrones,0.10,0.10,5,1);
    ri.inicio();
    ri.Print();
    cout << "Hello world!" << endl;
    return 0;
}
