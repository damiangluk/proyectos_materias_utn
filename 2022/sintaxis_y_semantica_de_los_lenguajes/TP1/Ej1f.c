#include <stdio.h>
#include <string.h>

void modificarPosicionDeCadena(char cadena[], int posAIngresar, char letraAIngresar)
{
    int contCadena = retornarLongitud(cadena);

    if (posAIngresar > contCadena || posAIngresar < 1)
    {
        return "pos_inv";
    }
    
    cadena[posAIngresar-1] = letraAIngresar;
}