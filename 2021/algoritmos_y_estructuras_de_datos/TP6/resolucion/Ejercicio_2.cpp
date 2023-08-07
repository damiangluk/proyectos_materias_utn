#include <iostream>
using namespace std;

struct Nodo2 { int info; Nodo2* sig; };
Nodo2* insertarAlFinal(Nodo2*&, int);

void main() {

	int dato;
	Nodo2* listA = NULL;
	cout << "Ingrese un numero para la listA: ";
	cin >> dato;

	while (dato != 0) {
		insertarAlFinal(listA, dato);
		cout << "Ingrese un numero para la listA: ";
		cin >> dato;
	}

	Nodo2* listB = NULL;
	cout << "Ingrese un numero para la listB: ";
	cin >> dato;

	while (dato != 0) {
		insertarAlFinal(listB, dato);
		cout << "Ingrese un numero para la listB: ";
		cin >> dato;
	}
	Nodo2* listC = NULL;
	while (listA != NULL || listB != NULL)
	{
		if (listA != NULL)
		{
			insertarAlFinal(listC, listA->info);
			listA = listA->sig;
		}
		else
		{
			insertarAlFinal(listC, listB->info);
			listB = listB->sig;
		}
	}
	while (listC != NULL)
	{
		cout << listC->info << " ";
		listC = listC->sig;
	}

}

Nodo2* insertarAlFinal(Nodo2*& l, int x) {
	Nodo2* nuevo = new Nodo2();
	nuevo->info = x;
	nuevo->sig = NULL;

	if (l == NULL) {
		l = nuevo;
	}
	else {
		Nodo2* aux = l;
		while (aux->sig != NULL)
			aux = aux->sig;

		aux->sig = nuevo;
	}
	return nuevo;
}