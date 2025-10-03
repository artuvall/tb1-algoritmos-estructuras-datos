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

    // destructor virtual para evitar problemas con delete
    virtual ~Transaccion() {}

    // metodos virtuales puros
    virtual bool ejecutar() = 0;

    // getters publicos para acceder a los datos
    string getId() const { return id; }
    double getMonto() const { return monto; }
    string getFecha() const { return fecha; }
    string getTipo() const { return tipo; }
};

#endif