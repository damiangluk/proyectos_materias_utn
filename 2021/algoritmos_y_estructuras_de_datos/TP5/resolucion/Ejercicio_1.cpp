#include<iostream>
using namespace std;

struct Nodo { int valor; Nodo* Siguiente; };

void push1(Nodo*&, int);
int pop1(Nodo*&);
void EliminarPrimeros2YAgregarValor(Nodo*&, int);

void main1()
{
	Nodo* pila = NULL;
	int numero;

	for (int i = 0; i < 10; i++)
	{
		push1(pila, i + 1);
	}

	cout << "Ingrese un valor: ";
	cin >> numero;
	EliminarPrimeros2YAgregarValor(pila, numero);
	while (pila != NULL)
	{
		cout << pop1(pila) << " ";
	}
}

int pop1(Nodo*& pila) {
	int x = pila->valor;
	Nodo* NodoAEliminar = pila;
	pila = NodoAEliminar->Siguiente;
	delete NodoAEliminar;
	return x;
}

void push1(Nodo*& NodoActual, int InfoActual)
{
	Nodo* NodoNuevo = new Nodo();
	NodoNuevo->valor = InfoActual;
	NodoNuevo->Siguiente = NodoActual;
	NodoActual = NodoNuevo;
}

void EliminarPrimeros2YAgregarValor(Nodo*& pila, int valor)
{
	Nodo* pilaNueva = NULL;
	push1(pilaNueva, pila->valor);
	while (pila->Siguiente != NULL)
	{
		pila = pila->Siguiente;
		push1(pilaNueva, pila->valor);
	}

	pila = NULL;
	pilaNueva = pilaNueva->Siguiente;
	push1(pila, valor);
	while (pilaNueva->Siguiente != NULL)
	{
		pilaNueva = pilaNueva->Siguiente;
		push1(pila, pilaNueva->valor);
	}
}