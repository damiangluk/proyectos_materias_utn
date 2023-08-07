#include <iostream>
using namespace std;

struct ALUMNO {
    int legajo, codigoPostal, anioDeIngreso;
    char apellidoYNombre[30 + 1], domicilio[20 + 1], telefono[10 + 1];
};

struct NOVEDAD {
    ALUMNO alumno;
    char operacion;
};

void ordenar(ALUMNO[], int);
int busquedaBinaria(ALUMNO[], int, int);
ALUMNO IngresarAlumnos(FILE*, char[]);

void main10() 
{
    cout << "INGRESO DE ALUMNOS";
    FILE* f;
    errno_t pFile = fopen_s(&f, "ALUMNOS.DAT", "wb+");
    ALUMNO alumno;
    int CantAlumnos;
    for (CantAlumnos = 0; CantAlumnos < 10; CantAlumnos++) {

        do {
            cout << endl << "Ingrese el nombre del alumno: ";
            cin >> alumno.apellidoYNombre;
        } while (strlen(alumno.apellidoYNombre) > 30);

        if (!strcmp(alumno.apellidoYNombre, "-"))
        {
            break;
        }

        alumno = IngresarAlumnos(f, alumno.apellidoYNombre);
        fwrite(&alumno, sizeof(ALUMNO), 1, f);
    }

    cout << endl << "INGRESO DE NOVEDADES";
    FILE* f2;
    errno_t pFile2 = fopen_s(&f2, "NOVEDADES.DAT", "wb+");
    NOVEDAD novedad;
    int CantNovedades;
    for (CantNovedades = 0; CantNovedades < 10; CantNovedades++) {

        do {
            cout << endl << "Ingrese el nombre del alumno: ";
            cin >> alumno.apellidoYNombre;
        } while (strlen(alumno.apellidoYNombre) > 30);

        if (!strcmp(alumno.apellidoYNombre, "-"))
        {
            break;
        }
        alumno = IngresarAlumnos(f, alumno.apellidoYNombre);
        novedad.alumno = alumno;

        do {
            cout << "Ingrese la operacion a realizar: ";
            cin >> novedad.operacion;
        } while (novedad.operacion != 'A' && novedad.operacion != 'B' && novedad.operacion != 'M');

        fwrite(&novedad, sizeof(NOVEDAD), 1, f2);
    }
    
    ALUMNO alumnos[10] = { 0 };
    fseek(f, 0, SEEK_SET);
    fread(&alumnos, sizeof(ALUMNO), CantAlumnos, f);
    ordenar(alumnos, CantAlumnos);

    NOVEDAD novedades[10] = { 0 };
    fseek(f2, 0, SEEK_SET);
    fread(&novedades, sizeof(NOVEDAD), CantNovedades, f2);

    int CantAlumnosActualizados = 0;
    ALUMNO alumnosActualizados[20] = { 0 };

    for (int i = 0; i < CantNovedades; i++)
    {
        if (novedades[i].operacion == 'A') {
            alumnosActualizados[CantAlumnosActualizados] = novedades[i].alumno;
            CantAlumnosActualizados++;
        }
        else if (novedades[i].operacion == 'B')
        {
            int pos = busquedaBinaria(alumnos, novedades[i].alumno.legajo, CantAlumnos);
            if (pos != -1)
            {
                alumnos[pos].legajo = -1;
            }
        }
        else if (novedades[i].operacion == 'M');
        {
            int pos = busquedaBinaria(alumnos, novedades[i].alumno.legajo, CantAlumnos);
            if (pos != -1) {
                alumnos[pos] = novedades[i].alumno;
            }
        }
    }

    for (int i = 0; i < CantAlumnos; i++)
    {
        if (alumnos[i].legajo != -1) {
            alumnosActualizados[CantAlumnosActualizados] = alumnos[i];
            CantAlumnosActualizados++;
        }
    }
    ordenar(alumnosActualizados, CantAlumnosActualizados);

    FILE* f3;
    errno_t pFile3 = fopen_s(&f3, "ALUMACTU.DAT", "wb+");
    fwrite(&alumnosActualizados, sizeof(ALUMNO), CantAlumnosActualizados, f3);

    fclose(f);
    fclose(f2);
    fclose(f3);
}

ALUMNO IngresarAlumnos(FILE* f, char nombre[])
{
    ALUMNO al;
    strcpy_s(al.apellidoYNombre, nombre);
    do {
        cout << "ingrese el legajo: ";
        cin >> al.legajo;
    } while (al.legajo < 1 || al.legajo > 99999999);

    do {
        cout << "ingrese el domicilio: ";
        cin >> al.domicilio;
    } while (strlen(al.domicilio) > 30);

    do {
        cout << "ingrese el codigo postal: ";
        cin >> al.codigoPostal;
    } while (al.codigoPostal < 1 || al.codigoPostal > 9999);

    do {
        cout << "ingrese el telefono: ";
        cin >> al.telefono;
    } while (strlen(al.telefono) > 10);

    do {
        cout << "Ingresar anio del ingreso: ";
        cin >> al.anioDeIngreso;
    } while (al.anioDeIngreso < 1000 || al.anioDeIngreso > 2021);

    return al;
}

void ordenar(ALUMNO v[], int N) {
    ALUMNO aux;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (N - 1); j++) {
            if (v[j].legajo > v[j + 1].legajo) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

int busquedaBinaria(ALUMNO v[], int buscado, int N) {

    int primero = 0, medio, ultimo = N - 1;
    while (primero <= ultimo) {
        medio = (primero + ultimo) / 2;
        if (v[medio].legajo == buscado)
        {
            return medio;
        }
        if (buscado > v[medio].legajo)
        {
            primero = medio + 1;
        }
        else ultimo = medio - 1;
    };
    return -1;
}