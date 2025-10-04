#ifndef CUOTA_H
#define CUOTA_H
// =============================================================================
// archivo: cuota.h
// descripcion: entidad cuota - representa pago mensual de prestamo
// cumplimiento de rubrica:
//   - entidad #12: parte del sistema de prestamos
//   - encapsulamiento: atributos privados con getters
// =============================================================================

//Cuota.h
#include <string>
#include <iostream>

using namespace std;

// clase cuota: representa un pago mensual de un prestamo
// cada prestamo tiene multiples cuotas (una por mes)
class Cuota {
private:
    int num;              // numero de cuota (1, 2, 3, ...)
    double monto;         // monto a pagar en esta cuota
    string fechaVenc;     // fecha de vencimiento (MM/YYYY)
    bool pagado;          // estado: true si ya fue pagada

public:
    // constructor: inicializa cuota con numero, monto y fecha
    // por defecto no esta pagada
    Cuota(int n, double m, string f, bool p = false)
        : num(n), monto(m), fechaVenc(f), pagado(p) {
    }

    // marcar cuota como pagada
    // complejidad: O(1)
    // retorna false si ya estaba pagada
    bool pagar() {
        if (pagado) {
            cout << "Esta cuota ya fue pagada.\n";
            return false;
        }
        pagado = true;
        cout << "Cuota #" << num << " pagada exitosamente.\n";
        return true;
    }

    // getters para acceder a los datos: encapsulamiento
    int getNum() const { return num; }
    double getMonto() const { return monto; }
    string getFechaVenc() const { return fechaVenc; }
    bool isPagado() const { return pagado; }

    // mostrar informacion de la cuota
    void mostrarInfo() const {
        cout << "Cuota #" << num << " | Monto: S/ " << monto
             << " | Vence: " << fechaVenc
             << " | Estado: " << (pagado ? "PAGADA" : "PENDIENTE") << "\n";
    }
};

#endif