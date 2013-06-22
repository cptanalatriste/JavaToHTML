#include <iostream>
#include "codegen.h"
#include "node.h"


extern Bloque* bloquePrograma;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();
    std::cout << bloquePrograma << std::endl;
    ContextoGeneracion context;
    context.generarCodigo(*bloquePrograma);
    context.generarSite();
    return 0;
}
