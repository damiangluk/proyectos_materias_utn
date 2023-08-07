#include <iostream>
using namespace std;

void main()
{
	int saldo1 = 0, saldo2 = 0, saldo3 = 0, saldo4 = 0;
	float sueldos = -1;
	while (sueldos != 0)
	{
		cout << "Ingrese su sueldo (0 si desea ver los resultados): ";
		cin >> sueldos;
		if (sueldos > 0)
		{
			if (sueldos < 1520)
			{
				saldo1++;
			}
			else if (sueldos < 2780)
			{
				saldo2++;
			}
			else if (sueldos < 5999)
			{
				saldo3++;
			}
			else
			{
				saldo4++;
			}
		}
		else if(sueldos < 0)
		{
			cout << "No puedes recibir un sueldo menor a 0 pesos: ";
		}
	};

	cout << saldo1 << " empleado/s reciben un sueldo menor a $1.520" << endl;
	cout << saldo2 << " empleado/s reciben un sueldo mayor o igual a $1.520 y menor a $2.780" << endl;
	cout << saldo3 << " empleado/s reciben un sueldo mayor o igual a $2.780 y menor a $5.999" << endl;
	cout << saldo4 << " empleado/s reciben un sueldo mayor o igual $5.999" << endl;
}