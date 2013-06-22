#include "node.h"
#include "codegen.h"
#include "parser.hpp"

using namespace std;

void ContextoGeneracion::generarCodigo(Bloque& root)
{
	std::cout << "Generando código...\n";
	root.generarCodigo(*this);
	std::cout << "El código se ha generado.\n";

}

void ContextoGeneracion::generarSite()
{
	std::cout << "Generando archivos ...\n";
	std::cout << "Los archivos del Sitio fueron generados.\n";
}

std::string* Bloque::generarCodigo(ContextoGeneracion& context)
{
	ListadoSentencias::const_iterator it;
	std::string *last = NULL;
	for (it = statements.begin(); it != statements.end(); it++) {
		std::cout << "Generando código para " << typeid(**it).name() << endl;
		last = (**it).generarCodigo(context);
	}
	std::cout << "Creando bloque" << endl;
	return last;
}

std::string* Entero::generarCodigo(ContextoGeneracion& context)
{
	std::cout << "Creando entero: " << value << endl;
	std::string *result = new std::string("");
	return result;
}

std::string* Identificador::generarCodigo(ContextoGeneracion& context)
{
	std::string *result = new std::string("");
	return result;
}

std::string* InvocacionFuncion::generarCodigo(ContextoGeneracion& context)
{
	std::string *result = new std::string("");
	std::cout << "Creating invocación a función: " << id.name << endl;
	return result;
}

std::string* Asignacion::generarCodigo(ContextoGeneracion& context)
{
	std::string *result = new std::string("");
	return result;
}

std::string* ExpresionSentencia::generarCodigo(ContextoGeneracion& context)
{
	std::cout << "Generando codigo para " << typeid(expression).name() << endl;
	return expression.generarCodigo(context);
}

std::string* DeclaracionVariable::generarCodigo(ContextoGeneracion& context)
{
	std::string *result = new std::string("");
	return result;
}

std::string* DeclaracionFuncion::generarCodigo(ContextoGeneracion& context)
{
	std::string *result = new std::string("");
	ListadoDeclaraciones::const_iterator it;
	for (it = arguments.begin(); it != arguments.end(); it++) {
		(**it).generarCodigo(context);
	}
	block.generarCodigo(context);
	std::cout << "Creando función: " << id.name << endl;
	return result;
}
