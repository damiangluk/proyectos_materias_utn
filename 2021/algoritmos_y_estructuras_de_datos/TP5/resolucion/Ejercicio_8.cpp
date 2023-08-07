#include<iostream>
using namespace std;

struct Nodo { char Nombre[20 + 1], Apellido[20 + 1]; Nodo* Siguiente; };

void push8(Nodo*&, char[20 + 1], char[20 + 1]);
void pop8(Nodo*&);

void main8()
{
	Nodo* pila = NULL;
	char Nombre[20 + 1], Apellido[20 + 1];

	cout << "Ingrese su nombre (0 si desea terminar): ";
	cin >> Nombre;
	while (strcmp(Nombre, "0"))
	{
		cout << "Ingrese su apellido: ";
		cin >> Apellido;
		push8(pila, Nombre, Apellido);
		cout << "Ingrese su nombre (0 si desea terminar): ";
		cin >> Nombre;
	} 

	while (pila != NULL)
	{
		cout << pila->Nombre << " " << pila->Apellido << ", ";
		pila = pila->Siguiente;
	}
}

void pop8(Nodo*& pila) {
	Nodo* NodoAEliminar = pila;
	pila = NodoAEliminar->Siguiente;
	delete NodoAEliminar;
}

void push8(Nodo*& NodoActual, char Nombre[20 + 1], char Apellido[20 + 1])
{
	Nodo* NodoNuevo = new Nodo();
	strcpy_s(NodoNuevo->Nombre, Nombre);
	strcpy_s(NodoNuevo->Apellido, Apellido);
	NodoNuevo->Siguiente = NodoActual;
	NodoActual = NodoNuevo;
}