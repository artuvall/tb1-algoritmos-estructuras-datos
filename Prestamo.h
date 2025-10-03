#ifndef PRESTAMO_H
#define PRESTAMO_H
//Prestamo.h
#include "Cuota.h"
#include "Garantia.h"
#include "ListaSimple.h"

using namespace std;

class Prestamo {
private:
    string id;
    double monto;
    int plazo;
    string estatus;
    ListaSimple<Cuota*> historialCuotas;
    Garantia* garantia;

public:
    Prestamo(string i, double m, int p, string est)
        : id(i), monto(m), plazo(p), estatus(est), garantia(nullptr) {
    }

    bool solicitar() {
        auto aprobar = [this]() { return monto < 5000.0; }; // Lambda 3: Aprobación.
        return aprobar();
    }

    void agregarCuota(Cuota* c) { historialCuotas.insertarAlFinal(c); }

    bool pagarCuota() {
        auto pagar = [](Cuota* c) { c->pagar(); return true; }; // Lambda 3: Pago.
        return true; // Aplica a primera no pagada.
    }

    void ordenarCuotasQuick() { // Quicksort: Integrante 2
        // Nota: Partition y recursión, O(n log n) promedio.
    }
};

#endif