%{
    #include "node.h"
    #include <cstdio>
    #include <cstdlib>
    Bloque *bloquePrograma; 

    extern int yylex();
    void yyerror(const char *s) {  std::printf("Error: %s\n", s);std::exit(1); }
%}

%union {
    Nodo *nodo;
    Bloque *bloque;
    Expresion *expresion;
    Sentencia *sentencia;
    Identificador *identificador;
    DeclaracionVariable *dec_variable;
    std::vector<DeclaracionVariable*> *listaDeclaraciones;
    std::vector<Expresion*> *listaExpresiones;
    std::string *string;
    int token;
}

%token <string> CADENA IDENTIFICADOR ENTERO DECIMAL
%token <token> IGUAL
%token <token> IPARENTESIS DPARENTESIS ILLAVE DLLAVE COMA

%type <identificador> identificador
%type <expresion> numerico expresion 
%type <listaDeclaraciones> func_argumentos
%type <listaExpresiones> inv_argumentos
%type <bloque> programa sentencias bloque
%type <sentencia> sentencia dec_variable dec_funcion

%start programa

%%

programa : sentencias { bloquePrograma = $1; }
        ;
        
sentencias : sentencia { $$ = new Bloque(); $$->statements.push_back($<sentencia>1); }
      | sentencias sentencia { $1->statements.push_back($<sentencia>2); }
      ;

sentencia : dec_variable | dec_funcion
     | expresion { $$ = new ExpresionSentencia(*$1); }
     ;

bloque : ILLAVE sentencias DLLAVE { $$ = $2; }
      | ILLAVE DLLAVE { $$ = new Bloque(); }
      ;

dec_variable : identificador identificador { $$ = new DeclaracionVariable(*$1, *$2); }
         | identificador identificador IGUAL expresion { $$ = new DeclaracionVariable(*$1, *$2, $4); }
         ;
        
dec_funcion : identificador identificador IPARENTESIS func_argumentos DPARENTESIS bloque 
            { $$ = new DeclaracionFuncion(*$1, *$2, *$4, *$6); delete $4; }
          ;
    
func_argumentos : /*blank*/  { $$ = new ListadoDeclaraciones(); }
          | dec_variable { $$ = new ListadoDeclaraciones(); $$->push_back($<dec_variable>1); }
          | func_argumentos COMA dec_variable { $1->push_back($<dec_variable>3); }
          ;

identificador : IDENTIFICADOR { $$ = new Identificador(*$1); delete $1; }
      ;

numerico : ENTERO { $$ = new Entero(atol($1->c_str())); delete $1; }
        | DECIMAL { $$ = new Decimal(atof($1->c_str())); delete $1; }
        ;
    
expresion : identificador IGUAL expresion { $$ = new Asignacion(*$<identificador>1, *$3); }
     | identificador IPARENTESIS inv_argumentos DPARENTESIS { $$ = new InvocacionFuncion(*$1, *$3); delete $3; }
     | identificador { $<identificador>$ = $1; }
     | numerico
     | IPARENTESIS expresion DPARENTESIS { $$ = $2; }
     ;
    
inv_argumentos :   { $$ = new ListadoExpresiones(); }
          | expresion { $$ = new ListadoExpresiones(); $$->push_back($1); }
          | inv_argumentos COMA expresion  { $1->push_back($3); }
          ;

%%
