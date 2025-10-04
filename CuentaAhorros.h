// CuentaAhorros.h
#ifndef CUENTAAHORROS_H
#define CUENTAAHORROS_H
// =============================================================================
// archivo: cuentaahorros.h
// descripcion: clase derivada de cuentabancaria - cuenta de ahorros
// cumplimiento de rubrica:
//   - entidad #6: hereda de cuentabancaria
//   - lambdas integrante 2: 3 lambdas adicionales (validar limite, calcular interes, promocion)
//   - paradigma poo: herencia, polimorfismo
// =============================================================================

#include "CuentaBancaria.h" // incluye la clase base
#include "Retiro.h"
#include "Deposito.h"
using namespace std;

// clase cuentaahorros: hereda de cuentabancaria
// caracteristicas especiales: genera intereses, tiene limite de retiro diario
class CuentaAhorros : public CuentaBancaria {
private:
    double tasaInteres;         // tasa de interes anual (ej: 0.05 = 5%)
    double limiteRetiroDiario;  // monto maximo que se puede retirar por dia

public:
    // constructor sobrecargado: con limite predeterminado
    CuentaAhorros(string num, double s, string tit, string fecha, double tasa)
        : CuentaBancaria(num, s, tit, fecha), tasaInteres(tasa), limiteRetiroDiario(500.0) {}

    // constructor con limite custom
    CuentaAhorros(string num, double s, string tit, string fecha, double tasa, double limite)
        : CuentaBancaria(num, s, tit, fecha), tasaInteres(tasa), limiteRetiroDiario(limite) {}

    // implementacion del metodo abstracto depositar()
    // complejidad: O(1)
    // polimorfismo: implementacion especifica para cuenta de ahorros
    bool depositar(double monto) override {
        saldo += monto;
        // nota: la transaccion ya viene creada con la fecha correcta desde el sistema
        // no crear una nueva aqui para no perder la fecha aleatoria
        return true;
    }

    // implementacion del metodo abstracto retirar()
    // complejidad: O(1)
    // polimorfismo: incluye validacion de limite diario
    bool retirar(double monto) override {
        // *** lambda #3 integrante 2: validar limite de retiro ***
        // esta lambda verifica que el retiro no exceda el limite diario
        // uso de lambda: captura this por valor para acceder a limiteretirodiario
        // razon: cuentas de ahorro tienen restriccion de retiro diario
        auto dentroLimite = [this](double m) { return m <= limiteRetiroDiario; };

        if (monto <= saldo && dentroLimite(monto)) {
            saldo -= monto;
            // nota: la transaccion ya viene creada con la fecha correcta desde el sistema
            // no crear una nueva aqui para no perder la fecha aleatoria
            return true;
        }
        return false;
    }

    // *** lambda #4 integrante 2: calcular interes diario ***
    // esta lambda calcula el interes generado por el saldo actual
    // formula: interes = saldo * tasa_anual / 360 dias
    // uso de lambda: captura this para acceder a saldo y tasainteres
    // complejidad: O(1)
    // razon: calcular rendimiento diario de la cuenta
    double calcularInteres() {
        auto calcular = [this]() { return saldo * tasaInteres / 360; };
        return calcular();
    }

    // *** lambda #5 integrante 2: verificar elegibilidad para promocion ***
    // esta lambda verifica si el cliente califica para promociones especiales
    // criterios: saldo mayor a 1000 y limite de retiro mayor a 500
    // uso de lambda: captura this para acceder a atributos
    // complejidad: O(1)
    // razon: determinar beneficios adicionales para clientes premium
    bool esElegiblePromocion() {
        auto promocion = [this]() { return saldo > 1000.0 && limiteRetiroDiario > 500.0; };
        return promocion();
    }
};

#endif