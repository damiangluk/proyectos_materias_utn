#include <iostream>
#include<string.h>
using namespace std;

struct PRECIOS {
	char Descripcion[19];
	int NumeroArticulo, Precio, CantStock, Proveedor;
};

void ordenar(PRECIOS[], int, int);

void main7()
{
	FILE* f;
	errno_t pFile = fopen_s(&f, "EJERCICIO6.DAT", "rb");

	PRECIOS precios[10];
	int i = 0;

	if (pFile == 0)
	{
		fread(&precios[0], sizeof(PRECIOS), 1, f);
		while (!feof(f) && i < 10)
		{
			i++;
			fread(&precios[i], sizeof(PRECIOS), 1, f);
		}

		int ordenamiento = -1;
		while (ordenamiento < 0 || ordenamiento > 4)
		{
			cout << "Como desea ordenar el archivo?" << endl;
			cout << "0. Sin orden" << endl;
			cout << "1. Articulo creciente" << endl;
			cout << "2. Descripcion creciente" << endl;
			cout << "3. Proveedor creciente y Articulo creciente" << endl;
			cout << "4. Proveedor creciente y Articulo decreciente." << endl << endl;
			cin >> ordenamiento;
			cout << endl;
		}

		if (ordenamiento != 0)
		{
			ordenar(precios, i, ordenamiento);
		}

		for (int a = 0; a < i; a++)
		{
			cout << "Nro articulo: " << precios[a].NumeroArticulo;
			cout << ", Descripcion: " << precios[a].Descripcion;
			cout << ", Precio: " << precios[a].Precio;
			cout << ", Stock: " << precios[a].CantStock;
			cout << ", Proveedor: " << precios[a].Proveedor << endl;
		}
	}
	else
	{
		cout << "No se encontro el archivo";
	}
	
}



void ordenar(PRECIOS precios[], int i, int ordenamiento) 
{
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < (i - 1); b++)
		{
			if (ordenamiento == 1)
			{
				if (precios[b].NumeroArticulo > precios[b + 1].NumeroArticulo)
				{
					PRECIOS aux = precios[b];
					precios[b] = precios[b + 1];
					precios[b + 1] = aux;
				}
			}
			else if (ordenamiento == 2)
			{
				if (strcmp(precios[b].Descripcion, precios[b + 1].Descripcion) > 0)
				{
					PRECIOS aux = precios[b];
					precios[b] = precios[b + 1];
					precios[b + 1] = aux;
				}
			}
			else if (ordenamiento == 3)
			{
				if (precios[b].Proveedor > precios[b + 1].Proveedor || (precios[b].Proveedor == precios[b + 1].Proveedor && precios[b].NumeroArticulo > precios[b + 1].NumeroArticulo))
				{
					PRECIOS aux = precios[b];
					precios[b] = precios[b + 1];
					precios[b + 1] = aux;
				}
			}
			else if (precios[b].Proveedor > precios[b + 1].Proveedor || (precios[b].Proveedor == precios[b + 1].Proveedor && precios[b].NumeroArticulo < precios[b + 1].NumeroArticulo))
			{
					PRECIOS aux = precios[b];
					precios[b] = precios[b + 1];
					precios[b + 1] = aux;
			}
		}
	}
}