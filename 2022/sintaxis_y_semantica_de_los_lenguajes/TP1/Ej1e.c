#include <stdio.h>
#include <string.h>

void concatenarCadena2EnCadena1(char cadena1[], char cadena2[])
{
    int i = retornarLongitud(cadena1);

    for(int j=0; cadena2[j]!='\0'; ++j, ++i)
    {
        printf("%d",i);
        cadena1[i] = cadena2[j];
    }
    i++;
    cadena1[i]='\0';
}