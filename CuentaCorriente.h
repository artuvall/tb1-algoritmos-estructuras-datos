#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H
//CuentaCorriente.h
#include "CuentaBancaria.h"

using namespace std;

class CuentaCorriente : public CuentaBancaria {
private:
    double sobreGiro;

public:
    CuentaCorriente(string num, double s, string tit, string fecha, double sg)
        : CuentaBancaria(num, s, tit, fecha), sobreGiro(sg) {
    }

    bool depositar(double monto) override {
        saldo += monto;
        return true;
    }

    bool retirar(double monto) override {
        if (monto <= saldo + sobreGiro) {
            saldo -= monto;
            return true;
        }
        return false;
    }
};

#endif