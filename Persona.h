#ifndef PERSONA_H
#define PERSONA_H
// Persona.h
#include <string>

using namespace std;

class Persona {
protected:
    string id;
    string nombre;
    string apellido;
    string email;

public:
    Persona(string i = "", string n = "", string a = "", string e = "")
        : id(i), nombre(n), apellido(a), email(e) {
    }

    virtual bool validar() = 0; // Metodo abstracto para polimorfismo.

    string getId() const { return id; }
    string getNombre() const { return nombre; }
};

#endif