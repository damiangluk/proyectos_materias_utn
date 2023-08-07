#include <iostream>
using namespace std;

int main()
{
	int cantCursos;
	do
	{
		cout << "Ingrese la cantidad de cursos (< 20): ";
		cin >> cantCursos;
	} while (cantCursos >= 20 || cantCursos < 1);


	for (int i = 0; i < cantCursos; i++)
	{
		int cantAlum, Legajo, nota, Aprobados = 0, Desaprobados = 0;
		string codigo;
		int Contadores[11] = { 0 };
		do
		{
			cout << "Ingrese el codigo del curso: ";
			cin >> codigo;

		} while (std::string(codigo).size() < 4 || std::string(codigo).size() > 4);

		cout << "Ingrese la cantidad de alumnos del curso " << codigo << ": ";
		cin >> cantAlum;

		for (int i = 0; i < cantAlum; i++)
		{
			cout << "Ingrese el legajo del alumno: ";
			cin >> Legajo;

			do
			{
				cout << "Ingrese la nota del alumno: ";
				cin >> nota;
			} while (nota > 10 || nota < 0);

			nota >= 6 ? Aprobados++ : Desaprobados++;
			Contadores[nota]++;
		}
		for (int i = 0; i <= 10; i++)
		{
			cout << Contadores[i] << " alumnos tuvieron un " << i << " como nota" << endl;
		}
		cout << "El codigo del curso es:" << codigo << endl;
		cout << "Hubo un " << (Aprobados * 100) / cantAlum << "% de alumnos aprobados" << endl;
		cout << "Hubo un " << (Desaprobados * 100) / cantAlum << "% de alumnos desaprobados" << endl;
	}
}