#ifndef HISTORICOTRANSACCIONES_H
#define HISTORICOTRANSACCIONES_H

#include "ListaDoble.h"
#include "Transaccion.h"
// HistoricoTransacciones.h
using namespace std;

class HistoricoTransacciones {
private:
    ListaDoble<Transaccion*> lista;

public:
    void agregar(Transaccion* t) { lista.insertarAlInicio(t); }

    void ordenarShell() { // Shellsort: Integrante 4, O(n log n).
        // Nota: Gaps decrecientes, insercion por gaps.
    }
};

#endif