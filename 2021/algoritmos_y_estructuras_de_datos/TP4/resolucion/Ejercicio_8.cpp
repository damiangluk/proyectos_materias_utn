#include <iostream> 
using namespace std;

struct VUELO { int CodigoVuelo, CantDisponible; };
struct VUELO_SOLICITADO { int CodigoVueloSolicitado, CantSolicitado, Dni; char NomApe[20]; };

void ordenarVector(VUELO[], int);
int busquedaBinaria(VUELO[], int, int);

void main8()
{
	FILE* f;
	errno_t pfile = fopen_s(&f, "VUELOS.DAT", "wb+");
	FILE* f1;
	errno_t pfile1 = fopen_s(&f1, "VUELOS_SOLICITADOS.DAT", "wb+");

	VUELO vuelos[10];
	VUELO_SOLICITADO vuelos_solicitados[10];
	VUELO ingresoVuelo;
	VUELO_SOLICITADO ingresoVueloSolicitado;

	cout << "INGRESO DE VUELOS" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << "Ingrese el codigo del vuelo: ";
		cin >> ingresoVuelo.CodigoVuelo;
		if (ingresoVuelo.CodigoVuelo <= 0)
		{
			break;
		}
		cout << "Ingrese la Cantidad de pasajes disponibles: ";
		cin >> ingresoVuelo.CantDisponible;

		fwrite(&ingresoVuelo, sizeof(VUELO), 1, f);
	}

	cout << endl << "INGRESO DE VUELOS SOLICITADOS";

	for (int i = 0; i < 10; i++)
	{
		cout << endl << "Ingrese el codigo de vuelo solicitado: ";
		cin >> ingresoVueloSolicitado.CodigoVueloSolicitado;
		if (ingresoVueloSolicitado.CodigoVueloSolicitado <= 0)
		{
			break;
		}

		do
		{
			cout << "Ingrese la Cantidad de pasajes solicitados: ";
			cin >> ingresoVueloSolicitado.CantSolicitado;
			cout << "Ingrese el DNI del solicitante: ";
			cin >> ingresoVueloSolicitado.Dni;
			cout << "Ingrese el apellido y nombre del solicitante: ";
			cin >> ingresoVueloSolicitado.NomApe;
		} while (ingresoVueloSolicitado.CodigoVueloSolicitado > 999999 || strlen(ingresoVueloSolicitado.NomApe) > 30 || ingresoVueloSolicitado.CantSolicitado > 999 || ingresoVueloSolicitado.Dni > 99999999);

		fwrite(&ingresoVueloSolicitado, sizeof(VUELO_SOLICITADO), 1, f1);
	}

	fseek(f, 0, SEEK_SET);
	fseek(f1, 0, SEEK_SET);

	int CantVuelos = 0;
	fread(&vuelos[0], sizeof(VUELO), 1, f);
	while (!feof(f) && CantVuelos < 10)
	{
		CantVuelos++;
		fread(&vuelos[CantVuelos], sizeof(VUELO), 1, f);
	}

	int CantVuelosSolicitados = 0;
	fread(&vuelos_solicitados[0], sizeof(VUELO_SOLICITADO), 1, f1);
	while (!feof(f1) && CantVuelosSolicitados < 10)
	{
		CantVuelosSolicitados++;
		fread(&vuelos_solicitados[CantVuelosSolicitados], sizeof(VUELO_SOLICITADO), 1, f1);
	}

	ordenarVector(vuelos, CantVuelos);

	cout << endl << "VUELOS SOLICITADOS" << endl;

	int pos, NoVendidos[10] = { 0 };
	for (int i = 0; i < CantVuelosSolicitados; i++)
	{
		if (vuelos_solicitados[i].CodigoVueloSolicitado <= 0)
		{
			continue;
		}
		cout << "Codigo de vuelo: " << vuelos_solicitados[i].CodigoVueloSolicitado;
		cout << " - Cantidad de pasajes: " << vuelos_solicitados[i].CantSolicitado;
		cout << " - DNI: " << vuelos_solicitados[i].Dni;
		cout << " - Nombre y Apellido: " << vuelos_solicitados[i].NomApe << endl;

		pos = busquedaBinaria(vuelos, vuelos_solicitados[i].CodigoVueloSolicitado, CantVuelos);
		if (vuelos[pos].CantDisponible >= vuelos_solicitados[i].CantSolicitado)
		{
			vuelos[pos].CantDisponible -= vuelos_solicitados[i].CantSolicitado;
		}
		else
		{
			NoVendidos[pos] = vuelos_solicitados[i].CantSolicitado;
		}

	}
	cout << endl << "VUELOS" << endl;
	for (int i = 0; i < CantVuelos; i++)
	{
		cout << "Codigo de vuelo: " << vuelos[i].CodigoVuelo;
		cout << " - Pasajes libres: " << vuelos[i].CantDisponible;
		cout << " - Pasajes no vendidos: " << NoVendidos[i] << endl;
	}

	fclose(f);
	fclose(f1);
}

void ordenarVector(VUELO vec[], int N) {
	VUELO aux;
	for (int i = 0; i < N; i++) {
		for (int a = 0; a < (N - 1); a++) {
			if (vec[a].CodigoVuelo > vec[a + 1].CodigoVuelo) {
				aux = vec[a];
				vec[a] = vec[a + 1];
				vec[a + 1] = aux;
			}
		}
	}
}

int busquedaBinaria(VUELO v[], int buscado, int N) 
{
	int primero = 0, medio, ultimo = N - 1;
	while (primero <= ultimo) {
		medio = (primero + ultimo) / 2;
		if (v[medio].CodigoVuelo == buscado) {
			return medio;
		}
		if (buscado > v[medio].CodigoVuelo) {
			primero = medio + 1;
		}
		else
		{
			ultimo = medio - 1;
		}
	};
	return -1;
}