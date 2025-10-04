#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H
//CuentaCorriente.h
#include "CuentaBancaria.h"
#include "Retiro.h"
#include "Deposito.h"
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
        // nota: la transaccion ya viene creada con la fecha correcta desde el sistema
        // no crear una nueva aqui para no perder la fecha aleatoria
        return true;
    }

    bool retirar(double monto) override {
        if (monto <= saldo + sobreGiro) {
            saldo -= monto;
            // nota: la transaccion ya viene creada con la fecha correcta desde el sistema
            // no crear una nueva aqui para no perder la fecha aleatoria
            return true;
        }
        return false;
    }
};

#endif