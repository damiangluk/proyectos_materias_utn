#include <iostream>
using namespace std;
void main() {

	int acum[3] = { 0,0,0 }, cont = 0;

	for (int i = 0; i < 5; i++)
	{
		int infra, valor;
		char mot[40+1], grav;
		cout << "Ingresar tipo de infraccion (1 a 4): ";
		cin >> infra;

		cout << "Ingresar motivo de la infraccion: ";
		cin >> mot;

		cout << "Ingresar valor de la multa: ";
		cin >> valor;

		cout << "Ingresar gravedad de la infraccion (L, M, G): ";
		cin >> grav;

		if (grav == 'L' || grav == 'l') {
			acum[0] += valor;
		}
		else if (grav == 'M' || grav == 'm')
		{
			acum[1] += valor;
		}
		else if (grav == 'G' || grav == 'g')
		{
			acum[2] += valor;
			if (infra == 3 || infra == 4)
			{
				cont++;
			}
		}
	}

	cout << "Valores totales de la multa a pagar de acuerdo al tipo de gravedad: " << endl;
	cout << "L: " << acum[0] << endl;
	cout << "M: " << acum[1] << endl;
	cout << "G: " << acum[2] << endl;

	if (cont > 3)
	{
		cout << "Clausurar fabrica" << endl;
	}
}