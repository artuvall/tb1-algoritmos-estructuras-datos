#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H
// =============================================================================
// archivo: cuentacorriente.h
// descripcion: clase derivada de cuentabancaria - cuenta corriente
// cumplimiento de rubrica:
//   - entidad #7: hereda de cuentabancaria
//   - paradigma poo: herencia, polimorfismo
//   - caracteristica especial: permite sobregiro (saldo negativo hasta limite)
// =============================================================================

//CuentaCorriente.h
#include "CuentaBancaria.h"
#include "Retiro.h"
#include "Deposito.h"
using namespace std;

// clase cuentacorriente: hereda de cuentabancaria
// caracteristica especial: permite sobregiro (linea de credito)
// permite tener saldo negativo hasta cierto limite
class CuentaCorriente : public CuentaBancaria {
private:
    double sobreGiro;  // monto maximo de sobregiro permitido

public:
    // constructor: inicializa con datos de cuenta y limite de sobregiro
    CuentaCorriente(string num, double s, string tit, string fecha, double sg)
        : CuentaBancaria(num, s, tit, fecha), sobreGiro(sg) {
    }

    // implementacion del metodo abstracto depositar()
    // complejidad: O(1)
    // polimorfismo: implementacion simple para cuenta corriente
    bool depositar(double monto) override {
        saldo += monto;
        // nota: la transaccion ya viene creada con la fecha correcta desde el sistema
        // no crear una nueva aqui para no perder la fecha aleatoria
        return true;
    }

    // implementacion del metodo abstracto retirar()
    // complejidad: O(1)
    // polimorfismo: permite sobregiro (diferencia con cuentaahorros)
    // puede retirar aunque saldo sea menor al monto, si tiene sobregiro disponible
    bool retirar(double monto) override {
        // validar que monto no exceda (saldo + sobregiro disponible)
        // ejemplo: si saldo = 100 y sobregiro = 500, puede retirar hasta 600
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