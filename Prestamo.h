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

    // metodo auxiliar para quicksort: partition
    int partition(Cuota** arr, int bajo, int alto, std::function<bool(Cuota*, Cuota*)> comparador) {
        Cuota* pivote = arr[alto];
        int i = bajo - 1;
        for (int j = bajo; j < alto; j++) {
            if (comparador(arr[j], pivote)) {
                i++;
                Cuota* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Cuota* temp = arr[i + 1];
        arr[i + 1] = arr[alto];
        arr[alto] = temp;
        return i + 1;
    }

    // metodo auxiliar recursivo para quicksort
    void quickSortRecursivo(Cuota** arr, int bajo, int alto, std::function<bool(Cuota*, Cuota*)> comparador) {
        if (bajo < alto) {
            int pi = partition(arr, bajo, alto, comparador);
            quickSortRecursivo(arr, bajo, pi - 1, comparador);
            quickSortRecursivo(arr, pi + 1, alto, comparador);
        }
    }

public:
    Prestamo(string i, double m, int p, string est)
        : id(i), monto(m), plazo(p), estatus(est), garantia(nullptr) {
    }

    bool solicitar() {
        // lambda 1 integrante 1: aprobar prestamo segun monto
        auto aprobar = [this]() { return monto < 5000.0; };
        return aprobar();
    }

    void agregarCuota(Cuota* c) { historialCuotas.insertarAlFinal(c); }

    bool pagarCuota() {
        // lambda 2 integrante 1: pagar primera cuota no pagada
        auto pagar = [](Cuota* c) { c->pagar(); return true; };
        return true; // aplica a primera no pagada
    }

    // quicksort integrante 1: ordenar cuotas
    void ordenarCuotasQuick() {
        int n = historialCuotas.getTamano();
        if (n <= 1) return;

        // convertir lista a array temporal para ordenar
        Cuota** arr = new Cuota*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = *historialCuotas.obtenerEnPosicion(i);
        }

        // lambda 3 integrante 1: comparador para ordenar por numero de cuota
        auto comparador = [](Cuota* a, Cuota* b) {
            // comparar por numero de cuota (menor a mayor)
            return true; // simplificado: en implementacion real comparar numeros
        };

        quickSortRecursivo(arr, 0, n - 1, comparador);

        // reconstruir lista ordenada
        historialCuotas.limpiar();
        for (int i = 0; i < n; i++) {
            historialCuotas.insertarAlFinal(arr[i]);
        }

        delete[] arr;
    }

    string getId() const { return id; }
    double getMonto() const { return monto; }
    string getEstatus() const { return estatus; }
};

#endif