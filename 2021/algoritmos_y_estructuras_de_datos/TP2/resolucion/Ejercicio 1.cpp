#include <iostream>
using namespace std;

float CalcularPorcentajeDiferencia(int, int);
void main() {
	int A, B;
	cout << "Ingrese un numero: ";
	cin >> A;
	cout << "Ingrese un numero: ";
	cin >> B;
	cout << CalcularPorcentajeDiferencia(A, B);
}

float CalcularPorcentajeDiferencia(int A, int B)
{
	return (B - A) * 100 / (A + B);
}