#include <iostream>
using namespace std;

int main()
{
	int vector[10] = { 5, 3, 9, 13 , 85, 32, 23, 3, 15, 0 };
	int posiciones[10] = { -1 };
	int longitud = sizeof(vector) / sizeof(*vector);
	int menor = 0;
	int posUtilizadas = 1;
	for (int i = 0; i < longitud && vector[i] != 0; i++)
	{
		cout << vector[i] << ", ";
		if (i == 0 || vector[i] < menor)
		{
			menor = vector[i];
			posiciones[0] = i + 1;
			posUtilizadas = 1;
		}
		else if (vector[i] == menor)
		{
			posiciones[posUtilizadas] = i + 1;
			posUtilizadas++;
		}
	}
	cout << endl;

	cout << "El menor numero del conjunto es: " << menor << endl;
	if (posUtilizadas > 1)
	{
		cout << "Las posiciones en las que se encuentra el menor son: ";
		for (int i = 0; i < posUtilizadas; i++)
		{
			cout << posiciones[i];
			if (i < posUtilizadas - 1)
			{
				cout << ", ";
			}
		}
	}
	else
	{
		cout << "La posicion en la que se encuentra es: " << posiciones[0];
	}
}