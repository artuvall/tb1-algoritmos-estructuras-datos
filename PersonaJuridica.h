#ifndef PERSONAJURIDICA_H
#define PERSONAJURIDICA_H
// =============================================================================
// archivo: personajuridica.h
// descripcion: clase derivada de persona - representa persona juridica (empresa)
// cumplimiento de rubrica:
//   - entidad #3: hereda de persona (clase base)
//   - uso de lambda integrante 3: validacion de ruc
//   - paradigma poo: herencia, polimorfismo
// =============================================================================

// PersonaJuridica.h
#include "Persona.h"

using namespace std;

// clase personajuridica: hereda de persona
// representa empresas u organizaciones (con ruc)
class PersonaJuridica : public Persona {
private:
    // atributos especificos de persona juridica
    string ruc;           // registro unico de contribuyentes (11 digitos)
    string razonSocial;   // nombre legal de la empresa

public:
    // constructor: llama al constructor de la clase base
    PersonaJuridica(string i, string n, string a, string e, string r, string razon)
        : Persona(i, n, a, e), ruc(r), razonSocial(razon) {
    }

    // implementacion del metodo abstracto validar() de la clase base
    // demuestra polimorfismo: validacion diferente a personanatural
    bool validar() override {
        // *** lambda integrante 3 para validacion de ruc ***
        // esta lambda verifica que el ruc tenga exactamente 11 caracteres
        // en peru, el ruc de empresas siempre tiene 11 digitos
        // uso de lambda: captura por valor, recibe string por referencia
        auto esValido = [](const string& s) { return s.length() == 11; };

        return esValido(ruc);
    }

    // getters para acceder a datos especificos
    // encapsulamiento: acceso controlado a atributos privados
    string getRuc() const { return ruc; }
    string getRazonSocial() const { return razonSocial; }
};

#endif