#ifndef PERSONANATURAL_H
#define PERSONANATURAL_H
// =============================================================================
// archivo: personanatural.h
// descripcion: clase derivada de persona - representa persona natural
// cumplimiento de rubrica:
//   - entidad #2: hereda de persona (clase base)
//   - uso de lambda integrante 3: validacion de dni
//   - paradigma poo: herencia, polimorfismo
// =============================================================================

// PersonaNatural.h
#include "Persona.h"

using namespace std;

// clase personanatural: hereda de persona
// representa personas individuales (con dni)
class PersonaNatural : public Persona {
private:
    // atributos especificos de persona natural
    string dni;
    string fechaNac;

public:
    // constructor: llama al constructor de la clase base
    PersonaNatural(string i, string n, string a, string e, string d, string f)
        : Persona(i, n, a, e), dni(d), fechaNac(f) {
    }

    // implementacion del metodo abstracto validar() de la clase base
    // demuestra polimorfismo: cada tipo de persona valida de forma diferente
    bool validar() override {
        // *** lambda integrante 3 para validacion ***
        // esta lambda verifica que el dni tenga al menos 8 caracteres
        // uso de lambda: captura por valor, recibe string por referencia
        // retorna bool indicando si es valido
        auto esValido = [](const string& s) { return s.length() >= 8; };

        // validar tanto dni como fecha de nacimiento
        return esValido(dni) && esValido(fechaNac);
    }

    // getters para acceder a los datos especificos
    // encapsulamiento: acceso controlado a atributos privados
    string getDni() const { return dni; }
    string getFechaNac() const { return fechaNac; }
};

#endif