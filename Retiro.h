// Retiro.h
#ifndef RETIRO_H
#define RETIRO_H
// =============================================================================
// archivo: retiro.h
// descripcion: clase derivada de transaccion - representa retiro
// cumplimiento de rubrica:
//   - entidad #10: hereda de transaccion
//   - lambdas integrante 3: 3 lambdas para validacion y confirmacion
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
    bool ejecutar() override {
        // *** lambda #1 integrante 3: validar monto positivo ***
        // esta lambda verifica que el retiro sea mayor a 0
        // uso de lambda: captura por valor, retorna bool
        // razon: no tiene sentido retirar monto negativo o cero
        auto montoValido = [](double m) { return m > 0; };
        if (!montoValido(monto)) {
            cout << "Error: Monto de retiro debe ser mayor a 0.\n";
            return false;
        }

        // *** lambda #2 integrante 3: validar canal de retiro ***
        // esta lambda verifica que el canal sea uno de los permitidos
        // uso de lambda: captura this por valor para acceder a canal
        // razon: solo ciertos canales de retiro estan habilitados
        auto canalValido = [this]() {
            return (canal == "Cajero" || canal == "Ventanilla" || canal == "App");
        };
        if (!canalValido()) {
            cout << "Error: Canal de retiro no valido.\n";
            return false;
        }

        // *** lambda #3 integrante 3: confirmar ejecucion exitosa ***
        // esta lambda muestra mensaje de confirmacion al usuario
        // uso de lambda: captura this por valor para acceder a atributos
        // razon: feedback al usuario sobre operacion exitosa
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