// Deposito.h
#ifndef DEPOSITO_H
#define DEPOSITO_H
#include "Transaccion.h"
using namespace std;

class Deposito : public Transaccion {
private:
    string metodo; // "Efectivo", "Transferencia", etc.

public:
    Deposito(string i, double m, string f, string t, string met)
        : Transaccion(i, m, f, t), metodo(met) {}

    bool ejecutar() override {
        // Lambda 1: Validar monto. Integrante 3
        auto montoValido = [](double m) { return m > 0; };
        if (!montoValido(monto)) {
            cout << "Error: Monto de depósito debe ser mayor a 0.\n";
            return false;
        }

        // Lambda 2: Validar metodo. Integrante 3
        auto metodoValido = [this]() {
            return (metodo == "Efectivo" || metodo == "Transferencia" || metodo == "Cheque");
        };
        if (!metodoValido()) {
            cout << "Error: Método de depósito no válido.\n";
            return false;
        }

        // Lambda 3: Confirmar deposito. Integrante 3
        auto confirmar = [this]() {
            cout << "Depósito exitoso: ID=" << id << ", Monto=" << monto
                 << ", Método=" << metodo << endl;
        };
        confirmar();

        return true;
    }
};

#endif