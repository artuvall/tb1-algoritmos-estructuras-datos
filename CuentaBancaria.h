#ifndef CUENTABANCARIA_H
#define CUENTABANCARIA_H
//CuentaBancaria.h
#include <string>
#include "Transaccion.h"
#include "ListaDoble.h"

using namespace std;

class CuentaBancaria {
protected:
    string numCuenta;
    double saldo;
    string titular;
    string fechaApertura;
    ListaDoble<Transaccion*> historialTransacciones;

public:
    CuentaBancaria(string num, double s, string tit, string fecha)
        : numCuenta(num), saldo(s), titular(tit), fechaApertura(fecha) {
    }

    virtual bool depositar(double monto) = 0;
    virtual bool retirar(double monto) = 0;

    void agregarTransaccion(Transaccion* t) { historialTransacciones.insertarAlInicio(t); }

    double getSaldo() const { return saldo; }

    void ordenarHistorialMerge() { // Mergesort: Integrante 1
        // Nota: Simplifico, en real divide lista y mergea.
    }
};

#endif