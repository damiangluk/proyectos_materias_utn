#include <iostream>
using namespace std;

int main()
{
	int Negativos[30], Positivos[30], N, num, CantNegativos = 0, CantPositivos = 0;

	do
	{
		cout << "Ingrese la cantidad de valores que desea ingresar (< 30): ";
		cin >> N;
	} while (N >= 30 || N < 0);


	for (int i = 0; i < N; i++)
	{
		cout << "Ingrese un valor: ";
		cin >> num;

		if (num < 0)
		{
			Negativos[CantNegativos] = num;
			CantNegativos++;
		}
		else
		{
			Positivos[CantPositivos] = num;
			CantPositivos++;
		}
	}
	if (num < 10)
	{
		cout << "Los elementos negativos son: ";
		for (int i = 0; i < CantNegativos; i++)
		{
			cout << Negativos[i] << " ";
		}
	}
	else
	{
		cout << "Los elementos positivos son: ";
		for (int i = 0; i < CantPositivos; i++)
		{
			cout << Positivos[i] << " ";
		}
	}

}