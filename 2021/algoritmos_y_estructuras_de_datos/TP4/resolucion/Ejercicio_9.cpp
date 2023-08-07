#include <iostream>
using namespace std;

struct ACTA {
    char NomApe[20 + 1];
    int Libro, Folio, Fecha, CodigoMateria, Legajo, Nota;
};

void ordenarVector(ACTA[], int);

void main9() {

    struct TOTAL {
        int Libro, Folio, AlumnosInscriptos = 0, AlumnosAusentes = 0, AlumnosAprobados = 0, AlumnosDesaprobados = 0;
    };

    ACTA actas[10];
    int CantActas = 0;
    for (int i = 0; i < 10; i++)
    {
        do {
            cout << endl << "ingrese el libro: ";
            cin >> actas[i].Libro;
        } while (actas[i].Libro > 999999);

        if (actas[i].Libro <= 0)
        {
            break;
        }

        CantActas++;

        do {
            cout << "ingrese el folio: ";
            cin >> actas[i].Folio;
        } while (actas[i].Folio < 1 || actas[i].Folio > 999);

        do {
            cout << "ingrese la fecha: ";
            cin >> actas[i].Fecha;
        } while (actas[i].Fecha < 10000000 || actas[i].Fecha > 99999999);

        do {
            cout << "ingrese el codigo de materia: ";
            cin >> actas[i].Fecha;
        } while (actas[i].Fecha < 100000 || actas[i].Fecha > 999999);

        do {
            cout << "Ingresar legajo: ";
            cin >> actas[i].Legajo;
        } while (actas[i].Legajo < 1 || actas[i].Legajo > 9999999999);

        do {
            cout << "Ingresar nombre y apellido del alumno: ";
            cin >> actas[i].NomApe;
        } while (strlen(actas[i].NomApe) > 20);

        do {
            cout << "Ingresar nota: ";
            cin >> actas[i].Nota;
        } while (actas[i].Nota < 0 || actas[i].Nota > 10);
    }

    ordenarVector(actas, CantActas);

    FILE* f;
    errno_t pFile = fopen_s(&f, "ACTASFINALES.DAT", "wb+");
    for (int i = 0; i < CantActas; i++)
    {
        fwrite(&actas[i], sizeof(ACTA), 1, f);
    }

    ACTA actas2[10];
    fseek(f, 0, SEEK_SET);
    int CantActas2 = 0;
    fread(&actas2[0], sizeof(ACTA), 1, f);
    while (!feof(f))
    {
        CantActas2++;
        fread(&actas2[CantActas2], sizeof(ACTA), 1, f);
    }

    TOTAL totales[10];
    int j = 0;    
    for (int i = 0; i < CantActas2; i++)
    {
        while (j == i || (totales[i].Libro == actas2[j].Libro && totales[i].Folio == actas2[j].Folio)) {

            if (j == i) {
                totales[i].Libro = actas2[j].Libro;
                totales[i].Folio = actas2[j].Folio;
                if (actas2[j].Nota >= 6) {
                    totales[i].AlumnosAprobados++;
                }
                else if (actas2[j].Nota > 0 || actas2[j].Nota < 6)
                {
                    totales[i].AlumnosDesaprobados++;
                }
                if (actas2[j].Nota == 0) {
                    totales[i].AlumnosAusentes++;
                }
                totales[i].AlumnosInscriptos++;
            }
            else {
                if (totales[i].Libro == actas2[j].Libro && totales[i].Folio == actas2[j].Folio) {
                    if (actas2[j].Nota >= 6) {
                        totales[i].AlumnosAprobados++;
                    }
                    else if (actas2[j].Nota > 0 || actas2[j].Nota < 6)
                    {
                        totales[i].AlumnosDesaprobados++;
                    }
                    if (actas2[j].Nota == 0) {
                        totales[i].AlumnosAusentes++;
                    }
                    totales[i].AlumnosInscriptos++;
                }
                else {
                }
            }
            j++;
        }
    }
    fclose(f);

    FILE* f2;
    errno_t pFile2 = fopen_s(&f2, "TOTALES.DAT", "wb+");
    int i = 0;
    while (totales[i].Libro > 0)
    {
        fwrite(&totales[i], sizeof(TOTAL), 1, f2);
        i++;
    }
    fclose(f2);

}

void ordenarVector(ACTA v[], int N) 
{
    int i, j, repe = 0;
    ACTA aux, aux2;
    for (i = 1; i < N; i++) {
        int M = N - i;
        int w;
        for (j = 1; j <= M; j++) {
            if (v[j - 1].Libro > v[j].Libro) {
                int H = j - 1;
                aux = v[j];
                v[j] = v[H];
                v[H] = aux;
            }
            if (v[j - 1].Libro == v[j].Libro)
            {
                if (v[j - 1].Folio > v[j].Folio) {
                    if (repe == 0) {
                        w = j - 1;
                        aux2 = v[j];
                        repe++;
                    }
                    else
                    {
                        if (v[j - 1].Folio > aux2.Folio) {
                            w = j - 1;
                            aux2 = v[j];
                        }
                    }
                    v[j] = v[w];
                    v[w] = aux2;
                }
            }
        }
    }
}