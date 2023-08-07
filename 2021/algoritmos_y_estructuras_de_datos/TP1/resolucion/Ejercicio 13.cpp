#include <iostream>
#include <cstring>

using namespace std;
void main() {
    float maxNegativo = 0, minPositivo = 0, minRango = 0;
    float sumaValores = 0, promedio, cantNumIngresados = 0;
    float valor;
    cout << "ingrese un numero: ";
    cin >> valor;
    while (valor != 0)
    {
        if (valor > 0 && (minPositivo == 0 || valor < minPositivo))
        {
            minPositivo = valor;
        }
        else if (valor < 0 && (maxNegativo == 0 || valor > maxNegativo))
        {
            maxNegativo = valor;
        }
        if (valor >= -17.3 && valor <= 26.9 && (minRango == 0 || valor < minRango)) {
            minRango = valor;
        }
        sumaValores = sumaValores + valor;
        cantNumIngresados++;
        cout << "ingrese un numero: ";
        cin >> valor;
    }
    if (cantNumIngresados == 0)
    {
        cout << "No se ingresaron numeros";
    }
    else
    {
        promedio = sumaValores / cantNumIngresados;
        cout << "el maximo de los negativos es: " << maxNegativo << endl;
        cout << "el minimo de los positivos es: " << minPositivo << endl;
        cout << "el promedio de valores es: " << promedio << endl;
        cout << "el minimo valor entre el rango -17.3 y 26.9 es: " << minRango << endl;
    }
}