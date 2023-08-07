#include <iostream>
using namespace std;
void main()
{
    int a, b, c, max;
    cout << "Ingresa el valor de a: ";
    cin >> a;

    cout << "Ingresa el valor de b: ";
    cin >> b;

    cout << "Ingresa el valor de c: ";
    cin >> c;

    if (a > b && a > c)
    {
        if ((c + b) > a) {
            cout << "Se puede formar un triangulo" << endl;
        }
        else {
            cout << "No se puede formar un triangulo" << endl;
        }
    }
    else if (b > a && b > c)
    {
        if ((c + a) > b) {
            cout << "Se puede formar un triangulo" << endl;
        }
        else {
            cout << "No se puede formar un triangulo" << endl;
        }
    }
    else if (c > a && c > b)
    {
        if ((a + b) > c) {
            cout << "Se puede formar un triangulo" << endl;
        }
        else {
            cout << "No se puede formar un triangulo" << endl;
        }
    }
    else if (c == a && c == b) {
        cout << "Se puede formar un triangulo" << endl;
    }
    else if (a == c || a == b) {
        cout << "Se puede formar un triangulo" << endl;
    }
    else {
        cout << "No se puede formar un triangulo" << endl;
    }
}