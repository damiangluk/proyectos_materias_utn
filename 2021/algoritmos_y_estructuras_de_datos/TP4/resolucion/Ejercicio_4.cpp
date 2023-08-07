#include <iostream>
using namespace std;

void ordenamiento(int);
bool busqueda(int, int);

struct ALUMNOS {
	char nombreYApellido[25 + 1];
	int NroDeLegajo;
};
ALUMNOS alumnos[10] = { 0 };

void main4() {
	FILE* f;
	errno_t pFile = fopen_s(&f, "EJERCICIO3.DAT", "rb+");

	FILE* f2;
	errno_t pFile2 = fopen_s(&f2, "EJERCICIO4.DAT", "wb+");
	
	struct BOLETA {
		char nombreYApellido[25 + 1];
		int NroDeLegajo, codigoDeMateria, diaDelExamen, mesDelExamen, anioDelExamen;
	};

	BOLETA boletas[10] = { 0 };
	
	int boletasLeidas = 0;
	fread(&boletas[0], sizeof(BOLETA), 1, f);
	while (!feof(f)) {
		boletasLeidas++;
		fread(&boletas[boletasLeidas], sizeof(BOLETA), 1, f);
	}
	int cantalumnos = 0;
	for (int a = 0; a < boletasLeidas; a++)
	{
		if (!busqueda(boletas[a].NroDeLegajo, cantalumnos) && boletas[a].NroDeLegajo != 0) {
			alumnos[cantalumnos].NroDeLegajo = boletas[a].NroDeLegajo;
			strcpy_s(alumnos[cantalumnos].nombreYApellido, boletas[a].nombreYApellido);
			cantalumnos++;
		}
	}
	ordenamiento(cantalumnos);
	for (int k = 0; k < cantalumnos; k++)
	{
		fwrite(&alumnos[k], sizeof(ALUMNOS), 1, f2);
	}

}
void ordenamiento(int cantidad) {
	for (int a = 0; a < cantidad; a++)
	{
		for (int b = 0; b < (cantidad - 1); b++)
		{
			if (alumnos[b].NroDeLegajo > alumnos[b + 1].NroDeLegajo)
			{
				ALUMNOS aux = alumnos[b];
				alumnos[b] = alumnos[b + 1];
				alumnos[b + 1] = aux;
			}
		}
	}
}
bool busqueda(int buscado, int cantidad) {
	for (int i = 0; i < cantidad; i++)
	{
		if (buscado == alumnos[i].NroDeLegajo) {
			return 1;
		}
	}
	return 0;
}