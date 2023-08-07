#include <stdio.h>
#include <string.h>

void convMayus(char cadena[])
{
  int i = 0;
  while (cadena[i] != '\0')
  {
    if(cadena[i] >= 'a' && cadena[i] <= 'z')
      cadena[i] =cadena[i] - 32;
    i++;
  }
}