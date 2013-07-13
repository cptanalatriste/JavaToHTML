#include "node.h"
#include "codegen.h"
#include "parser.hpp"
#include <fstream>
#include <iostream>

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
	std::string htmlComoString("<!DOCTYPE HTML>");
	htmlComoString = htmlComoString + "<html lang='en'>";
	htmlComoString = htmlComoString + "<head>";
	htmlComoString = htmlComoString + "<meta charset='utf-8'>";
	htmlComoString = htmlComoString + "<title>";
	htmlComoString = htmlComoString + tituloFormulario;
	htmlComoString = htmlComoString + "</title>";
	htmlComoString = htmlComoString + "<link rel='stylesheet' href='" + hojaEstilos + "' media='screen'>";
	htmlComoString = htmlComoString + "</head>";
	htmlComoString = htmlComoString + "<body>";
	htmlComoString = htmlComoString + "<h1>";
	htmlComoString = htmlComoString + tituloFormulario;
	htmlComoString = htmlComoString + "</h1>";
	htmlComoString = htmlComoString + "<form>";
	std::vector<std::string>::iterator iterator;

	for ( iterator = elementosAgregados.begin(); iterator < elementosAgregados.end(); ++iterator )
	{
		std::cout << "*iterator: " << *iterator << endl;
		ElementoHTML* elemento =elementosGenerados[*iterator];
		std::string elementoComoString = elemento->generarHTML();
		std::cout << "elementoComoString: " << elementoComoString << endl;
		htmlComoString = htmlComoString + elementoComoString;
	}
	htmlComoString = htmlComoString + "</form>";
	htmlComoString = htmlComoString + "</body>";
	htmlComoString = htmlComoString + "</html>";

	std::ofstream archivoSalida("formulario.html");
	archivoSalida << htmlComoString;
	archivoSalida.close();
	std::cout << "Los archivos del Sitio fueron generados.\n";
}

ElementoHTML* Bloque::generarCodigo(ContextoGeneracion& context)
{
	ListadoSentencias::const_iterator it;
	ElementoHTML *last = NULL;
	for (it = statements.begin(); it != statements.end(); it++) {
		std::cout << "Generando código para " << typeid(**it).name() << endl;
		last = (**it).generarCodigo(context);
	}
	std::cout << "Creando bloque" << endl;
	return new Texto("");
}

ElementoHTML* Entero::generarCodigo(ContextoGeneracion& context)
{
	std::cout << "Creando entero: " << value << endl;
	std::string *result = new std::string("");
	return new Texto("");
}

ElementoHTML* Decimal::generarCodigo(ContextoGeneracion& context)
{
	std::cout << "Creando decimal: " << value << endl;
	std::string *result = new std::string("");
	return new Texto("");
}

ElementoHTML* Cadena::generarCodigo(ContextoGeneracion& context)
{
	Texto *result = new Texto(value);
	return  result;
}

ElementoHTML* Identificador::generarCodigo(ContextoGeneracion& context){
    	//TODO: Validar si la variable ha sido declarada.
	std::cout << "Creando referencia a identificador: " << name << endl;
	return new IdentificadorHTML(name);
}

ElementoHTML* InvocacionFuncion::generarCodigo(ContextoGeneracion& context)
{
    	//TODO: Validar que la función haya sido declarada.
	ElementoHTML* result;
	std::cout << "Creando invocación a función: " << id.name << endl;
	
	ListadoExpresiones::const_iterator it;
	std::cout << "arguments.size() "  << arguments.size() << endl;
	if (id.name == "definirTitulo"){
		it = arguments.begin();
		ElementoHTML* elemento = (**it).generarCodigo(context);
		context.setTituloFormulario(elemento->generarHTML());
		std::cout << "Título configurado :"<< elemento->generarHTML() << endl;
	} else if (id.name == "definirHojaDeEstilos"){
		it = arguments.begin();
		ElementoHTML* elemento = (**it).generarCodigo(context);
		context.setHojaEstilos(elemento->generarHTML());
		std::cout << "Hoja de estilos definida : "<< elemento->generarHTML() << endl;
	} else if (id.name == "generarParrafo"){
		it = arguments.begin();
		ElementoHTML* elemento = (**it).generarCodigo(context);
		result = new Parrafo(elemento->generarHTML());
	} else if (id.name == "agregarElemento"){
		it = arguments.begin();
		ElementoHTML* elemento = (**it).generarCodigo(context);
		context.agregarElemento(elemento->generarHTML());
	} else if (id.name == "generarCajaTexto"){
		it = arguments.begin();
		ElementoHTML* elemento = (**it).generarCodigo(context);
		std::string id = elemento->generarHTML();
		it++;
		elemento = (**it).generarCodigo(context);
		std::string etiqueta = elemento->generarHTML();
		result = new CajaTexto(id, etiqueta);
	} else if (id.name == "generarBoton"){
		it = arguments.begin();
		ElementoHTML* elemento = (**it).generarCodigo(context);
		result = new Boton(elemento->generarHTML());
	}
	return result;
}

ElementoHTML* Asignacion::generarCodigo(ContextoGeneracion& context)
{
    	//TODO: Validar si la variable ha sido declarada.
	std::cout << "Creando una asignación para " << lhs.name << endl;
    	ElementoHTML* result = rhs.generarCodigo(context);
	std::cout << "Registrando elemento con el key " << lhs.name << endl;
	context.generarElemento(lhs.name, result);
	return result;
}

ElementoHTML* ExpresionSentencia::generarCodigo(ContextoGeneracion& context)
{
	std::cout << "Generando codigo para " << typeid(expression).name() << endl;
	return expression.generarCodigo(context);
}

ElementoHTML* DeclaracionVariable::generarCodigo(ContextoGeneracion& context)
{
	std::cout << "Creando una declaración de variable para " << type.name << " " << id.name << endl;
	ElementoHTML* result;
	if (assignmentExpr != NULL) {
		Asignacion assn(id, *assignmentExpr);
		result = assn.generarCodigo(context);
		std::cout << "Registrando elemento con el key " << id.name << endl;
		context.generarElemento(id.name, result);
    	}
	return result;
}

ElementoHTML* DeclaracionFuncion::generarCodigo(ContextoGeneracion& context)
{
	std::string *result = new std::string("");
	ListadoDeclaraciones::const_iterator it;
	for (it = arguments.begin(); it != arguments.end(); it++) {
		(**it).generarCodigo(context);
	}
	block.generarCodigo(context);
	std::cout << "Creando función: " << id.name << endl;
	return new Texto("");
}
