#include <iostream>
#include "Grilla.h"
using namespace std;

int main()
{
    Grilla gri1(20);
    int time=0;
    while (time<10)
    {
        gri1.Simular();
        time++;
    }

    cout << "Hello world!" << endl;
    return 0;
}
