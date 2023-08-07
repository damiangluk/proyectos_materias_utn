%{ 
    #include<stdio.h>
    int yylex(void);
    void yyerror(const char *);
%} 

%union {
    int num;
    char sym;
}

%token PR_CORRER PR_BAR
%token IDENTIFICADOR
%token<num> CONSTANTE
%token LITERAL_CADENA

%left '%' '@'


%% 
variasSentencias : sentencia variasSentencias | sentencia;
sentencia :  sentenciaEjecucion | sentenciaDeclaracion |sentenciaFuncion;
sentenciaEjecucion : PR_CORRER expresion'.';
sentenciaDeclaracion : declaracion'.';
sentenciaFuncion : IDENTIFICADOR '(' parametros ')' '(' sentencia ')';
parametros : IDENTIFICADOR parametros | IDENTIFICADOR;

expresion : expresionAsignacion | expresionSuma;
termino : CONSTANTE | LITERAL_CADENA | expresionSuma | IDENTIFICADOR ;
expresionAsignacion : termino '@' IDENTIFICADOR ;
expresionSuma : '%' termino termino;

declaracion : declaracionVariable | declaracionFuncion;
declaracionVariable : IDENTIFICADOR PR_BAR;
declaracionFuncion : IDENTIFICADOR PR_BAR '(' CONSTANTE ')';


%% 

int main(void)
{
    switch(yyparse())
    {
        case 0:
            puts("Pertenece al LIC");
            return 0;
        case 1:
            puts("NO pertenece al LIC");
            return 1;

    }

}

void yyerror(const char *s)
{
    puts(s);
    return ;
}