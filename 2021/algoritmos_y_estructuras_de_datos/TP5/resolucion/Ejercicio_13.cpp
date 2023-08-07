#include <iostream>
using namespace std;

// Si tiene mas de 10 nodos*

struct Registro { int info; };
struct Nodo { Registro reg; Nodo* sgte; };

void queue13(Nodo*&, Nodo*&, int);
int unqueue13(Nodo*&, Nodo*&);
void push(Nodo*&, int);
int pop(Nodo*&);

void main13() {

    int ingreso;
    Nodo* Frente = NULL, * Fin = NULL;

    cout << "ingrese un valor a la cola (0 si desea terminar): ";
    cin >> ingreso;
    while (ingreso != 0) {
        queue13(Frente, Fin, ingreso);
        cout << "ingrese un valor a la cola (0 si desea terminar): ";
        cin >> ingreso;
    }

    Nodo* FrenteAux = NULL, * FinAux = NULL;
    int CantNodos = 0;
    while (Frente != NULL) {
        CantNodos++;
        queue13(FrenteAux, FinAux, unqueue13(Frente, Fin));
    }
    Frente = FrenteAux; Fin = FinAux;

    if (CantNodos <= 10)
    {
        while (Frente != NULL)
        {
            cout << unqueue13(Frente, Fin) << " ";
        }
    }
    else
    {
        Nodo* pila = NULL;
        while (Frente != NULL) {
            push(pila, unqueue13(Frente, Fin));
        }
        while (pila != NULL)
        {
            cout << pop(pila) << " ";
        }
    }
}

void queue13(Nodo*& frente, Nodo*& fin, int x) {
    Nodo* p = new Nodo();
    p->reg.info = x;
    p->sgte = NULL;
    if (frente == NULL) frente = p; else fin->sgte = p;
    fin = p;
    return;
}

int unqueue13(Nodo*& frente, Nodo*& fin) {
    int x;
    Nodo* p = frente;
    x = p->reg.info;
    frente = p->sgte;
    if (frente == NULL) fin = NULL;
    delete p;
    return x;
}

void push(Nodo*& Pila, int x)
{
    Nodo* p = new Nodo();
    p->reg.info = x;
    p->sgte = Pila;
    Pila = p;
    return;
}

int pop(Nodo*& Pila)
{
    int x;
    Nodo* p = Pila;
    x = p->reg.info;
    Pila = p->sgte;
    delete p;
    return x;
}