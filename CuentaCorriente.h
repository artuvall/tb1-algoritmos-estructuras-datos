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
        Transaccion* t = new Deposito("DEP-" + numCuenta, monto, "2025-04-05", "Deposito", "Transferencia");
        agregarTransaccion(t);
        return true;
    }

    bool retirar(double monto) override {
        if (monto <= saldo + sobreGiro) {
            saldo -= monto;
            // Crear registro de retiro en el historial
            Transaccion* t = new Retiro("RET-" + numCuenta, monto, "2025-04-05", "Retiro", "Ventanilla");
            agregarTransaccion(t);
            return true;
        }
        return false;
    }
};

#endif