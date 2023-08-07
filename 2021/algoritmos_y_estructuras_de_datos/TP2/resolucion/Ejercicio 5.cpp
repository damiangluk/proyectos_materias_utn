#include <iostream>
#include <string>
#include<cstring>
#include <string>
using namespace std;

string CalcularCUIL(char[9], char);
void main() {
	char DNI[9];
	char Sexo ='H';
	cout << "Ingrese su DNI: ";
	cin >> DNI;
	while (Sexo != 'F' && Sexo != 'M')
	{
		cout << "Ingrese su sexo (M: Masculino, F: Femenino): ";
		cin >> Sexo;
	}
	cout << CalcularCUIL(DNI, Sexo);
}

string CalcularCUIL(char DNI[9], char Sexo)
{
	int Conjunto[8 + 1] = { 3, 2, 7, 6, 5, 4, 3, 2 };
	int Sumador = 0;
	string CUIL = "";
	for (int i = 0;i < 8; i++)
	{
		int Digito = DNI[i] - '0';
		Sumador += (Digito * Conjunto[i]);
	}

	Sexo == 'M'? Sumador += 10: Sumador += 38;
	string DNIstr = DNI;

	if (Sumador % 11 == 1)
	{
		CUIL += "23-" + DNIstr;
		if (Sexo == 'M')
		{
			CUIL += "-9";
		}
		else
		{
			CUIL += "-4";
		}
	}
	else
	{
		CUIL += "20-" + DNIstr;
		if (Sexo == 'F')
		{
			CUIL += "-27";
		}
		else if(Sumador % 11 == 0)
		{
			CUIL += "-0";
		}
		else
		{
			string sufijo = std::to_string(11 - (Sumador % 11));
			CUIL += "-"+sufijo;
		}
	}

	return CUIL;
}