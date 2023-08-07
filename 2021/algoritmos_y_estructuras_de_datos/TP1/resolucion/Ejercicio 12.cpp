#include <iostream>
#include <cstring>
using namespace std;
void main() {
    char nombre[10 + 1]; int fecha, fechaMayor, fechaMenor, i = 0;
    char nombreMayor[10 + 1], nombreJoven[10 + 1];

    cout << "Ingrese su nombre:" << endl;
    cin >> nombre;

    strcpy_s(nombreMayor, nombre);
    strcpy_s(nombreJoven, nombre);
    int resultado = strcmp("FIN", nombre);

    while (resultado != 0)
    {
        cout << "Ingrese su fecha de nacimiento en formato (AAAAMMDD):" << endl;
        cin >> fecha;

        if (i == 0)
        {
            fechaMayor = fecha;
            fechaMenor = fecha;
        }else if(fecha > fechaMayor)
        {
            fechaMenor = fecha;
            strcpy_s(nombreJoven, nombre);
        }else if (fecha < fechaMenor)
        {
            fechaMayor = fecha;
            strcpy_s(nombreMayor, nombre);
        }


        cout << "Ingrese su nombre (FIN si desea ver los resultados):" << endl;
        cin >> nombre;
        resultado = strcmp("FIN", nombre);
        i++;
    }

    cout << "La persona mas joven es " << nombreJoven << endl;
    cout << "La persona mas grande es " << nombreMayor << endl;
}