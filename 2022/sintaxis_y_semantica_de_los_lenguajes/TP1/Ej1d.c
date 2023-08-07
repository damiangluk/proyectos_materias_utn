#include <stdio.h>
#include <string.h>

void eliminarCaracter(char cadena[], char c)
{
	int len = 0;
	char cadenaresultado[20];
	for (int i = 0; cadena[i] != '\0'; i++)
	{
		len++;		
		cadenaresultado[i] = cadena[i];
	}

	int j = 0;
  	for(int i = 0; i < len; i++)
	{
		if(cadenaresultado[i] != c)
		{
			cadena[j] = cadenaresultado[i];
            j++;
		}
	}
	cadena[j] = '\0';
}