#include <iostream> 
using namespace std;

void main6()
{
	FILE* f;
	errno_t pfile = fopen_s(&f, "EJERCICIO6.DAT", "wb+");

	struct PRECIOS {
		char Descripcion[19];
		int NumeroArticulo, Precio, CantStock, Proveedor;
	};

	for (int i = 0; i < 10; i++)
	{
		PRECIOS precio;
		cout << endl << "Ingrese el numero de articulo: ";
		cin >> precio.NumeroArticulo;
		if (precio.NumeroArticulo <= 0)
		{
			break;
		}

		do
		{
			cout << "Ingrese la descripcion del archivo: ";
			cin >> precio.Descripcion;
			cout << "Ingrese el Precio del articulo: ";
			cin >> precio.Precio;
			cout << "Ingrese la cantidad de stock: ";
			cin >> precio.CantStock;
			cout << "Ingrese el numero de proveedor: ";
			cin >> precio.Proveedor;

		} while (precio.NumeroArticulo > 99999 || strlen(precio.Descripcion) > 19 || precio.CantStock < 0 || precio.Proveedor < 0 || precio.Proveedor > 9999);

		fwrite(&precio, sizeof(PRECIOS), 1, f);
	}
	fclose(f);
}

