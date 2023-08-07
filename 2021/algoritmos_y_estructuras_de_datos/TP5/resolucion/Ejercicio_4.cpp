#include<iostream>
using namespace std;

struct Nodo { int valor; Nodo* Siguiente; };

void push4(Nodo*&, int);
int pop4(Nodo*&);
bool InsertarValorXEnPosY(Nodo*&, int, int);

void main4()
{
	Nodo* pila = NULL;
	int x, y;

	for (int i = 0; i < 10; i++)
	{
		push4(pila, i + 1);
	}

	cout << "Ingrese el valor a reemplazar: ";
	cin >> x;
	cout << "Ingrese la posicion donde desea reemplazar: ";
	cin >> y;
	if (InsertarValorXEnPosY(pila, x, y))
	{
		cout << "Se inserto correctamente" << endl;
	}
	else
	{
		cout << "No se pudo insertar en la posicion indicada" << endl;
	}
	while (pila != NULL)
	{
		cout << pop4(pila) << " ";
	}
}

int pop4(Nodo*& pila) {
	int x = pila->valor;
	Nodo* NodoAEliminar = pila;
	pila = NodoAEliminar->Siguiente;
	delete NodoAEliminar;
	return x;
}

void push4(Nodo*& NodoActual, int InfoActual)
{
	Nodo* NodoNuevo = new Nodo();
	NodoNuevo->valor = InfoActual;
	NodoNuevo->Siguiente = NodoActual;
	NodoActual = NodoNuevo;
}

bool InsertarValorXEnPosY(Nodo*& pila, int x, int y)
{
	Nodo* pilaNueva = NULL;
	push4(pilaNueva, pila->valor);
	while (pila->Siguiente != NULL)
	{
		pila = pila->Siguiente;
		push4(pilaNueva, pila->valor);
	}

	pila = NULL;
	bool inserto = false;
	for (int i = 1; pilaNueva != NULL; i++)
	{
		if (y == i)
		{
			push4(pila, x);
			inserto = true;
		}
		push4(pila, pilaNueva->valor);
		pilaNueva = pilaNueva->Siguiente;
	}
	return inserto;
}