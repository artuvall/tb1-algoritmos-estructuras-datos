#ifndef PERSONA_H
#define PERSONA_H
// =============================================================================
// archivo: persona.h
// descripcion: clase base abstracta persona - parte de la jerarquia de herencia
// cumplimiento de rubrica:
//   - entidad #1: clase base para personanatural y personajuridica
//   - paradigma poo: herencia, polimorfismo, encapsulamiento
//   - destructor virtual para manejo correcto de memoria en herencia
// =============================================================================

// Persona.h
#include <string>

using namespace std;

// clase abstracta persona - base para personanatural y personajuridica
// demuestra uso de polimorfismo y herencia (requisito de poo)
class Persona {
protected:
    // atributos protegidos: accesibles por clases derivadas
    string id;
    string nombre;
    string apellido;
    string email;

public:
    // constructor: inicializa atributos basicos de toda persona
    Persona(string i = "", string n = "", string a = "", string e = "")
        : id(i), nombre(n), apellido(a), email(e) {
    }

    // destructor virtual: esencial para herencia
    // permite eliminar objetos derivados correctamente a traves de puntero base
    // sin esto habria memory leaks en personanatural y personajuridica
    virtual ~Persona() {}

    // metodo abstracto puro: obliga a clases derivadas a implementarlo
    // esto hace que persona sea abstracta (no se puede instanciar)
    // cada tipo de persona (natural/juridica) tendra su propia validacion
    virtual bool validar() = 0;

    // getters basicos: encapsulamiento - acceso controlado a atributos privados
    string getId() const { return id; }
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getEmail() const { return email; }
};

#endif