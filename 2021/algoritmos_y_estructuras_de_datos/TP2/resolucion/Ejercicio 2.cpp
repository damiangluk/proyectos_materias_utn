#include <iostream>
#include <string>
using namespace std;

string Tendencia(int, int);
void main() {
	int A, B;
	cout << "Ingrese un numero: ";
	cin >> A;
	cout << "Ingrese un numero: ";
	cin >> B;
	cout << Tendencia(A, B);
}

string Tendencia(int A, int B)
{
	if ((B - A) < 0)
	{
		return "Decreciente";
	}
	else if ((B - A) < (2 * A / 100))
	{
		return "Estable";
	}
	else if((B-A) < (5*A/100))
	{
		return "Leve ascenso";
	}
	else
	{
		return "En ascenso";
	}
}