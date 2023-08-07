#include <iostream>
using namespace std;

struct Nodo3 {
	int Legajo;
	Nodo3* Siguiente;
};

Nodo3* insertarAlFinal(Nodo3*&, int);
Nodo3* insertaPrimero(Nodo3*&, int);

void main() {

	int dato,contador=0;
	cout << "Ingrese dato entero: ";
	cin >> dato;
	Nodo3* lista = new Nodo3();
	lista->Legajo = dato;
	lista->Siguiente = NULL;
	cout << "Ingrese dato entero: ";
	cin >> dato;

	while (dato != 0) {
		insertarAlFinal(lista, dato);
		cout << "Ingrese dato entero: ";
		cin >> dato;
	}

	Nodo3* aux = new Nodo3();
	aux = lista;
	while (aux != NULL) {
		contador++;
		aux = aux->Siguiente;
	}
	aux = new Nodo3();
	aux = lista;
	if (contador < 5) {
		while (aux != NULL) {
			cout << aux->Legajo << endl;
			aux = aux->Siguiente;
		}
	} else{
		Nodo3* aux2 = new Nodo3();
		while (aux != NULL) {
			insertaPrimero(aux2, aux->Legajo);
			aux = aux->Siguiente;
		}
		while (aux2 != NULL) {
			cout << aux2->Legajo << endl;
			aux2 = aux2->Siguiente;
		}
	}

}
Nodo3* insertarOrdenado(Nodo3*& l, int v) {

	Nodo3* nuevo = new Nodo3();
	nuevo->Legajo = v;
	nuevo->Siguiente = NULL;
	Nodo3* ant = NULL;
	Nodo3* actual = l;
	Nodo3* aux = l;

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

Nodo3* insertarAlFinal(Nodo3*& l, int x) {
	Nodo3* nuevo = new Nodo3();
	nuevo->Legajo = x;
	nuevo->Siguiente = NULL;

	if (l == NULL) {
		l = nuevo;
	}
	else {
		Nodo3* aux = l;
		while (aux->Siguiente != NULL)
			aux = aux->Siguiente;

		aux->Siguiente = nuevo;
	}
	return nuevo;
}

Nodo3* insertaPrimero(Nodo3*& l, int x)
{
	Nodo3* p = new Nodo3();
	p->Legajo = x;
	p->Siguiente = l;
	l = p;
	return p;
}
