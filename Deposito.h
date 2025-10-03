#ifndef DEPOSITO_H
#define DEPOSITO_H
//Deposito.h
#include "Transaccion.h"

using namespace std;

class Deposito : public Transaccion {
private:
    string metodo;

public:
    Deposito(string i, double m, string f, string t, string met)
        : Transaccion(i, m, f, t), metodo(met) {
    }

    bool ejecutar() override { return true; } // Simula deposito.
};

#endif