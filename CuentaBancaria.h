// CuentaBancaria.h
#ifndef CUENTABANCARIA_H
#define CUENTABANCARIA_H
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
        : numCuenta(num), saldo(s), titular(tit), fechaApertura(fecha) {}

    virtual ~CuentaBancaria() = default; // Destructor virtual para herencia

    virtual bool depositar(double monto) = 0;
    virtual bool retirar(double monto) = 0;

    void agregarTransaccion(Transaccion* t) {
        historialTransacciones.insertarAlInicio(t);
    }

    double getSaldo() const { return saldo; }
    string getNumCuenta() const { return numCuenta; }

    // Metodo para ordenar historial con Merge Sort (Integrante 2)
    void ordenarHistorialMerge(); // Nota: Simplifico, en real divide lista y mergea.
};

#endif