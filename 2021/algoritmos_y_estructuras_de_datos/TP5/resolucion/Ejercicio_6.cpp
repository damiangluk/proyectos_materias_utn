#include<iostream>
using namespace std;

struct Nodo { int valor; Nodo* Siguiente; };

void push6(Nodo*&, int);
int pop6(Nodo*&);
bool InsertarValorXPorY(Nodo*&, int, int);

void main6()
{
	Nodo* pila = NULL;
	int x, y;

	for (int i = 0; i < 10; i++)
	{
		push6(pila, i + 1);
	}

	cout << "Ingrese el valor a buscar: ";
	cin >> x;
	cout << "Ingrese un valor a reemplazar: ";
	cin >> y;
	if (InsertarValorXPorY(pila, x, y))
	{
		cout << "Se reemplazo correctamente" << endl;
	}
	else
	{
		cout << "No se encontro el valor " << x << " en la pila" << endl;
	}
	while (pila != NULL)
	{
		cout << pop6(pila) << " ";
	}
}

int pop6(Nodo*& pila) {
	int x = pila->valor;
	Nodo* NodoAEliminar = pila;
	pila = NodoAEliminar->Siguiente;
	delete NodoAEliminar;
	return x;
}

void push6(Nodo*& NodoActual, int InfoActual)
{
	Nodo* NodoNuevo = new Nodo();
	NodoNuevo->valor = InfoActual;
	NodoNuevo->Siguiente = NodoActual;
	NodoActual = NodoNuevo;
}

bool InsertarValorXPorY(Nodo*& pila, int x, int y)
{
	Nodo* pilaNueva = NULL;
	push6(pilaNueva, pila->valor);
	while (pila->Siguiente != NULL)
	{
		pila = pila->Siguiente;
		push6(pilaNueva, pila->valor);
	}

	pila = NULL;
	bool inserto = false;
	while (pilaNueva != NULL)
	{
		if (x == pilaNueva->valor)
		{
			push6(pila, y);
			inserto = true;
		}
		else
		{
			push6(pila, pilaNueva->valor);
		}
		pilaNueva = pilaNueva->Siguiente;
	}
	return inserto;
}