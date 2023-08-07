#include <iostream>
using namespace std;
void main() {
    int valores;
    cout << "Cuantos valores desea ingresar?" << endl;
    cin >> valores;

    int i = 0;
    int MaximoValor,PosMaximo,MinimoValor,PosMinimo;
    while (i < valores)
    {
        int numero;
        cout << "ingrese el valor numero "<< i+1 << ": ";
        cin >> numero;
        if (i==0)
        {
            MaximoValor = numero;
            MinimoValor = numero;
            PosMaximo = i + 1;
            PosMinimo = i + 1;
        }else if (numero > MaximoValor)
        {
            MaximoValor = numero;
            PosMaximo = i + 1;
        }
        if(numero < MinimoValor)
        {
            MinimoValor = numero;
            PosMinimo = i + 1;
        }
        i++;
    }
    cout << "el valor mas grande es: " << MaximoValor << " y fue ingresado en la posicion: " << PosMaximo << endl;
    cout << "el valor mas chico es: " << MinimoValor << " y fue ingresado en la posicion: " << PosMinimo << endl;
    system("pause");
}