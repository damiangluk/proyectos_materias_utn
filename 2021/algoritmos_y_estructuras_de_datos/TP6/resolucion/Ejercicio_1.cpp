#include <iostream>
#include <cstring>
using namespace std;

struct Nodo1 {
	int Legajo;
	Nodo1* Siguiente;
};

Nodo1* insertarOrdenado(Nodo1*&, int);

void main() 
{
	int dato, contador = 0;
	cout << "Ingrese dato entero: ";
	cin >> dato;
	Nodo1* lista = new Nodo1();
	lista->Legajo = dato;
	lista->Siguiente = NULL;
	cout << "Ingrese dato entero: ";
	cin >> dato;

	while (dato!=0) {
		insertarOrdenado(lista, dato);
		cout << "Ingrese dato entero: ";
		cin >> dato;
	}

	Nodo1* aux = new Nodo1();
	aux = lista;
	while (aux != NULL) {
		contador++;
		aux = aux->Siguiente;
	}
	cout << "el numero de nodos es: " << contador;
}

Nodo1* insertarOrdenado(Nodo1*& l, int v) {

	Nodo1* nuevo = new Nodo1();
	nuevo->Legajo = v;
	nuevo->Siguiente = NULL;
	Nodo1* ant = NULL;
	Nodo1* actual = l;
	Nodo1* aux = l;

	while (actual != NULL && aux->Legajo < v) {
		ant = actual;
		actual = actual->Siguiente;
	}

	if (ant == NULL)
		l = nuevo;
	else
		ant->Siguiente = nuevo;

	nuevo->Siguiente = actual;

	return nuevo;
}