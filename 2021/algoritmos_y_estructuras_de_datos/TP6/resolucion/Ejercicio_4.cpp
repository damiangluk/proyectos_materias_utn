#include <iostream>
using namespace std;

struct Nodo4 {
	int Legajo;
	Nodo4* Siguiente;
};

Nodo4* insertarAlFinal(Nodo4*&, int);

void main() {
	int datoAnterior = 0, dato;
	Nodo4* lista1 = NULL;
	cout << "Ingrese un numero para la lista1: ";
	cin >> dato;

	while (dato != 0 && dato >= datoAnterior) {
		insertarAlFinal(lista1, dato);
		datoAnterior = dato;
		cout << "Ingrese un numero para la lista1: ";
		cin >> dato;
	}

	datoAnterior = 0;
	Nodo4* lista2 = NULL;
	cout << "Ingrese un numero para la lista2: ";
	cin >> dato;

	while (dato != 0 && dato >= datoAnterior) {
		insertarAlFinal(lista2, dato);
		datoAnterior = dato;
		cout << "Ingrese un numero para la lista2: ";
		cin >> dato;
	}

	Nodo4* lista3 = NULL;
	while (lista1 != NULL && lista2 != NULL)
	{
		if (lista1->Legajo < lista2->Legajo)
		{
			insertarAlFinal(lista3, lista1->Legajo);
			lista1 = lista1->Siguiente;
		}
		else
		{
			insertarAlFinal(lista3, lista2->Legajo);
			lista2 = lista2->Siguiente;
		}
	}
	while (lista1 != NULL) {
		insertarAlFinal(lista3, lista1->Legajo);
		lista1 = lista1->Siguiente;
	}
	while (lista2 != NULL) {
		insertarAlFinal(lista3, lista2->Legajo);
		lista2 = lista2->Siguiente;
	}

	while (lista3 != NULL)
	{
		cout << lista3->Legajo << " ";
		lista3 = lista3->Siguiente;
	}
}

Nodo4* insertarAlFinal(Nodo4*& l, int x) {
	Nodo4* nuevo = new Nodo4();
	nuevo->Legajo = x;
	nuevo->Siguiente = NULL;

	if (l == NULL) {
		l = nuevo;
	}
	else {
		Nodo4* aux = l;
		while (aux->Siguiente != NULL)
			aux = aux->Siguiente;

		aux->Siguiente = nuevo;
	}
	return nuevo;
}