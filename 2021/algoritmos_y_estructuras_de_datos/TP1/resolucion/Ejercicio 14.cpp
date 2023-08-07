#include <iostream>
#include <cstring>
using namespace std;

void main() {
	int Id, Peso, Puerto;
	int PesoTotal = 0,MayorPeso,MayorId,Cant1 = 0,Cant2 = 0, Cant3 = 0;
	for (int i = 0; i < 5; i++)
	{
		cout << "Ingresar identificacion del contenedor: ";
		cin >> Id;
		cout << "Ingresar peso del contenedor: ";
		cin >> Peso;
		cout << "Ingresar puerto de arribo (1 a 3): ";
		cin >> Puerto;

		PesoTotal += Peso;
		if (i == 0 || Peso > MayorPeso)
		{
			MayorPeso = Peso;
			MayorId = Id;
		}
		if (Puerto == 1)
		{
			Cant1++;
		}
		else if(Puerto == 2)
		{
			Cant2++;
		}
		else if (Puerto == 3)
		{
			Cant3++;
		}
	}

	cout << "El peso total que el buque debe trasladar es:" << PesoTotal << endl;
	cout << "La identificacion del contenedor de mayor peso es:" << MayorId << endl;
	cout << "La cantidad de contenedores que fueron al puerto 1 son: " << Cant1 << ", al puerto 2 fueron: " << Cant2 << " y al puerto 3 fueron: " << Cant3 << endl;
}