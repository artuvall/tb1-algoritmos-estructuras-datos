#ifndef PERSONAJURIDICA_H
#define PERSONAJURIDICA_H
// PersonaJuridica.h
#include "Persona.h"

using namespace std;

class PersonaJuridica : public Persona {
private:
    string ruc;
    string representante;

public:
    PersonaJuridica(string i, string n, string a, string e, string r, string rep)
        : Persona(i, n, a, e), ruc(r), representante(rep) {
    }

    bool validar() override {
        auto esValido = [](const string& s) { return s.length() == 11; }; // Para RUC.
        return esValido(ruc);
    }
};

#endif