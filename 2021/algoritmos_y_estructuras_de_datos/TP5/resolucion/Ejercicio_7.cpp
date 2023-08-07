#include<iostream>
using namespace std;

bool EsInversible(char[50 + 1]);

void main7()
{
	char Cadena1[24 + 1], Cadena2[24 + 1];
	cout << "Ingrese la primer cadena: ";
	cin >> Cadena1;
	cout << "Ingrese la segunda cadena: ";
	cin >> Cadena2;
	strcat_s(Cadena1, ".");
	strcat_s(Cadena1, Cadena2);
	if (EsInversible(Cadena1))
	{
		cout << "La cadena es inversible";
	}
	else
	{
		cout << "La cadena no es inversible";
	}
}

bool EsInversible(char cadena[50 + 1])
{
	int CantIzq = 0;
	int CantDer = 0;
	for (int i = 0; i < strlen(cadena); i++)
	{
		if (cadena[i] != '.')
		{
			CantDer++;
		}
		else
		{
			CantIzq = CantDer;
			CantDer = 0;
			continue;
		}
	}
	if (CantIzq != CantDer)
	{
		return false;
	}
	int a = strlen(cadena) - 1;
	for (int i = 0; i < CantIzq; i++)
	{
		if (cadena[i] != cadena[a])
		{
			return false;
		}
		a--;
	}
}