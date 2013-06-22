#include <typeinfo>

class Bloque;

class ContextoGeneracion {
   std::string codigoGenerado;

public:      
    void generarCodigo(Bloque& root);
    void generarSite();
};
