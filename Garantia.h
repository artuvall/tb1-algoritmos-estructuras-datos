#ifndef GARANTIA_H
#define GARANTIA_H
//Garantia.h
#include <string>

using namespace std;

class Garantia {
private:
    string tipo;
    double valor;

public:
    Garantia(string t, double v) : tipo(t), valor(v) {}

    void adjuntar() { /* Asociar a prestamo. */ }
};

#endif