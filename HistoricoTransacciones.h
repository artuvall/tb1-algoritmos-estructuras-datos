#ifndef HISTORICOTRANSACCIONES_H
#define HISTORICOTRANSACCIONES_H

#include "ListaDoble.h"
#include "Transaccion.h"
#include <iostream>
#include <iomanip> // para setprecision
// HistoricoTransacciones.h
using namespace std;

class HistoricoTransacciones {
private:
    ListaDoble<Transaccion*> lista;

public:
    void agregar(Transaccion* t) { lista.insertarAlInicio(t); }

    // shellsort integrante 4: ordenar transacciones por monto
    void ordenarShell() {
        int n = lista.getTamano();
        if (n <= 1) return;

        // convertir lista a array temporal
        Transaccion** arr = new Transaccion*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = *lista.obtenerEnPosicion(i);
        }

        // lambda 1 integrante 4: comparador para ordenar por monto
        auto comparador = [](Transaccion* a, Transaccion* b) {
            // comparar por monto (menor a mayor)
            return a->getMonto() < b->getMonto();
        };

        // shellsort con gaps decrecientes
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                Transaccion* temp = arr[i];
                int j;
                // lambda 2 integrante 4: verificar si necesita intercambio
                auto necesitaIntercambio = [&comparador](Transaccion* a, Transaccion* b) {
                    return comparador(b, a);
                };

                for (j = i; j >= gap && necesitaIntercambio(arr[j - gap], temp); j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }

        // reconstruir lista ordenada
        while (lista.getTamano() > 0) {
            lista.eliminarPorValor(*lista.obtenerEnPosicion(0));
        }

        for (int i = 0; i < n; i++) {
            lista.insertarAlFinal(arr[i]);
        }

        delete[] arr;
    }

    // lambda 3 integrante 4: filtrar transacciones por monto minimo
    ListaDoble<Transaccion*> filtrarPorMonto(double montoMin) {
        auto filtro = [montoMin](Transaccion* t) {
            return t->getMonto() >= montoMin;
        };
        return lista.filtrar(filtro);
    }

    // metodo para imprimir historial con detalles completos
    void imprimir() {
        cout << "\n=== HISTORIAL DE TRANSACCIONES ===\n";
        auto imprimirTransaccion = [](Transaccion* t) {
            // mostrar informacion detallada de cada transaccion
            cout << "ID: " << t->getId()
                 << " | Tipo: " << t->getTipo()
                 << " | Monto: S/ " << fixed << setprecision(2) << t->getMonto()
                 << " | Fecha: " << t->getFecha() << "\n";
        };
        lista.aplicar(imprimirTransaccion);
    }

    int getTamano() { return lista.getTamano(); }
};

#endif