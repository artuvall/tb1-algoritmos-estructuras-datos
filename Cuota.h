#ifndef CUOTA_H
#define CUOTA_H
//Cuota.h
#include <string>
#include <iostream>

using namespace std;

class Cuota {
private:
    int num;
    double monto;
    string fechaVenc;
    bool pagado;

public:
    Cuota(int n, double m, string f, bool p = false)
        : num(n), monto(m), fechaVenc(f), pagado(p) {
    }

    bool pagar() {
        if (pagado) {
            cout << "Esta cuota ya fue pagada.\n";
            return false;
        }
        pagado = true;
        cout << "Cuota #" << num << " pagada exitosamente.\n";
        return true;
    }

    // getters para acceder a los datos
    int getNum() const { return num; }
    double getMonto() const { return monto; }
    string getFechaVenc() const { return fechaVenc; }
    bool isPagado() const { return pagado; }

    void mostrarInfo() const {
        cout << "Cuota #" << num << " | Monto: S/ " << monto
             << " | Vence: " << fechaVenc
             << " | Estado: " << (pagado ? "PAGADA" : "PENDIENTE") << "\n";
    }
};

#endif