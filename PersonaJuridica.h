#ifndef PERSONAJURIDICA_H
#define PERSONAJURIDICA_H
// PersonaJuridica.h
#include "Persona.h"

using namespace std;

class PersonaJuridica : public Persona {
private:
    string ruc;
    string razonSocial; // razon social de la empresa

public:
    PersonaJuridica(string i, string n, string a, string e, string r, string razon)
        : Persona(i, n, a, e), ruc(r), razonSocial(razon) {
    }

    bool validar() override {
        auto esValido = [](const string& s) { return s.length() == 11; }; // validar ruc
        return esValido(ruc);
    }

    // getters para acceder a datos especificos
    string getRuc() const { return ruc; }
    string getRazonSocial() const { return razonSocial; }
};

#endif