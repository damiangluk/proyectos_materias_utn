#include <iostream>
using namespace std;

struct BOLETA {
    char NomApe[25 + 1];
    int Legajo, CodigoMateria, DiaEx, MesEx, AnioEx;
};

void ordenamiento(BOLETA[], int);

void main5() {
    FILE* f;
    errno_t pfile = fopen_s(&f, "EJERCICIO2.DAT", "rb+");

    FILE* f2;
    errno_t pfile2 = fopen_s(&f2, "EJERCICIO2_2.DAT", "rb+");

    if (pfile == 0 || pfile2 == 0)
    {
        BOLETA BoletasTotales[10] = { 0 };
        int CantTotales = 0;
        fread(&BoletasTotales[0], sizeof(BOLETA), 1, f);
        while (!feof(f))
        {
            CantTotales++;
            fread(&BoletasTotales[CantTotales], sizeof(BOLETA), 1, f);
        }
        ordenamiento(BoletasTotales, CantTotales);

        BOLETA BoletasDia[10] = { 0 };
        int CantDia = 0;
        fread(&BoletasDia[0], sizeof(BOLETA), 1, f2);
        while (!feof(f2))
        {
            CantDia++;
            fread(&BoletasDia[CantDia], sizeof(BOLETA), 1, f2);
        }
        ordenamiento(BoletasDia, CantDia);

        //APAREO
        int TotalesIndex = 0, DiaIndex = 0, FinalesIndex = 0;
        BOLETA BoletasFinales[20] = { 0 };

        while (TotalesIndex < 10 && DiaIndex < 10 && BoletasTotales[TotalesIndex].Legajo != 0 && BoletasDia[DiaIndex].Legajo != 0) {
            if (BoletasTotales[TotalesIndex].CodigoMateria < BoletasDia[DiaIndex].CodigoMateria) {
                BoletasFinales[FinalesIndex] = BoletasTotales[TotalesIndex];
                FinalesIndex++;
                TotalesIndex++;
            }
            else {
                BoletasFinales[FinalesIndex] = BoletasDia[DiaIndex];
                FinalesIndex++;
                DiaIndex++;
            }
        }

        while (TotalesIndex < 10 && BoletasTotales[TotalesIndex].Legajo != 0) {
            BoletasFinales[FinalesIndex] = BoletasTotales[TotalesIndex];
            FinalesIndex++;
            TotalesIndex++;
        }

        while (DiaIndex < 10 && BoletasDia[DiaIndex].Legajo != 0) {
            BoletasFinales[FinalesIndex] = BoletasDia[DiaIndex];
            FinalesIndex++;
            DiaIndex++;
        }

        fclose(f);
        fclose(f2);

        FILE* f3;
        errno_t pFile3 = fopen_s(&f3, "EJERCICIO5.DAT", "wb+");
        fwrite(&BoletasFinales, sizeof(BOLETA), (CantTotales + CantDia), f3);
        fclose(f3);
    }
    else
    {
        cout << "Uno de los archivos no se pudo cargar";
    }
}

void ordenamiento(BOLETA v[], int N) {
    BOLETA aux;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < (N - 1); j++) 
        {
            if (v[j].CodigoMateria > v[j + 1].CodigoMateria) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}