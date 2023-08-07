#include<iostream>
using namespace std;

struct Nodo { int valor; Nodo* Siguiente; };

void push2(Nodo*&, int);
int pop2(Nodo*&);
void InsertarValorEnTerceraPosicion(Nodo*&, int);

void main2()
{
	Nodo* pila = NULL;
	int numero;

	for (int i = 0; i < 10; i++)
	{
		push2(pila, i + 1);
	}

	cout << "Ingrese un valor: ";
	cin >> numero;
	InsertarValorEnTerceraPosicion(pila, numero);
	while (pila != NULL)
	{
		cout << pop2(pila) << " ";
	}
}

int pop2(Nodo*& pila) {
	int x = pila->valor;
	Nodo* NodoAEliminar = pila;
	pila = NodoAEliminar->Siguiente;
	delete NodoAEliminar;
	return x;
}

void push2(Nodo*& NodoActual, int InfoActual)
{
	Nodo* NodoNuevo = new Nodo();
	NodoNuevo->valor = InfoActual;
	NodoNuevo->Siguiente = NodoActual;
	NodoActual = NodoNuevo;
}

void InsertarValorEnTerceraPosicion(Nodo*& pila, int valor)
{
	Nodo* pilaNueva = NULL;
	push2(pilaNueva, pila->valor);
	while (pila->Siguiente != NULL)
	{
		pila = pila->Siguiente;
		push2(pilaNueva, pila->valor);
	}

	pila = NULL;
	int i = 1;
	push2(pila, pilaNueva->valor);
	while (pilaNueva->Siguiente != NULL)
	{
		pilaNueva = pilaNueva->Siguiente;
		push2(pila, pilaNueva->valor);
		i++;
		if (i == 2)
		{
			push2(pila, valor);
		}
	}
}