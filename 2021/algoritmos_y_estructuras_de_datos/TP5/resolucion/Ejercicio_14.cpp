#include <iostream>
using namespace std;

struct registro { int ARRIBO; };
struct Nodo { registro REG; Nodo* sgte; };
void queue14(Nodo*&, Nodo*&, int);
int unqueue14(Nodo*&, Nodo*&);
void apareo(Nodo*&, Nodo*&, Nodo*&, Nodo*&, Nodo*&, Nodo*&);


void main() {

    int ingreso;
    Nodo *FrenteA = NULL, *FinA = NULL;
    Nodo *FrenteB = NULL, *FinB = NULL;
    Nodo *FrenteAB = NULL, *FinAB = NULL;

    cout << "ingrese un valor a la cola A (0 si desea terminar): ";
    cin >> ingreso;
    while (ingreso > 0) {
        queue14(FrenteA, FinA, ingreso);
        cout << "ingrese un valor a la cola A (0 si desea terminar): ";
        cin >> ingreso;
    }

    cout << endl << "ingrese un valor a la cola B (0 si desea terminar): ";
    cin >> ingreso;
    while (ingreso > 0) {
        queue14(FrenteB, FinB, ingreso);
        cout << "ingrese un valor a la cola B (0 si desea terminar): ";
        cin >> ingreso;
    }

    apareo(FrenteAB, FinAB, FrenteA, FinA, FrenteB, FinB);

    while (FrenteAB != NULL)
    {
        cout << unqueue14(FrenteAB, FinAB) << endl;
    }

}

void queue14(Nodo*& frente, Nodo*& fin, int x) {
    Nodo* p = new Nodo();
    p->REG.ARRIBO = x;
    p->sgte = NULL;
    if (frente == NULL) frente = p; else fin->sgte = p;
    fin = p;
    return;
}

int unqueue14(Nodo*& frente, Nodo*& fin) {
    int x;
    Nodo* p = frente;
    x = p->REG.ARRIBO;
    frente = p->sgte;
    if (frente == NULL) fin = NULL;
    delete p;
    return x;
}

void apareo(Nodo*& FrenteAB, Nodo*& FinAB, Nodo*& FrenteA, Nodo*& FinA, Nodo*& FrenteB, Nodo*& FinB)
{
    while (FrenteA != NULL && FrenteB != NULL)
    {
        if (FrenteA->REG.ARRIBO < FrenteB->REG.ARRIBO)
        {
            queue14(FrenteAB, FinAB, unqueue14(FrenteA, FinA));
        }
        else
        {
            queue14(FrenteAB, FinAB, unqueue14(FrenteB, FinB));
        }
    }
    while (FrenteA != NULL) {
        queue14(FrenteAB, FinAB, unqueue14(FrenteA, FinA));
    }
    while (FrenteB != NULL) {
        queue14(FrenteAB, FinAB, unqueue14(FrenteB, FinB));
    }
}

