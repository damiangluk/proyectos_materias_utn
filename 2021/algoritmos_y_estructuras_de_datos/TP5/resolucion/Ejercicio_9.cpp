#include<iostream>
using namespace std;

struct Nodo { int info; Nodo* Siguiente; };

void push9(Nodo*& NodoActual, int InfoActual);
int pop9(Nodo*&);
Nodo* ordenar(Nodo*&, int);

void main9()
{
    Nodo* pila = NULL;
    int numero, CantElementos = 0;
    cout << "Ingrese un valor (0 si desea terminar): ";
    cin >> numero;
    while (numero != 0)
    {
        CantElementos++;
        push9(pila, numero);
        cout << "Ingrese un valor (0 si desea terminar): ";
        cin >> numero;
    }

    pila = ordenar(pila, CantElementos);

    while (pila->Siguiente != NULL)
    {
        cout << pop9(pila) << " ";
    }
    cout << pila->info;
}

void push9(Nodo*& NodoActual, int InfoActual)
{
    Nodo* NodoNuevo = new Nodo();
    NodoNuevo->info = InfoActual;
    NodoNuevo->Siguiente = NodoActual;
    NodoActual = NodoNuevo;
}

int pop9(Nodo*& pila) {
    int x = pila->info;
    Nodo* NodoAEliminar = pila;
    pila = NodoAEliminar->Siguiente;
    delete NodoAEliminar;
    return x;
}

Nodo* ordenar(Nodo*& pila, int CantElementos) {
    Nodo* aux1 = NULL;
    Nodo* aux2 = NULL;
    int ValorMaximo;
    do
    {
        aux2 = pila;
        ValorMaximo = pila->info;
        while (pila->Siguiente != NULL)
        {
            if (pila->Siguiente->info > ValorMaximo)
            {
                ValorMaximo = pila->Siguiente->info;
            }
            pila = pila->Siguiente;
        }
        pila = aux2;
        aux2 = NULL;
        while (pila != NULL)
        {
            int x = pop9(pila);
            if (x == ValorMaximo)
            {
                push9(aux1, x);
            }
            else
            {
                push9(aux2, x);
            }

        }
        pila = aux2;
    } while (aux2 != NULL);
    return aux1;
}