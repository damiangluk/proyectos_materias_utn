%{

#include <stdio.h>
#include "parser.tab.h"
#include <ctype.h>
%}


%%

correr { printf("Encontre la palabra reservada: %s\n", yytext); return PR_CORRER; }
bar { printf("Encontre la palabra reservada: %s\n", yytext); return PR_BAR; }
[opa]+ { printf("Encontre el identificador: %s\n", yytext); return IDENTIFICADOR; }
[012]+ { printf("Encontre la constante: %s\n", yytext); return CONSTANTE; }
![edu]*! { printf("Encontre el literal cadena: %s\n", yytext); return LITERAL_CADENA; }
[%] { printf("Encontre el operador: %s\n", yytext); return '%'; }
[@] { printf("Encontre el operador: %s\n", yytext); return '@'; }
[.] { printf("Encontre el caracter de puntuacion: %s\n", yytext); return '.'; }
[(] { printf("Encontre el caracter de puntuacion: %s\n", yytext); return '('; }
[)] { printf("Encontre el caracter de puntuacion: %s\n", yytext); return ')'; }

.l\n;
%%

yywrap() {}
