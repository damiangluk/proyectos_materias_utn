#include <iostream>
using namespace std;

void main()
{
	int edad;

	cout << "Ingrese su edad: ";
	cin >> edad;
	if (edad < 0)
	{
		cout << "No puedes tener menos de 0 anios :(";
	}
	else if (edad <= 12)
	{
		cout << "sos menor";
	}
	else if (edad > 12 && edad <= 18)
	{
		cout << "Sos cadete";
	}
	else if (edad > 18 && edad <= 26)
	{
		cout << "Sos juvenil";
	}
	else
	{
		cout << "Sos mayor";
	}
}