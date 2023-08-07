#include <iostream>
using namespace std;

void main3() {
	FILE* f;
	errno_t pFile = fopen_s(&f, "EJERCICIO2.DAT", "rb+");

	FILE* f2;
	errno_t pFile2 = fopen_s(&f2, "EJERCICIO3.DAT", "wb+");

	struct BOLETA {
		char NomApe[25 + 1];
		int Legajo, CodigoMateria, DiaEx, MesEx, AnioEx;
	};

	int CodigoBuscado;
	cout << "Ingrese el codigo de materia que desea buscar: ";
	cin >> CodigoBuscado;
	
	if (pFile == 0)
	{
		BOLETA b;
		while (fread(&b, sizeof(BOLETA), 1, f)) {
			if (CodigoBuscado == b.CodigoMateria) {
				fwrite(&b, sizeof(BOLETA), 1, f2);
			}
		}
	}
	else {
		cout << "No se encontro el archivo";
	}
	fclose(f);
	fclose(f2);
}