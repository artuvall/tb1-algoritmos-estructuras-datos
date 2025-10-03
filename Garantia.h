#ifndef GARANTIA_H
#define GARANTIA_H
//Garantia.h
#include <string>
#include <iostream>

using namespace std;

class Garantia {
private:
    string tipo; // vehiculo, inmueble, aval, etc.
    double valor;

public:
    Garantia(string t, double v) : tipo(t), valor(v) {}

    // getters para acceder a los datos
    string getTipo() const { return tipo; }
    double getValor() const { return valor; }

    void mostrarInfo() const {
        cout << "Tipo: " << tipo << " | Valor: S/ " << valor;
    }
};

#endif