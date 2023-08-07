#include <iostream>
using namespace std;

struct Nodo { int info; Nodo* Siguiente; };
void insertarEnCola2(Nodo*&, Nodo*&, int);
int eliminarEnCola2(Nodo*&, Nodo*&);

void main11() {
	int ingreso;
	Nodo* frente = NULL, * fin = NULL;

	cout << "ingrese un valor (0 si desea terminar): ";
	cin >> ingreso;
	while (ingreso != 0) {
		insertarEnCola2(frente, fin, ingreso);
		cout << "ingrese un valor (0 si desea terminar): ";
		cin >> ingreso;
	}

	int CantNodos = 0;
	while (frente != NULL)
	{
		CantNodos++;
		eliminarEnCola2(frente, fin);
	}
	cout << "La cantidad de nodos de la cola es " << CantNodos;
}

void insertarEnCola2(Nodo*& frente, Nodo*& fin, int x) {
	Nodo* p = new Nodo();
	p->info = x;
	p->Siguiente = NULL;
	if (frente == NULL) frente = p; else fin->Siguiente = p;
	fin = p;
	return;
}

int eliminarEnCola2(Nodo*& frente, Nodo*& fin) {
	int x;
	Nodo* p = frente;
	x = p->info;
	frente = p->Siguiente;
	if (frente == NULL)
		fin = NULL;
	delete p;
	return x;
}
