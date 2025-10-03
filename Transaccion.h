#ifndef TRANSACCION_H
#define TRANSACCION_H
//Transaccion.h
#include <string>

using namespace std;

class Transaccion {
protected:
    string id;
    double monto;
    string fecha;
    string tipo;

public:
    Transaccion(string i, double m, string f, string t)
        : id(i), monto(m), fecha(f), tipo(t) {
    }

    virtual bool ejecutar() = 0;
};

#endif