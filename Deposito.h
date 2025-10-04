// Deposito.h
#ifndef DEPOSITO_H
#define DEPOSITO_H
// =============================================================================
// archivo: deposito.h
// descripcion: clase derivada de transaccion - representa deposito
// cumplimiento de rubrica:
//   - entidad #9: hereda de transaccion
//   - lambda integrante 3 (#1): validacion de monto con lambda
//   - paradigma poo: herencia, polimorfismo
// =============================================================================

#include "Transaccion.h"
using namespace std;

// clase deposito: hereda de transaccion
// representa entrada de dinero a una cuenta bancaria
class Deposito : public Transaccion {
private:
    string metodo; // forma de deposito: "efectivo", "transferencia", "cheque"

public:
    // constructor: llama al constructor de la clase base
    Deposito(string i, double m, string f, string t, string met)
        : Transaccion(i, m, f, t), metodo(met) {}

    // implementacion del metodo abstracto ejecutar()
    // demuestra polimorfismo: cada transaccion ejecuta de forma diferente
    // este metodo ahora es llamado por sistemafinanciero::procesarsiguientetransaccion()
    bool ejecutar() override {
        // *** lambda #1 integrante 3: validar monto positivo ***
        // esta lambda verifica que el deposito sea mayor a 0
        // uso de lambda: captura por valor [m], retorna bool
        // razon: validacion critica - no tiene sentido depositar monto negativo o cero
        // complejidad: o(1) - comparacion simple
        auto montoValido = [](double m) { return m > 0; };

        if (!montoValido(monto)) {
            cout << "error: monto de deposito debe ser mayor a 0.\n";
            return false;
        }

        cout << "deposito validado: id=" << id << ", monto=" << monto
             << ", metodo=" << metodo << endl;

        return true;
    }
};

#endif