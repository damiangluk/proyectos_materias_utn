#include <iostream>
using namespace std;

int main()
{
	struct persona { string nombre; int fecha; };
	persona personas[10] = { {"Damian", 20030508},{"Lucas",20030509}, {"Martin", 20020303}, {"Rodrigo", 20030508}, {"Martin",19970715}, {"Julieta", 20020718}, {"Lisandro", 20000920}, {"Gian", 19950515}, {"Gabriela", 19900910}, {"Mariela",20101110} };
	int num = 11;
	while (num >= 10 || num <0)
	{
		cout << "Ingrese un numero mayor a 0 y menor a 10: ";
		cin >> num;
		cout << endl;
	}

	//primer orden
	persona aux;
	int pos = num -1;
	for (int a = 0; a < num; a++)
	{
		for (int i = 0; i < pos; i++)
		{
			if (personas[i + 1].nombre < personas[i].nombre)
			{
				aux = personas[i];
				personas[i] = personas[i + 1];
				personas[i + 1] = aux;
			}
		}
		pos--;
	}

	cout << "Las personas ordenadas por nombre ascendente son: " << endl;
	for (int i = 0; i < num; i++)
	{
		cout << "Nombre: " << personas[i].nombre << ", Fecha de nacimiento: " << personas[i].fecha << endl;
	}

	cout << endl;

	//segundo orden
	pos = num - 1;
	for (int a = 0; a < num; a++)
	{
		for (int i = 0; i < pos; i++)
		{
			if (personas[i + 1].fecha < personas[i].fecha)
			{
				aux = personas[i];
				personas[i] = personas[i + 1];
				personas[i + 1] = aux;
			}
			else if (personas[i + 1].fecha == personas[i].fecha)
			{
				if (personas[i + 1].nombre < personas[i].nombre)
				{
					aux = personas[i];
					personas[i] = personas[i + 1];
					personas[i + 1] = aux;
				}
			}
		}
		pos--;
	}

	cout << "Las personas ordenadas por fecha y nombre ascendente son: " << endl;
	for (int i = 0; i < num; i++)
	{
		cout << "Nombre: " << personas[i].nombre << ", Fecha de nacimiento: " << personas[i].fecha << endl;
	}

	cout << endl;

	//tercer orden
	pos = num - 1;
	for (int a = 0; a < num; a++)
	{
		for (int i = 0; i < pos; i++)
		{
			if (personas[i + 1].nombre < personas[i].nombre)
			{
				aux = personas[i];
				personas[i] = personas[i + 1];
				personas[i + 1] = aux;
			}
			else if (personas[i + 1].nombre == personas[i].nombre)
			{
				if (personas[i + 1].fecha < personas[i].fecha)
				{
					aux = personas[i];
					personas[i] = personas[i + 1];
					personas[i + 1] = aux;
				}
			}
		}
		pos--;
	}

	cout << "Las personas ordenadas por nombre y fecha ascendente son: " << endl;
	for (int i = 0; i < num; i++)
	{
		cout << "Nombre: " << personas[i].nombre << ", Fecha de nacimiento: " << personas[i].fecha << endl;
	}
}