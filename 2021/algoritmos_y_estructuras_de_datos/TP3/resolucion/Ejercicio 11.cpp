#include <iostream>
using namespace std;

int main()
{
	int Matriz[5][5] = { {1,-23,-3,9,73},{24,-38,1,-21,84},{9,-12,45,99,-21}, {-54,65,5,9,87}, {-2,66,5,25,44} };
	int num, suma = 0, filaMin = 0, MaxCol = 0;

	do
	{
		cout << "Ingrese un numero menor a 5: ";
		cin >> num;
	} while (num >5);

	cout << endl << "A." << endl;

	for (int i = 0; i < num; i++)
	{
		cout << "La fila " << i + 1 << " esta conformada por: ";
		for (int a = 0; a < num; a++)
		{
			cout << Matriz[i][a] << " ";
			suma = suma + Matriz[i][a];
		}
		cout << endl;
	}

	cout << endl << "B." << endl;

	for (int i = 0; i < num; i++)
	{
		cout << "La columna " << i + 1 << " esta conformada por: ";
		for (int a = 0; a < num; a++)
		{
			cout << Matriz[a][i] << " ";
		}
		cout << endl;
	}

	cout << endl << "C. ";

	cout << "La sumatoria de los elementos de la matriz es " << suma << " y su promedio es " << suma / (num * num) << endl;

	cout << endl << "D. ";
	int maximoFila = 0, maximoColumna = 0, maximo = 0;
	for (int i = 0; i < num; i++)
	{
		for (int a = 0; a < num; a++)
		{
			if (i == 0 && a == 0)
			{
				maximo = Matriz[i][a];
			}
			else if (Matriz[i][a] > maximo)
			{
				maximo = Matriz[i][a];
				maximoFila = i + 1;
				maximoColumna = a + 1;
			}
		}
	}
	cout << "El maximo elemento de la matriz es " << maximo << " y se encontro en la fila " << maximoFila << " y la columna " << maximoColumna << endl;

	cout << endl << "E." << endl;

	int minimosPorFila[5] = { 0 }, maximosPorColumna[5] = { 0 };
	for (int i = 0; i < num; i++)
	{
		for (int a = 0; a < num; a++)
		{
			if (a == 0)
			{
				minimosPorFila[i] = Matriz[i][0];
			}else if (Matriz[i][a] < minimosPorFila[i])
			{
				minimosPorFila[i] = Matriz[i][a];
			}
			if (i == 0)
			{
				maximosPorColumna[a] = Matriz[0][a];
			}else if (Matriz[i][a] > maximosPorColumna[a])
			{
				maximosPorColumna[a] = Matriz[i][a];
			}
		}
		cout << "En la fila " << i + 1 << " el elemento minimo es " << minimosPorFila[i] << endl;

	}
	cout << endl;
	for (int a = 0; a < num; a++)
	{
		if (maximosPorColumna[a] != 0) { cout << "En la columna " << a + 1 << " el elemento maximo es " << maximosPorColumna[a] << endl; }
	}

	cout << endl << "F." << endl;
	int contadorPositivos = 0, contadorNegativos = 0;;
	for (int i = 0; i < num; i++)
	{
		for (int a = 0; a < num; a++)
		{
			if (i == a && Matriz[i][a] > 0)
			{
				contadorPositivos++;
			}
			if (a == (num - (i + 1)) && Matriz[i][a] < 0)
			{
				contadorNegativos++;
			}
		}
	}
	cout << "En la diagonal principal hay " << contadorPositivos << " elementos positivos" << endl;
	cout << "En la diagonal secundaria hay " << contadorNegativos << " elementos negativos" << endl;

}