#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Ej1a.c"
#include "Ej1b.c"
#include "Ej1c.c"
#include "Ej1d.c"
#include "Ej1e.c"
#include "Ej1f.c"

void respuesta(bool resultado);
void mostrarCadena(char cadena[]);

int main()
{
    int entrada = 0;

    while (entrada != -1)
    {
        mostrarCadena("\ningrese el numero de ejercicio que desea probar (1 a 6 y -1 para salir)\n");
        scanf("%d",&entrada);

        char *cadena;

        switch (entrada)
        {
            case 1: // devolver la longitud de la palabra ingresada
            {
                int longitud1 = retornarLongitud("hola\0"), longitud2 = retornarLongitud("buenosdias\0");
                if(longitud1 == 4 && longitud2 == 10)
                {
                    respuesta(true);
                } else
                {
                    respuesta(false);
                    printf("%s%d\n","El resultado obtenido al ingresar 'hola' es: ", longitud1);
                    printf("%s%d\n","Al ingresar 'buenosdias es: ", longitud2);
                }
                break;
            }
                    
            case 2: // devolver los valores ASCII de la palabra ingresada
            {
                int digitos[5] = {2, 1, 3, 5,'\0'};
                int resultadoEsperado = 2135, resultado;
                mostrarCadena("\nEl resultado esperado al ingresar '2, 1, 3, 5' es: '2135'");
                resultado = valorNumericoDeCadena(digitos);

                mostrarCadena("\nEl resultado obtenido es: ");
                printf("%d", resultado);

                if(resultadoEsperado == resultado){
                    respuesta(true);
                } else {
                    respuesta(false);
                }
                break;
            }

            case 3: // devolver la palabra en mayusculas
            {
                char cadenaEsperada[12] = "TELEVISION\0";
                char resultadoCadena[12] = "television\0";
                convMayus(resultadoCadena);

                mostrarCadena("\nEl resultado esperado al ingresar 'television' es: 'TELEVISION'");
                mostrarCadena("\nEl resultado obtenido es: ");
                mostrarCadena(resultadoCadena);

                bool esCorrecto = true;
                for (int i = 0; i < 10; i++)
                {
                    if(resultadoCadena[i] != cadenaEsperada[i])
                    {
                        esCorrecto = false;
                        break;
                    }
                }
                
                respuesta(esCorrecto);
                
                break;
            }
                    
            case 4: // eliminar de una cadena todas las ocurrencias de un caracter determinado
            {
                char cadenaEsperada[15] = "mericltin\0";
                char resultadoCadena[15] = "americalatina\0";
                
                eliminarCaracter(resultadoCadena, 'a');

                mostrarCadena("\nEl resultado esperado al ingresar 'americalatina' es: 'mericltin'");
                mostrarCadena("\nEl resultado obtenido es: ");

                mostrarCadena(resultadoCadena);

                bool esCorrecto = true;
                for (int i = 0; i < 9; i++)
                {
                    if(resultadoCadena[i] != cadenaEsperada[i])
                    {
                        esCorrecto = false;
                        break;
                    }
                }
                
                respuesta(esCorrecto);
                break;
            }

                    
            case 5: // concatenar una cadena al final de otra
            {
                char cadenaEsperada[12] = "buenosdias\0";
                char resultadoCadena[12] = "buenos\0";
                concatenarCadena2EnCadena1(resultadoCadena,"dias\0");

                mostrarCadena("\nEl resultado esperado al ingresar 'buenos', 'dias' es: 'buenosdias'");
                mostrarCadena("\nEl resultado obtenido es: ");

                mostrarCadena(resultadoCadena);

                bool esCorrecto = true;
                for (int i = 0; i < 10; i++)
                {
                    if(resultadoCadena[i] != cadenaEsperada[i])
                    {
                        esCorrecto = false;
                        break;
                    }
                }
                
                respuesta(esCorrecto);
                break;
            }

            case 6: // insertar caracter en una posicion determinada de una cadena
            {
                char cadenaEsperada[8] = "ventana";
                char resultadoCadena[8] = "ventena";
                modificarPosicionDeCadena(resultadoCadena, 5, 'a');

                mostrarCadena("\nEl resultado esperado al ingresar 'ventena', 5 , 'a' es: 'ventana'");
                mostrarCadena("\nEl resultado obtenido es: ");

                mostrarCadena(resultadoCadena);

                bool esCorrecto = true;
                for (int i = 0; i < 7; i++)
                {
                    if(resultadoCadena[i] != cadenaEsperada[i])
                    {
                        esCorrecto = false;
                        break;
                    }
                }
                
                respuesta(esCorrecto);
                break;
            }

            default:
                if (entrada != -1) mostrarCadena("No se ingreso una opcion dentro del rango");
            break;
        }
    }

    return 0;
}

void respuesta(bool resultado)
{
    if (resultado)
    {
        mostrarCadena("\nEl ejercicio esta resuelto correctamente\n");
    }else
    {
        mostrarCadena("\nEl resultado del ejercicio no es correcto\n");
    }
}

void mostrarCadena(char cadena[])
{
    printf("%s",cadena);
}