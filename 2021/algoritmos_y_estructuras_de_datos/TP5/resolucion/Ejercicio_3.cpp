#include<iostream>
using namespace std;

struct Nodo { int valor; Nodo* Siguiente; };

void push3(Nodo*&, int);
int pop3(Nodo*&);
char InsertarValorXPorY(Nodo*&, int, int);

void main3()
{
	Nodo* pila = NULL;
	int x, y;

	for (int i = 0; i < 10; i++)
	{
		push3(pila, i + 1);
	}

	cout << "Ingrese el valor a buscar: ";
	cin >> x;
	cout << "Ingrese un valor a reemplazar: ";
	cin >> y;
	cout << InsertarValorXPorY(pila, x, y);
}

int pop3(Nodo*& pila) {
	int x = pila->valor;
	Nodo* NodoAEliminar = pila;
	pila = NodoAEliminar->Siguiente;
	delete NodoAEliminar;
	return x;
}

void push3(Nodo*& NodoActual, int InfoActual)
{
	Nodo* NodoNuevo = new Nodo();
	NodoNuevo->valor = InfoActual;
	NodoNuevo->Siguiente = NodoActual;
	NodoActual = NodoNuevo;
}

char InsertarValorXPorY(Nodo*& pila, int x, int y)
{
	Nodo* pilaNueva = NULL;
	push3(pilaNueva, pila->valor);
	while (pila->Siguiente != NULL)
	{
		pila = pila->Siguiente;
		push3(pilaNueva, pila->valor);
	}

	pila = NULL;
	char inserto = 'N';
	while (pilaNueva != NULL)
	{
		if (x == pilaNueva->valor)
		{
			push3(pila, y);
			inserto = 'S';
		}
		else
		{
			push3(pila, pilaNueva->valor);
		}
		pilaNueva = pilaNueva->Siguiente;
	}
	return inserto;
}