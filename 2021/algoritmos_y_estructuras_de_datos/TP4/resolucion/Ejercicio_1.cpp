#include <iostream>
using namespace std;

void main1()
{
	FILE* f;
	errno_t pFile;

	struct Alumnos { int Legajo, Promedio; };

	Alumnos alumnos[10];
	int Nota1, Nota2;
	for (int i = 0; i < 10; i++)
	{
		cout << "Ingrese su Legajo: ";
		cin >> alumnos[i].Legajo;
		if (alumnos[i].Legajo < 0)
		{
			break;
		}
		cout << "Ingrese su primer Nota: ";
		cin >> Nota1;
		cout << "Ingrese su segunda Nota: ";
		cin >> Nota2;
		alumnos[i].Promedio = ((Nota1 + Nota2) / 2);
	}

	pFile = fopen_s(&f, "EJERCICIO1.BIN", "wb");
	for (int i = 0; i < 10; i++)
	{
		if (!(alumnos[i].Legajo < 0))
		{
			fwrite(&alumnos[i], sizeof(Alumnos), 1, f);
			continue;
		}
		break;
	}
	fclose(f);
}