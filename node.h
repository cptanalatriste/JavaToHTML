#include <iostream>
#include <vector>

class Sentencia;
class Expresion;
class DeclaracionVariable;

typedef std::vector<Sentencia*> ListadoSentencias;
typedef std::vector<Expresion*> ListadoExpresiones;
typedef std::vector<DeclaracionVariable*> ListadoDeclaraciones;

class Nodo {
public:
    virtual ~Nodo() {}
};

class Expresion : public Nodo {
};

class Sentencia : public Nodo {
};

class Entero : public Expresion {
public:
    long long value;
    Entero(long long value) : value(value) { }
};

class Decimal : public Expresion {
public:
    double value;
    Decimal(double value) : value(value) { }
};

class Identificador : public Expresion {
public:
    std::string name;
    Identificador(const std::string& name) : name(name) { }
};

class InvocacionFuncion : public Expresion {
public:
    const Identificador& id;
    ListadoExpresiones arguments;
    InvocacionFuncion(const Identificador& id, ListadoExpresiones& arguments) :
        id(id), arguments(arguments) { }
    InvocacionFuncion(const Identificador& id) : id(id) { }
};

class Asignacion : public Expresion {
public:
    Identificador& lhs;
    Expresion& rhs;
    Asignacion(Identificador& lhs, Expresion& rhs) : 
        lhs(lhs), rhs(rhs) { }
};

class Bloque : public Expresion {
public:
    ListadoSentencias statements;
    Bloque() { }
};

class ExpresionSentencia : public Sentencia {
public:
    Expresion& expression;
    ExpresionSentencia(Expresion& expression) : 
        expression(expression) { }
};

class DeclaracionVariable : public Sentencia {
public:
    const Identificador& type;
    Identificador& id;
    Expresion *assignmentExpr;
    DeclaracionVariable(const Identificador& type, Identificador& id) :
        type(type), id(id) { }
    DeclaracionVariable(const Identificador& type, Identificador& id, Expresion *assignmentExpr) :
        type(type), id(id), assignmentExpr(assignmentExpr) { }
};

class DeclaracionFuncion : public Sentencia {
public:
    const Identificador& type;
    const Identificador& id;
    ListadoDeclaraciones arguments;
    Bloque& block;
    DeclaracionFuncion(const Identificador& type, const Identificador& id, 
            const ListadoDeclaraciones& arguments, Bloque& block) :
        type(type), id(id), arguments(arguments), block(block) { }
};
