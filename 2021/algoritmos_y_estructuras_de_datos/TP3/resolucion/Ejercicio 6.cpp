#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int codigoDeportes[20] = { 0 };
	int contadorDeportes[20] = { 0 };
	int i = 0, posLibre = 0,posEncontrado;
	while (i < 20)
	{
		int socio, deporte = -1, posEncontrado = -1;
		cout << "Ingrese su numero de socio: ";
		cin >> socio;
		if (socio == 0)
		{
			break;
		}
		while (deporte < 0)
		{
			cout << "Ingrese su codigo de deporte: ";
			cin >> deporte;
		}

		for (int i = 0; i < posLibre; i++)
		{
			if (codigoDeportes[i] == deporte)
			{
				posEncontrado = i;
			}
		}

		if (posLibre < 19)
		{
			if (posEncontrado != -1)
			{
				contadorDeportes[posEncontrado]++;
			}
			else
			{
				codigoDeportes[posLibre] = deporte;
				contadorDeportes[posLibre]++;
				posLibre++;
			}
		}
	}

	cout << endl;
	for (int i = 0; i <= posLibre; i++)
	{
		if (codigoDeportes[i] != 0)
		{
			cout << "Se inscribieron " << contadorDeportes[i] << " personas al deporte " << codigoDeportes[i] << endl;
		}
	}
}