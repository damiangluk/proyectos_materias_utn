#include <iostream>
using namespace std;

FILE* f;
errno_t pFile;
FILE* f2;
errno_t pFile2;

struct alumno {
	char nomYape[34 + 1];
	int NroDeLegajo, divAsignada;
};

void burbuja(alumno[], int);
int cantReg(FILE*);
void cargarArchivo();

void main() {
	//cargarArchivo(); para cargar el archivo ARCHA
	pFile = fopen_s(&f, "ARCHA.dat", "rb+");
	pFile2 = fopen_s(&f2, "ARCHL.dat", "wb+");
	int n = cantReg(f);

	alumno vec[4];
	fseek(f, 0, SEEK_SET);
	fread(vec, sizeof(alumno), n, f);
	burbuja(vec, n);

	for (int x = 0; x < 4; x++)
	{
		cout << "Alumno: " << vec[x].nomYape << " Numero de legajo: " << vec[x].NroDeLegajo << " Division asignada: " << vec[x].divAsignada << endl;
		fwrite(&vec[x], sizeof(alumno), 1, f2);
	}
	fclose(f);
	fclose(f2);
}

int cantReg(FILE* f) {
	int posInicial = ftell(f);
	fseek(f, 0, SEEK_END);
	int T = ftell(f);
	int cantReg = T / sizeof(alumno);
	fseek(f, posInicial, SEEK_SET);
	return cantReg;
}

void burbuja(alumno vec[], int N) {
	int x, y;
	alumno aux;
	for (x = 1; x < N; x++) {
		for (y = 1; y <= N - x; y++) {
			if (vec[y - 1].NroDeLegajo > vec[y].NroDeLegajo) {
				aux = vec[y];
				vec[y] = vec[y - 1];
				vec[y - 1] = aux;
			}
		}
	}
	return;
}

void cargarArchivo()
{
	pFile = fopen_s(&f, "ARCHA.dat", "wb+");
	alumno alu;
	do {
		cout << "Ingresar el nombre y apellido : ";
		cin >> alu.nomYape;
	} while (strlen(alu.nomYape) >= 34);

	while (strcmp(alu.nomYape, "-")) {

		do {
			cout << "ingrese el Nro. de legajo: ";
			cin >> alu.NroDeLegajo;
		} while (alu.NroDeLegajo < 1 || alu.NroDeLegajo > 999999);

		do {
			cout << "ingrese la division asignada: ";
			cin >> alu.divAsignada;
		} while (alu.divAsignada < 1 || alu.divAsignada > 101);


		if (pFile == 0)
		{
			fseek(f, 0, SEEK_END);
			fwrite(&alu, sizeof(alumno), 1, f);
		}
		else {
			cout << "No se puede cargar el archivardo" << endl;
		}

		do {
			cout << "Ingresar el nombre y apellido : ";
			cin >> alu.nomYape;
		} while (strlen(alu.nomYape) >= 34);

	}
	fclose(f);
}