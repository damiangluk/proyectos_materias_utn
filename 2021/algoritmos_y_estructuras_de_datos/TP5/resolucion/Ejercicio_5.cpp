#include<iostream>
using namespace std;

struct Nodo { int valor; Nodo* Siguiente; };

void push5(Nodo*&, int);
int pop5(Nodo*&);

void main5()
{
	Nodo* pila = NULL;
	int numero;

	for (int i = 0; i < 10; i++)
	{
		push5(pila, i + 1);
	}

	cout << "Ingrese un valor: ";
	cin >> numero;
	push5(pila, numero);
	while (pila != NULL)
	{
		cout << pop5(pila) << " ";
	}
}

int pop5(Nodo*& pila) {
	int x = pila->valor;
	Nodo* NodoAEliminar = pila;
	pila = NodoAEliminar->Siguiente;
	delete NodoAEliminar;
	return x;
}

void push5(Nodo*& NodoActual, int InfoActual)
{
	Nodo* NodoNuevo = new Nodo();
	NodoNuevo->valor = InfoActual;
	NodoNuevo->Siguiente = NodoActual;
	NodoActual = NodoNuevo;
}