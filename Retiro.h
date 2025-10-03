// Retiro.h
#ifndef RETIRO_H
#define RETIRO_H

#include "Transaccion.h"
#include <string>

using namespace std;

class Retiro : public Transaccion {
private:
    string canal; // ej: "Cajero", "Ventanilla", "App"

public:
    // constructor: hereda id, monto, fecha, tipo; añade canal
    Retiro(string i, double m, string f, string t, string can)
        : Transaccion(i, m, f, t), canal(can) {}

    // implementación de ejecutar() para retiro
    bool ejecutar() override {
        // Lambda 1: Validar monto positivo. Integrante 3
        auto montoValido = [](double m) { return m > 0; };
        if (!montoValido(monto)) {
            cout << "Error: Monto de retiro debe ser mayor a 0.\n";
            return false;
        }

        // Lambda 2: Validar canal permitido. Integrante 3
        auto canalValido = [this]() {
            return (canal == "Cajero" || canal == "Ventanilla" || canal == "App");
        };
        if (!canalValido()) {
            cout << "Error: Canal de retiro no válido.\n";
            return false;
        }

        // Lambda 3: Confirmar ejecución. Integrante 3
        auto confirmar = [this]() {
            cout << "Retiro exitoso: ID=" << id << ", Monto=" << monto
                 << ", Canal=" << canal << endl;
        };
        confirmar();

        return true;
    }

    // getter para el canal (para reportes o validacion)
    string getCanal() const { return canal; }
};

#endif