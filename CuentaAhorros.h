// CuentaAhorros.h
#ifndef CUENTAAHORROS_H
#define CUENTAAHORROS_H
#include "CuentaBancaria.h" // incluye la clase base
#include "Retiro.h"
#include "Deposito.h"
using namespace std;

class CuentaAhorros : public CuentaBancaria {
private:
    double tasaInteres;
    double limiteRetiroDiario;

public:
    // constructor sobrecargado: con limite predeterminado
    CuentaAhorros(string num, double s, string tit, string fecha, double tasa)
        : CuentaBancaria(num, s, tit, fecha), tasaInteres(tasa), limiteRetiroDiario(500.0) {}

    // constructor con limite custom
    CuentaAhorros(string num, double s, string tit, string fecha, double tasa, double limite)
        : CuentaBancaria(num, s, tit, fecha), tasaInteres(tasa), limiteRetiroDiario(limite) {}

    bool depositar(double monto) override {
        saldo += monto;
        Transaccion* t = new Deposito("DEP-" + numCuenta, monto, "2025-04-05", "Deposito", "Efectivo");
        agregarTransaccion(t);
        return true;
    }

    bool retirar(double monto) override {
        // lambda 1 integrante 2: validar limite de retiro
        auto dentroLimite = [this](double m) { return m <= limiteRetiroDiario; };
        if (monto <= saldo && dentroLimite(monto)) {
            saldo -= monto;
            Transaccion* t = new Retiro("RET-" + numCuenta, monto, "2025-04-05", "Retiro", "Cajero");
            agregarTransaccion(t);
            return true;
        }
        return false;
    }

    double calcularInteres() {
        // lambda 2 integrante 2: calcular interes diario
        auto calcular = [this]() { return saldo * tasaInteres / 360; };
        return calcular();
    }

    // lambda 3 integrante 2: verificar si se puede aplicar promocion
    bool esElegiblePromocion() {
        auto promocion = [this]() { return saldo > 1000.0 && limiteRetiroDiario > 500.0; };
        return promocion();
    }
};

#endif