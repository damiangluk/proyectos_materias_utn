#include <iostream>
using namespace std;

struct Nodo { int info; Nodo* Siguiente; };
bool eliminarPosicionCola(Nodo*&, Nodo*&, int, int);
void insertarEnCola1(Nodo*&, Nodo*&, int);
int eliminarEnCola1(Nodo*&, Nodo*&);

void main10() {
	int ingreso;
	Nodo* frente = NULL, * fin = NULL;
	bool dosnodoseliminados = false;

	cout << "ingrese un valor (0 si desea terminar): ";
	cin >> ingreso;
	while (ingreso != 0) {
		insertarEnCola1(frente, fin, ingreso);
		cout << "ingrese un valor (0 si desea terminar): ";
		cin >> ingreso;
	}

	int pos1 = -1, pos2 = -1;
	while (pos1 <= 0)
	{
		cout << endl << "Ingrese la primera posicion de la cola a eliminar: ";
		cin >> pos1;
	}
	while (pos2 <= 0)
	{
		cout << endl << "Ingrese la segunda posicion de la cola a eliminar: ";
		cin >> pos2;
	}
	if (eliminarPosicionCola(frente, fin, pos1 -1, pos2 -1))
	{
		cout << "S" << endl;
	}
	else {
		cout << "N" << endl;
	}

	while (frente != NULL) cout << eliminarEnCola1(frente, fin) << " ";
}

void insertarEnCola1(Nodo*& frente, Nodo*& fin, int x) {
	Nodo* p = new Nodo();
	p->info = x;
	p->Siguiente = NULL;
	if (frente == NULL) frente = p; else fin->Siguiente = p;
	fin = p;
	return;
}
bool eliminarPosicionCola(Nodo*& frente, Nodo*& fin, int f, int g) {
	bool eliminof = false;
	bool eliminog = false;
	Nodo* frentenuevo = frente;
	Nodo* finuevo = fin;
	frente = NULL;
	fin = NULL;

	for (int i = 0; frentenuevo != NULL; i++)
	{
		if (i == f) {

			eliminarEnCola1(frentenuevo, finuevo);
			eliminof = true;
		}
		else if (i == g) {
			eliminarEnCola1(frentenuevo, finuevo);
			eliminog = true;
		}
		else {
			insertarEnCola1(frente, fin, eliminarEnCola1(frentenuevo, finuevo));
		}
	}
	return (eliminof && eliminog);
}

int eliminarEnCola1(Nodo*& frente, Nodo*& fin) {
	int x;
	Nodo* p = frente;
	x = p->info;
	frente = p->Siguiente;
	if (frente == NULL)
		fin = NULL;
	delete p;
	return x;
}
