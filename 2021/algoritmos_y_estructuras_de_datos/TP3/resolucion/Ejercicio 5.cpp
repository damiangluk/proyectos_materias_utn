#include <iostream>
#include <cstring>
using namespace std;

void ingresarValores(int[]);
int main() {
	int Contadores[11] = { 0,0,0,0,0,0,0,0,0,0,0};
	ingresarValores(Contadores);
	for (int i = 2; i < 13; i++)
	{
		cout << "El " << i << " Salio " << Contadores[i - 2] << " veces" << endl;
	}

}

void ingresarValores(int vectorValoresDeDados[]) {
	for (int i = 0; i < 4; i++)
	{
		int Dado1 = 0, Dado2 = 0, suma;
		while (Dado1 < 1 || Dado1 >6) {
			cout << "Ingresar el valor del primer dado" << endl;
			cin >> Dado1;
		} 
		while (Dado2 < 1 || Dado2 > 6) {
			cout << "Ingresar el valor del segundo dado" << endl;
			cin >> Dado2;
		}

		suma = Dado1 + Dado2;
		vectorValoresDeDados[suma - 2]++;
	}
}