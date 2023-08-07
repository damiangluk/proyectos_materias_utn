#include <iostream>
using namespace std;

struct Registro { int info; };
struct Nodo { Registro reg; Nodo* sgte; };

void queue12(Nodo*&, Nodo*&, int);
int unqueue12(Nodo*&, Nodo*&);

void main12() {

    int ingreso;
    Nodo* FrenteA = NULL, * FinA = NULL, * FrenteB = NULL, * FinB = NULL, * FrenteAB = NULL, * FinAB = NULL;

    cout << "ingrese un valor a la cola A (0 si desea terminar): ";
    cin >> ingreso;
    while (ingreso != 0) {
        queue12(FrenteA, FinA, ingreso);
        cout << "ingrese un valor a la cola A (0 si desea terminar): ";
        cin >> ingreso;
    }

    cout << "ingrese un valor a la cola B (0 si desea terminar): ";
    cin >> ingreso;
    while (ingreso != 0) {
        queue12(FrenteB, FinB, ingreso);
        cout << "ingrese un valor a la cola B (0 si desea terminar): ";
        cin >> ingreso;
    }

    while (FrenteA != NULL) {
        queue12(FrenteAB, FinAB, unqueue12(FrenteA, FinA));
    }
    while (FrenteB != NULL) {
        queue12(FrenteAB, FinAB, unqueue12(FrenteB, FinB));
    }
    while (FrenteAB != NULL)
    {
        cout << unqueue12(FrenteAB, FinAB) << " ";
    }
}

void queue12(Nodo*& frente, Nodo*& fin, int x) {
    Nodo* p = new Nodo();
    p->reg.info = x;
    p->sgte = NULL;
    if (frente == NULL) frente = p; else fin->sgte = p;
    fin = p;
    return;
}

int unqueue12(Nodo*& frente, Nodo*& fin) {
    int x;
    Nodo* p = frente;
    x = p->reg.info;
    frente = p->sgte;
    if (frente == NULL) fin = NULL;
    delete p;
    return x;
}