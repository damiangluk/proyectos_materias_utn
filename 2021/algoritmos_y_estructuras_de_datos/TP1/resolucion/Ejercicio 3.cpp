#include <iostream>
using namespace std;

void main()
{
    int suma = 0;

    for (int i = 2; i <= 10000; i = i+2) {
        suma += i;
    }

    cout << "La suma de los numeros pares entre 2 y 10000 es: " << suma;
}