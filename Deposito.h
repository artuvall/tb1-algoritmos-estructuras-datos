// Deposito.h
#ifndef DEPOSITO_H
#define DEPOSITO_H
// =============================================================================
// archivo: deposito.h
// descripcion: clase derivada de transaccion - representa deposito
// cumplimiento de rubrica:
//   - entidad #9: hereda de transaccion
//   - lambdas integrante 3: 3 lambdas para validacion y confirmacion
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
    bool ejecutar() override {
        // *** lambda #1 integrante 3: validar monto positivo ***
        // esta lambda verifica que el deposito sea mayor a 0
        // uso de lambda: captura por valor, retorna bool
        // razon: no tiene sentido depositar monto negativo o cero
        auto montoValido = [](double m) { return m > 0; };
        if (!montoValido(monto)) {
            cout << "Error: Monto de deposito debe ser mayor a 0.\n";
            return false;
        }

        // *** lambda #2 integrante 3: validar metodo de deposito ***
        // esta lambda verifica que el metodo sea uno de los permitidos
        // uso de lambda: captura this por valor para acceder a metodo
        // razon: solo ciertos metodos de deposito son aceptados por el banco
        auto metodoValido = [this]() {
            return (metodo == "Efectivo" || metodo == "Transferencia" || metodo == "Cheque");
        };
        if (!metodoValido()) {
            cout << "Error: Metodo de deposito no valido.\n";
            return false;
        }

        // *** lambda #3 integrante 3: confirmar ejecucion exitosa ***
        // esta lambda muestra mensaje de confirmacion al usuario
        // uso de lambda: captura this por valor para acceder a atributos
        // razon: feedback al usuario sobre operacion exitosa
        auto confirmar = [this]() {
            cout << "Deposito exitoso: ID=" << id << ", Monto=" << monto
                 << ", Metodo=" << metodo << endl;
        };
        confirmar();

        return true;
    }
};

#endif