#include <iostream>
using namespace std;

int ingresoNumero();
int ingresoNumeroDeRepeticion();
void ingresoSegunLote(int, int&, int&, int&, int&, char);
void procesarNumero(int, int&, int&, int&, int&);
void mostrarResultados(int, int, int, int);

void main() {
	int CantNumeros, valoresCero = 0, acumValoresPos = 0, contValoresPos = 0, promedioValoresPos, sumValoresNeg = 0;
	char lote;
	do {
		cout << "Ingresar la letra del ejercicio que desea realizar" <<endl
			 <<"a: Ingresar 10 numeros" <<endl
			 <<"b: Ingresar N numeros" << endl
			 <<"c: Ingresar numeros hasta ingresar 2 iguales" << endl
			 <<"d: Ingresar numeros hasta N o ingresar 5 ceros" << endl
			 <<"e: Ingresar numeros hasta N o ingresar 5 ceros o promedio mayor a 6" << endl;
		cin >> lote;
	} while (lote != 'a' && lote != 'b' && lote != 'c' && lote != 'd' && lote != 'e');

	if (lote == 'a') {
		CantNumeros = 10;
	}
	else if (lote == 'b') {
		CantNumeros = ingresoNumeroDeRepeticion();
	}
	else if (lote == 'c') {
		CantNumeros = -1;
	}
	else if (lote == 'd') {
		CantNumeros = ingresoNumeroDeRepeticion();
	}
	else if (lote == 'e') {
		CantNumeros = ingresoNumeroDeRepeticion();
	}
	ingresoSegunLote(CantNumeros, valoresCero, acumValoresPos, contValoresPos, sumValoresNeg, lote);
	mostrarResultados(valoresCero, acumValoresPos, contValoresPos, sumValoresNeg);
}

int ingresoNumero() {
	int num;
	cout << "Ingresar un numero: ";
	cin >> num;
	return num;
}

int ingresoNumeroDeRepeticion() {
	int num;
	cout << "Cuantos valores desea a ingresar?: ";
	cin >> num;
	//system("cls");
	return num;
}

void mostrarResultados(int valoresCero, int acumValoresPos, int contValoresPos, int sumValoresNeg)
{
	cout << "La cantidad de valores ingresados iguales a cero es " << valoresCero << endl;
	if (contValoresPos != 0) {
		cout << "El promedio de valores positivos es " << acumValoresPos / contValoresPos << endl;
	}
	else {
		cout << "No se ingresaron valores positivos" << endl;
	}
	cout << "La sumatoria de valores negativos ingresados es " << sumValoresNeg << endl;
}

void procesarNumero(int num, int& valoresCero, int& acumValoresPos, int& contValoresPos, int& sumValoresNeg)
{
	if (num == 0) {
		valoresCero++;
	}
	else if (num > 0) {
		acumValoresPos += num;
		contValoresPos++;
	}
	else {
		sumValoresNeg += num;
	}
}

void ingresoSegunLote(int cantNumeros, int& valoresCero, int& acumValoresPos, int& contValoresPos, int& sumValoresNeg, char lote) {
	if (lote == 'a' || lote == 'b') {
		for (int i = 0; i < cantNumeros; i++)
		{
			int numero;
			numero = ingresoNumero();
			procesarNumero(numero, valoresCero, acumValoresPos, contValoresPos, sumValoresNeg);
			system("cls");
		}
	}
	else if (lote == 'd') {
		int i = 0;
		while (i < cantNumeros && valoresCero <= 4) {
			int numero;
			numero = ingresoNumero();
			procesarNumero(numero, valoresCero, acumValoresPos, contValoresPos, sumValoresNeg);
			i++;
			system("cls");
		}
	}
	else if (lote == 'e') {
		int i = 0, prom = 1;
		while (i < cantNumeros && valoresCero <= 4 && prom < 6) {
			int numero;
			numero = ingresoNumero();
			procesarNumero(numero, valoresCero, acumValoresPos, contValoresPos, sumValoresNeg);
			if (contValoresPos != 0) {
				prom = acumValoresPos / contValoresPos;
			}
			else {
				prom = 1;
			}
			i++;
			//system("cls");
		}
	}
	else if (lote == 'c') {
		int num, aux;
		num = ingresoNumero();
		aux = num - 1;
		while (num != aux) {
			procesarNumero(num, valoresCero, acumValoresPos, contValoresPos, sumValoresNeg);
			aux = num;
			//system("cls");
			num = ingresoNumero();
		}
	}
}
