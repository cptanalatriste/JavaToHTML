%{
#include <string>
#include "node.h"
#include "parser.hpp"
#define GUARDAR_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }
%}

%%

[ \t\n]                 ;
L?\"(\\.|[^\\"])*\"	GUARDAR_TOKEN; return CADENA;
[a-zA-Z_][a-zA-Z0-9_]*  GUARDAR_TOKEN; return IDENTIFICADOR;
[0-9]+\.[0-9]*          GUARDAR_TOKEN; return DECIMAL;
[0-9]+                  GUARDAR_TOKEN; return ENTERO;
"="                     return TOKEN(IGUAL);
"("                     return TOKEN(IPARENTESIS);
")"                     return TOKEN(DPARENTESIS);
"{"                     return TOKEN(ILLAVE);
"}"                     return TOKEN(DLLAVE);
","                     return TOKEN(COMA);
.                       printf("Token desconocido\n"); yyterminate();

%%
