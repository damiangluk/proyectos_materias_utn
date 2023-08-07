#include <iostream>
using namespace std;

void main()
{
    int L1, L2, L3;

    cout << "Ingrese la longitud del primer lado: "; cin >> L1;
    cout << "Ingrese la longitud del segundo lado: "; cin >> L2;
    cout << "Ingrese la longitud del tercer lado: "; cin >> L3;

    if (L1 == L2 && L2 == L3 && L3 == L1)
        cout << "Es un triangulo Equilatero" << endl;
    else if (L1 == L2 || L1 == L3 || L2 == L3)
        cout << "Es un triangulo Isosceles" << endl;
    else
        cout << "Es un triangulo Escaleno" << endl;
}