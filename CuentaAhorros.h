// CuentaAhorros.h
#ifndef CUENTAAHORROS_H
#define CUENTAAHORROS_H
#include "CuentaBancaria.h" // incluye la clase base
using namespace std;

class CuentaAhorros : public CuentaBancaria {
private:
    double tasaInteres;
    double limiteRetiroDiario;

public:
    CuentaAhorros(string num, double s, string tit, string fecha, double tasa, double limite)
        : CuentaBancaria(num, s, tit, fecha), tasaInteres(tasa), limiteRetiroDiario(limite) {}

    bool depositar(double monto) override {
        saldo += monto;
        Transaccion* t = new Deposito("DEP-" + numCuenta, monto, "2025-04-05", "Deposito", "Efectivo");
        agregarTransaccion(t);
        return true;
    }

    bool retirar(double monto) override {
        // Lambda 1: Validar limite de retiro. Integrante 2
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
        // Lambda 2: Calcular interes diario. Integrante 2
        auto calcular = [this]() { return saldo * tasaInteres / 360; };
        return calcular();
    }

    // Lambda 3: Verificar si se puede aplicar promocion. Integrante 2
    bool esElegiblePromocion() {
        auto promocion = [this]() { return saldo > 1000.0 && limiteRetiroDiario > 500.0; };
        return promocion();
    }
};

#endif