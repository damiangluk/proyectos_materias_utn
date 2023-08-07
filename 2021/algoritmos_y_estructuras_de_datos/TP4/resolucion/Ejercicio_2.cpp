#include <iostream>
using namespace std;

void main2() {
    FILE* f;
    errno_t pFile = fopen_s(&f, "EJERCICIO2.DAT", "wb+");

    struct BOLETA {
        char NomApe[25 + 1];
        int Legajo, CodigoMateria, DiaEx, MesEx, AnioEx;
    };

    BOLETA boleta;

    do {
        cout << "Ingresar nombre y apellido: ";
        cin >> boleta.NomApe;
    } while (strlen(boleta.NomApe) > 25);

    while (strcmp(boleta.NomApe, "-")) {

        do {
            cout << "ingrese el Legajo: ";
            cin >> boleta.Legajo;
        } while (boleta.Legajo < 1 || boleta.Legajo > 99999999);

        do {
            cout << "ingrese el Codigo de materia: ";
            cin >> boleta.CodigoMateria;
        } while (boleta.CodigoMateria < 1 || boleta.CodigoMateria > 999999);

        do {
            cout << "ingrese el Dia del examen: ";
            cin >> boleta.DiaEx;
        } while (boleta.DiaEx < 1 || boleta.DiaEx > 31);

        do {
            cout << "Ingresar el Mes del examen: ";
            cin >> boleta.MesEx;
        } while (boleta.MesEx < 1 || boleta.MesEx > 12);

        do {
            cout << "Ingresar el Anio del examen: ";
            cin >> boleta.AnioEx;
        } while (boleta.AnioEx < 1000 || boleta.AnioEx > 9999);

        cout << endl;
        fwrite(&boleta, sizeof(BOLETA), 1, f);

        do {
            cout << "Ingresar nombre y apellido: ";
            cin >> boleta.NomApe;
        } while (strlen(boleta.NomApe) > 25);
    }
    fclose(f);
}