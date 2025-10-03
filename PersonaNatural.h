#ifndef PERSONANATURAL_H
#define PERSONANATURAL_H
// PersonaNatural.h
#include "Persona.h"

using namespace std;

class PersonaNatural : public Persona {
private:
    string dni;
    string fechaNac;

public:
    PersonaNatural(string i, string n, string a, string e, string d, string f)
        : Persona(i, n, a, e), dni(d), fechaNac(f) {
    }

    bool validar() override {
        auto esValido = [](const string& s) { return s.length() >= 8; }; // lambda 3: validar dni
        return esValido(dni) && esValido(fechaNac);
    }

    // getters para acceder a los datos especificos
    string getDni() const { return dni; }
    string getFechaNac() const { return fechaNac; }
};

#endif