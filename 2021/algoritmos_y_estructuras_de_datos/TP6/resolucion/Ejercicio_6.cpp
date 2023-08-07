#include <iostream>
using namespace std;

FILE* f;
errno_t pFile;

struct acta {
    char apellidoYNombre[20 + 1];
    int division, legajo;
};

void ordenarxDivisionLegajo(acta[], int);
int cantReg(FILE*);

void main() 
{
    acta act[3];
    for (int i = 0; i < 3; i++)
    {
        do {
            cout << "ingrese la division: ";
            cin >> act[i].division;
        } while (act[i].division < 1);
        do {
            cout << "Ingresar legajo: ";
            cin >> act[i].legajo;
        } while (act[i].legajo < 1 || act[i].legajo > 9999999999);

        do {
            cout << "Ingresar nombre y apellido del alumno: ";
            cin >> act[i].apellidoYNombre;
        } while (strlen(act[i].apellidoYNombre) > 20);
    }
    ordenarxDivisionLegajo(act, 3);

    pFile = fopen_s(&f, "ARCHA.dat", "wb+");

    fseek(f, 0, SEEK_END);
    fwrite(act, sizeof(acta), 3, f);
    fclose(f);

    pFile = fopen_s(&f, "ARCHA.dat", "rb+");
    int n = cantReg(f);
    acta acta[3];
    fseek(f, 0, SEEK_SET);
    fread(acta, sizeof(acta), n, f);

    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << ". Alumno: " << acta[i].apellidoYNombre << ",Legajo: " << acta[i].legajo << ", Division: " << acta[i].division << endl;
    }
}

int cantReg(FILE* f) {
    int posInicial = ftell(f);
    fseek(f, 0, SEEK_END);
    int T = ftell(f);
    int cantReg = T / sizeof(acta);
    fseek(f, posInicial, SEEK_SET);
    return cantReg;
}

void ordenarxDivisionLegajo(acta v[], int N) {
    int i, j, repe = 0;
    acta aux, aux2;
    for (i = 1; i < N; i++) {
        int M = N - i;
        int w;
        for (j = 1; j <= M; j++) {
            if (v[j - 1].division > v[j].division) {
                int H = j - 1;
                aux = v[j];
                v[j] = v[H];
                v[H] = aux;
            }
            if (v[j - 1].division == v[j].division)
            {
                if (v[j - 1].legajo > v[j].legajo) {
                    if (repe == 0) {
                        w = j - 1;
                        aux2 = v[j];
                        repe++;
                    }
                    else
                    {
                        if (v[j - 1].legajo > aux2.legajo) {
                            w = j - 1;
                            aux2 = v[j];
                        }
                    }
                    v[j] = v[w];
                    v[w] = aux2;
                }
            }
        } // fin ciclo interno
    }// fin ciclo externo
} // fin de la funcion