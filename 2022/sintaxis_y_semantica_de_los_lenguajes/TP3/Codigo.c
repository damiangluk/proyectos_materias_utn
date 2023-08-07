#include <stdio.h>



typedef struct InfoEstado {

	int estadoActual;

	int siguiente;

    char caracter;

} tablaTransiciones;



int encontrarEstado(int[], int , int);

int buscarEnTransiciones(tablaTransiciones[], int, int, char);

int reconocerCategoriaLexica(tablaTransiciones [], int , int [], char [], int, int);

void printResult(int, char[], char[]);



int main() {

    int resultado;



    // IDENTIFICADOR (I)

    tablaTransiciones transicionesI[9] = {{0, 1, 'o'}, {0, 1, 'p'}, {0, 1, 'a'}, {1, 2, 'o'}, {1, 2, 'p'}, {1, 2, 'a'}, 

                                            {2, 1, 'o'}, {2, 1, 'p'}, {2, 1, 'a'}};

    int estadoInicialI = 0;

    int estadosFinalesI[2] = {1, 2};

    char cadenaErroneaI[] = "pared";

    char cadenaCorrectaI[] = "paooa";

    char categoriaI[] = "Identificador";



    resultado = reconocerCategoriaLexica(transicionesI, estadoInicialI, estadosFinalesI, cadenaErroneaI, 2, 9);

    printResult(resultado, cadenaErroneaI, categoriaI);

    resultado = reconocerCategoriaLexica(transicionesI, estadoInicialI, estadosFinalesI, cadenaCorrectaI, 2, 9);

    printResult(resultado, cadenaCorrectaI, categoriaI);

    printf("\n");

    

    // CONSTANTE (C)

    tablaTransiciones transicionesC[9] = {{0, 1, '0'}, {0, 1, '1'}, {0, 1, '2'}, {1, 2, '0'}, {1, 2, '1'}, {1, 2, '2'}, 

                                            {2, 1, '0'}, {2, 1, '1'}, {2, 1, '2'}};

    int estadoInicialC = 0;

    int estadosFinalesC[2] = {1, 2};

    char cadenaErroneaC[] = "0132010";

    char cadenaCorrectaC[] = "012010";

    char categoriaC[] = "Constante";



    resultado = reconocerCategoriaLexica(transicionesC, estadoInicialC, estadosFinalesC, cadenaErroneaC, 2, 9);

    printResult(resultado, cadenaErroneaC, categoriaC);

    resultado = reconocerCategoriaLexica(transicionesC, estadoInicialC, estadosFinalesC, cadenaCorrectaC, 2, 9);

    printResult(resultado, cadenaCorrectaC, categoriaC);

    printf("\n");



    // LITERAL CADENA (LC)

    tablaTransiciones transicionesLC[5] = {{0, 1, '!'}, {1, 1, 'e'}, {1, 1, 'd'}, {1, 1, 'u'}, {1, 2, '!'}};

    int estadoInicialLC = 0;

    int estadosFinalesLC[1] = {2};

    char cadenaErroneaLC[] = "!ede!!";

    char cadenaCorrectaLC[] = "!deued!";

    char categoriaLC[] = "Literal cadena";



    resultado = reconocerCategoriaLexica(transicionesLC, estadoInicialLC, estadosFinalesLC, cadenaErroneaLC, 1, 5);

    printResult(resultado, cadenaErroneaLC, categoriaLC);

    resultado = reconocerCategoriaLexica(transicionesLC, estadoInicialLC, estadosFinalesLC, cadenaCorrectaLC, 1, 5);

    printResult(resultado, cadenaCorrectaLC, categoriaLC);

    printf("\n");



    // OPERADOR (O)

    tablaTransiciones transicionesO[2] = {{0, 1, '%'}, {0, 1, '@'}};

    int estadoInicialO = 0;

    int estadosFinalesO[1] = {1};

    char cadenaErroneaO[] = "@%";

    char cadenaCorrectaO[] = "%";

    char categoriaO[] = "Operador";



    resultado = reconocerCategoriaLexica(transicionesO, estadoInicialO, estadosFinalesO, cadenaErroneaO, 1, 2);

    printResult(resultado, cadenaErroneaO, categoriaO);

    resultado = reconocerCategoriaLexica(transicionesO, estadoInicialO, estadosFinalesO, cadenaCorrectaO, 1, 2);

    printResult(resultado, cadenaCorrectaO, categoriaO);

    printf("\n");



    // CARACTER DE PUNTUACION (CP)

    tablaTransiciones transicionesCP[3] = {{0, 1, '.'}, {0, 1, '('}, {0, 1, ')'}};

    int estadoInicialCP = 0;

    int estadosFinalesCP[1] = {1};

    char cadenaErroneaCP[] = "/";

    char cadenaCorrectaCP[] = ".";

    char categoriaCP[] = "Caracter de puntuacion";



    resultado = reconocerCategoriaLexica(transicionesCP, estadoInicialCP, estadosFinalesCP, cadenaErroneaCP, 1, 3);

    printResult(resultado, cadenaErroneaCP, categoriaCP);

    resultado = reconocerCategoriaLexica(transicionesCP, estadoInicialCP, estadosFinalesCP, cadenaCorrectaCP, 1, 3);

    printResult(resultado, cadenaCorrectaCP, categoriaCP);



    // PALABRA RESERVADA (PR)

    tablaTransiciones transicionesPR[8] = {{0, 1, 'c'}, {0, 7, 'b'}, {1, 2, 'o'}, {2, 3, 'r'}, {3, 4, 'r'} , {4, 5, 'e'} , {5, 6, 'r'}, {7,5,'a'}};

    int estadoInicialPR = 0;

    int estadosFinalesPR[1] = {6};

    char cadenaErroneaPR[] = "hola";

    char cadenaCorrectaPR[] = "bar";

    char categoriaPR[] = "Palabra reservada";



    resultado = reconocerCategoriaLexica(transicionesPR, estadoInicialPR, estadosFinalesPR, cadenaErroneaPR, 1, 8);

    printResult(resultado, cadenaErroneaPR, categoriaPR);

    resultado = reconocerCategoriaLexica(transicionesPR, estadoInicialPR, estadosFinalesPR, cadenaCorrectaPR, 1, 8);

    printResult(resultado, cadenaCorrectaPR, categoriaPR);



}



int reconocerCategoriaLexica(tablaTransiciones transiciones[], int estadoInicial, int estadosFinales[], char cadena[], int cantFinales, int cantTransiciones)

{

    int estadoActual = estadoInicial;

    int i = 0;

    while (cadena[i] != '\0')

    {

        int pos = buscarEnTransiciones(transiciones, estadoActual, cantTransiciones, cadena[i]);

        if(pos != -1)

        {

            estadoActual = transiciones[pos].siguiente;

            i++;

        } else {

            return 0;

        }

    }



    if (encontrarEstado(estadosFinales, cantFinales, estadoActual) != -1)

    {

        return 1;

    }

    return 0;

}



int encontrarEstado(int vec[], int cant, int elemento)

{

    int pos=-1;

    for (int i = 0; i < cant; i++)

    {

        if(vec[i] == elemento){

            pos=i;

        }

    }



    return pos;

}



int buscarEnTransiciones(tablaTransiciones transiciones[], int estado, int cantEstados, char c)

{

    int pos=-1;

    for (int i = 0; i < cantEstados; i++)

    {   

        if(transiciones[i].estadoActual == estado && transiciones[i].caracter == c)

        {

            pos = i;

        }

    }



    return pos;

}



void printResult(int resultado, char cadena[], char categoria[])

{

    if(resultado) 

        printf("La cadena %s fue reconocida como un/a %s \n" , cadena, categoria);

    else

        printf("La cadena %s NO fue reconocida como un/a %s \n" , cadena, categoria);    

}