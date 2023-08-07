#include <iostream>
#include <cstring>
#include <string>
using namespace std;

void Solucion1(int, int, int);
void Solucion2(int, int, int);

void main() {
    int anio = 0, solucion = 0;
    int a, b, c, d, e;

    while (anio < 1900 || anio > 2100)
    {
        cout << "Ingrese un anio comprendido entre 1900 y 2100: " << endl;
        cin >> anio;
    }

    while (solucion != 1 && solucion != 2)
    {
        cout << "Ingrese solucion (1 o 2): " << endl;
        cin >> solucion;
    }

    a = anio % 19;
    b = anio % 4;
    c = anio % 7;
    d = (19 * a + 24) % 30;
    e = (2 * b + 4 * c + 6 * d + 5) % 7;

    if (solucion == 1)
    {
        Solucion1(d, e, a);
    }
    else
    {
        Solucion2(d, e, a);
    }
}

void Solucion1(int d, int e, int a)
{
    int suma = d + e;
    if (suma < 10)
    {
        cout << "La Pascua caera el " << suma + 22 << " de Marzo";
    }
    else if (suma > 9)
    {
        int Dia = suma - 9;
        if (Dia == 26)
        {
            cout << "La Pascua caera el 19 de Abril";
        }
        else if (Dia == 25 && d == 28 && e == 6 && a > 10)
        {
            cout << "La Pascua caera el 18 de Abril";
        }
        else
        {
            cout << "La Pascua caera el " << Dia << " de Abril";
        }
    }

}

void Solucion2(int d, int e, int a)
{
    if ((d + e) < 10)
    {
        int Dia = d + e + 22;
        string fecha = "03/" + std::to_string(d + e + 22);
        cout << "La fecha de Pascua sera " << fecha;
    }
    else if ((d + e) > 9)
    {
        string fecha;
        int Dia = (d + e - 9);
        if (Dia == 26)
        {
            fecha =  "04/19";
        }
        else if (Dia == 25 && d == 28 && e == 6 && a > 10)
        {
            fecha = "04/19";
        }
        else
        {
            fecha = "04/";
            if (Dia <= 9)
            {
                fecha += "0";
            }
            fecha += std::to_string(Dia);
        }
        cout << "La fecha de Pascua sera " << fecha;
    }
}