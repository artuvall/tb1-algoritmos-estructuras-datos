// Retiro.h
#ifndef RETIRO_H
#define RETIRO_H
// =============================================================================
// archivo: retiro.h
// descripcion: clase derivada de transaccion - representa retiro
// cumplimiento de rubrica:
//   - entidad #10: hereda de transaccion
//   - lambda integrante 3 (#2): validacion de monto con lambda
//   - paradigma poo: herencia, polimorfismo
// =============================================================================

#include "Transaccion.h"
#include <string>

using namespace std;

// clase retiro: hereda de transaccion
// representa salida de dinero de una cuenta bancaria
class Retiro : public Transaccion {
private:
    string canal; // canal de retiro: "cajero", "ventanilla", "app"

public:
    // constructor: hereda id, monto, fecha, tipo; añade canal
    Retiro(string i, double m, string f, string t, string can)
        : Transaccion(i, m, f, t), canal(can) {}

    // implementacion de ejecutar() para retiro
    // demuestra polimorfismo: validaciones diferentes a deposito
    // este metodo ahora es llamado por sistemafinanciero::procesarsiguientetransaccion()
    bool ejecutar() override {
        // *** lambda #2 integrante 3: validar monto positivo ***
        // esta lambda verifica que el retiro sea mayor a 0
        // uso de lambda: captura por valor [m], retorna bool
        // razon: validacion critica - no tiene sentido retirar monto negativo o cero
        // complejidad: o(1) - comparacion simple
        auto montoValido = [](double m) { return m > 0; };

        if (!montoValido(monto)) {
            cout << "error: monto de retiro debe ser mayor a 0.\n";
            return false;
        }

        cout << "retiro validado: id=" << id << ", monto=" << monto
             << ", canal=" << canal << endl;

        return true;
    }
};

#endif