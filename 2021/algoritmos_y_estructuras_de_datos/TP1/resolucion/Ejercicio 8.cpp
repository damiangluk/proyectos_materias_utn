#include <iostream>
using namespace std;

void main()
{
	int acum10 = 0, acum100 = 0, numero, cant100 = 0;
	//ingreso 10 numeros
	for (int i = 0; i < 10; i++)
	{
		cout << "Ingrese un numero: ";
		cin >> numero;
		if (numero > 100)
		{
			acum100 = acum100 + numero;
			cant100++;
		}
		else if(numero < -10)
		{
			acum10 += numero;
		}
	}
	int promedio = cant100 == 0 ? 0 : acum100 / cant100;
	cout << "El promedio de los mayores a 100 es: " << promedio << endl;
	cout << "La suma de los menores a -10 es: " << acum10;
}