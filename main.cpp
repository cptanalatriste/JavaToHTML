#include <iostream>
#include "node.h"
extern Bloque* bloquePrograma;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();
    std::cout << bloquePrograma << std::endl;
    return 0;
}
