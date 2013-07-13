#include <typeinfo>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>


class Bloque;
class ElementoHTML;

class ContextoGeneracion {
   std::string tituloFormulario;
   std::string hojaEstilos;
   std::map<std::string, ElementoHTML *> elementosGenerados;
   std::vector<std::string> elementosAgregados;

public:      
    void generarCodigo(Bloque& root);
    void generarSite();
    void setTituloFormulario(std::string titulo) {
	tituloFormulario =  titulo;
    };
    void setHojaEstilos(std::string hoja) {
	hojaEstilos =  hoja;
    };
    void generarElemento(std::string nombre, ElementoHTML *elementoHTML) {
	elementosGenerados[nombre] = elementoHTML;
    };
    void agregarElemento(std::string nombre) {
	elementosAgregados.push_back(nombre);
    };
};

class ElementoHTML {
public:
    ElementoHTML() {}
    virtual std::string generarHTML() {
	return "Implementación Base";
    }
};

class IdentificadorHTML : public ElementoHTML {
public:
    std::string texto;
    IdentificadorHTML(const std::string& texto) : texto(texto) { }
    std::string generarHTML(){
	return texto;
    }
};

class Texto : public ElementoHTML {
public:
    std::string texto;
    Texto(const std::string& texto) : texto(texto) { }
    std::string generarHTML(){
	std::cout << "Generamos HTML para el texto: "<< texto << std::endl;
	return texto.substr(1, texto.size()-2);
    }
};

class Parrafo : public ElementoHTML {
public:
    std::string texto;
    std::string estilo;
    Parrafo(const std::string& texto) : texto(texto) { }
    Parrafo(const std::string& texto, const std::string& estilo) :
        texto(texto), estilo(estilo) { }
    std::string generarHTML(){
	std::cout << "Generamos HTML para el párrafo: "<< texto << std::endl;
	std::string htmlComoString("<p>");
	htmlComoString = htmlComoString + texto;
	htmlComoString = htmlComoString + "</p>";
	return htmlComoString;
    }
};

class CajaTexto : public ElementoHTML {
public:
    std::string id;
    std::string etiqueta;
    CajaTexto(const std::string& id, const std::string& etiqueta) :
        id(id), etiqueta(etiqueta) { }
    std::string generarHTML(){
	std::cout << "Generamos HTML para la caja de texto: "<< id << std::endl;
	std::string htmlComoString("<div>");
	htmlComoString = htmlComoString + "<label for='" + id +"'>";
	htmlComoString = htmlComoString + etiqueta;
	htmlComoString = htmlComoString + "</label>";
	htmlComoString = htmlComoString + "<input type='text' name='" + id +"' id='" + id +"' value=''/>";
	htmlComoString = htmlComoString + "</div>";
	return htmlComoString;
    }
};

class Boton : public ElementoHTML {
public:
    std::string texto;
    Boton(const std::string& texto) : texto(texto) { }
    std::string generarHTML(){
	std::cout << "Generamos HTML para el botón: "<< texto << std::endl;
	std::string htmlComoString("<input type='submit' value='"+ texto +"' />");	
	return htmlComoString;    
    }
};

