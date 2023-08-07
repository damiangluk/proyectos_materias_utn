#include <stdio.h>
#include <string.h>

int retornarLongitud(char cadena[])
{
    int contador = 0;
    while (cadena[contador] != '\0') {
        contador++;
    }
    return contador;
}