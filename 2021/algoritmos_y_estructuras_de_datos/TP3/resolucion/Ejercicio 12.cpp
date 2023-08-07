#include <iostream>
#include <cstring>
using namespace std;

struct FechaDeNacimiento { int Dia; int Mes; int Anio; };
struct EstructuraVector1 { string Nombre; FechaDeNacimiento Fecha; };
struct ApellidoNombre { string Apellido; string Nombre; };
struct Calificaciones { int Nota1; int Nota2; int Nota3; };
struct EstructuraVector2 { int Legajo; ApellidoNombre ApellidoNombre; Calificaciones Notas; };

void BusquedaSecuencialPorApellido(string, EstructuraVector2[]);
int BusquedaBinariaPorLegajo(EstructuraVector2[], int);

int main()
{
	EstructuraVector1 Vector1[6] = { {"Damian",{8, 5,2003}}, {"Julian",{21, 2,2005}}, {"Alberto",{35, 10,2010}}, {"Alan",{16, 6,2004}}, {"Roberto",{3, 9,1985}}, {"Dylan",{8, 4,2006}} };
	EstructuraVector2 Vector2[6] = { {187364, {"Gluk","Damian"}, {6,4,7}}, {192837, {"Rodriguez","Lucas"}, {5,2,4}} , {284734, {"Benitez","Samuel"}, {6,8,6}} , {358473, {"Diaz","Ramiro"}, {8,8,3}} , {456789, {"Britos","Gonzalo"}, {10,8,9}} , {584736, {"Tinelli","Marcelo"}, {10,3,7}} };

	cout << "El campo dia de la posicion 4 del primer vector es: " << Vector1[4].Fecha.Dia << endl;
	cout << "El campo nommbre de la posicion 0 del primer vector es: " << Vector1[0].Nombre << endl << endl;

	for (int i = 0; i < 6; i++)
	{
		if (Vector2[i].Legajo == 456789)
		{
			cout << "La posicion en la que se encontro el legajo 456789 es: " << i + 1 << endl << endl;
			break;
		}
	}

	string apellido;
	cout << "Indique el apellido de la persona que desea encontrar: ";
	cin >> apellido;
	BusquedaSecuencialPorApellido(apellido, Vector2);
	int pos = BusquedaBinariaPorLegajo(Vector2, 5);
	if (pos != -1)
	{
		cout << "El legajo 456789 se encontro en la posicion " << pos << endl;
	}
	else
	{
		cout << "No se encontro el legajo 456789" << endl;
	}
}

void BusquedaSecuencialPorApellido(string Apellido, EstructuraVector2 Vector[])
{
	for (int i = 0; i < 6; i++)
	{
		if (Vector[i].ApellidoNombre.Apellido == Apellido)
		{
			cout << "La posicion en la que se encontro el apellido " << Apellido << " es: " << i + 1 << endl;
			cout << "Legajo: " << Vector[i].Legajo << endl;
			cout << "Nombre: " << Vector[i].ApellidoNombre.Nombre << endl;
			cout << "Calificaciones: Nota 1: " << Vector[i].Notas.Nota1 << ", Nota 2: " << Vector[i].Notas.Nota2 << ", Nota 3: " << Vector[i].Notas.Nota3 << endl << endl;
			break;
		}
		else if(i == 5)
		{
			cout << "No se encontro el apellido: " << Apellido << endl << endl;
		}
	}
}

int BusquedaBinariaPorLegajo(EstructuraVector2 Vector[], int ultimo)
{
	int medio, primero = 0;
	while (primero <= ultimo)
	{
		medio = (primero + ultimo) / 2;
		if (Vector[medio].Legajo == 456789)
		{
			return (medio + 1);
		}
		else if(456789 > Vector[medio].Legajo)
		{
			primero = medio + 1;
		}
		else
		{
			ultimo = medio - 1;
		}
	}
	return -1;
}