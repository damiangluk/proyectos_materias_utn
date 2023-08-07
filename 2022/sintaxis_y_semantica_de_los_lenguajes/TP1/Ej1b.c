#include <stdio.h>
#include <string.h>

int retornarLongitudDeDigitos(int cadena[])
{
    int contador = 0;
    while (cadena[contador] != '\0') {
        contador++;
    }
    return contador;
}

int Pow(int X, int Y) {

	int power = 1, i;

	for (i = 1; i <= Y; ++i) {
		power = power * X;
	}

	return power;

}

int valorNumericoDeCadena(int cadena[])
{
    int contador = 0;
    int numero = 0;
    int longitud = retornarLongitudDeDigitos(cadena);
    while (cadena[contador] != '\0') {
        printf("%d ", numero);
        numero += cadena[contador] * (Pow(10, longitud-1));
        contador++;
        longitud--;
    }
    return numero;
}