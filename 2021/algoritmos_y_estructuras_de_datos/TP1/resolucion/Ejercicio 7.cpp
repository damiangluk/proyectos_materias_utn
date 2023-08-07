#include <iostream>
#include <cstring>
using namespace std;

void main()
{
	char nombre[10 + 1],nombremin[10 + 1];
	int segundos, minutos, minutosmin, segundosmin;

	cout << "Ingrese su nombre: ";
	cin >> nombremin;
	cout << "Ingrese los minutos que tardo en recorrer la carrera: ";
	cin >> minutosmin;
	cout << "Ingrese los segundos que tardo en recorrer la carrera (menos de 60): ";
	cin >> segundosmin;

	while (strncmp(nombre,"Z",2) != 0)
	{
		cout << "Ingrese su nombre o ingrese 'Z' si desea ver los resultados: ";
		cin >> nombre;
		if (strncmp(nombre, "Z", 2) != 0)
		{
			cout << "Ingrese los minutos que tardo en recorrer la carrera: ";
			cin >> minutos;
			cout << "Ingrese los segundos que tardo en recorrer la carrera (menos de 60): ";
			cin >> segundos;

			if (minutos < minutosmin || (minutos == minutosmin && segundos < segundosmin))
			{
				minutosmin = minutos;
				segundosmin = segundos;
				strcpy_s(nombremin, nombre);
			}
		}
		
	}
	float velocidadmax = segundosmin + minutosmin * 60;
	cout << "El participante mas veloz fue " << nombremin << ", con una velocidad de " << 1500/velocidadmax <<" metros por segundo";
}