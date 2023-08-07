#include <iostream>
#include <cstring>
using namespace std;

int *OrdenAscendente(int[], int);
int *OrdenDescendente(int[], int);

int main() 
{
	const int tope = 5;
	int vec[tope] = {34,-20,10,-49,8};
	cout << "Vector inicial: ";
	for (int i = 0; i < tope; i++)
	{
		cout << vec[i];
		if (i < tope-1)
		{
			cout << ", ";
		}
		else
		{
			cout << endl;
		}
	}

	cout << "Vector ordenado ascendentemente: ";
	int *vec2 = OrdenAscendente(vec, tope);
	for (int i = 0; i < tope; i++)
	{
		cout << vec2[i];
		if (i < tope - 1)
		{
			cout << ", ";
		}
		else
		{
			cout << endl;
		}
	}

	cout << "Vector ordenado descendentemente: ";
	int* vec3 = OrdenDescendente(vec, tope);
	for (int i = 0; i < tope; i++)
	{
		cout << vec3[i];
		if (i < tope - 1)
		{
			cout << ", ";
		}
		else
		{
			cout << endl;
		}
	}
}

int *OrdenAscendente(int vec[], int tope) 
{
	int aux, pos = 4;
	for (int i = 0; i < tope; i++)
	{
		for (int i = 0; i < pos; i++)
		{
			if (vec[i+1] < vec[i])
			{
				aux = vec[i];
				vec[i] = vec[i + 1];
				vec[i + 1] = aux;
			}
		}
		pos--;
	}

	return vec;
}

int *OrdenDescendente(int vec[], int tope)
{
	int aux, pos = 4;
	for (int i = 0; i < tope; i++)
	{
		for (int i = 0; i < pos; i++)
		{
			if (vec[i + 1] > vec[i])
			{
				aux = vec[i];
				vec[i] = vec[i + 1];
				vec[i + 1] = aux;
			}
		}
		pos--;
	}

	return vec;
}