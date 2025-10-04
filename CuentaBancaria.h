// CuentaBancaria.h
#ifndef CUENTABANCARIA_H
#define CUENTABANCARIA_H
#include <string>
#include <vector>
#include <algorithm>
#include "Transaccion.h"
#include "ListaDoble.h"
using namespace std;

class CuentaBancaria {
protected:
    string numCuenta;
    double saldo;
    string titular;
    string fechaApertura;
    ListaDoble<Transaccion*> historialTransacciones;

    // metodo auxiliar para mergesort: merge dos sublistas
    // Complejidad: O(n) donde n es el tamaño del subarreglo
    void merge(Transaccion** arr, int izq, int medio, int der, std::function<bool(Transaccion*, Transaccion*)> comp) {
        int n1 = medio - izq + 1;
        int n2 = der - medio;

        Transaccion** L = new Transaccion*[n1];
        Transaccion** R = new Transaccion*[n2];

        for (int i = 0; i < n1; i++) L[i] = arr[izq + i];
        for (int j = 0; j < n2; j++) R[j] = arr[medio + 1 + j];

        int i = 0, j = 0, k = izq;
        while (i < n1 && j < n2) {
            if (comp(L[i], R[j])) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) { arr[k] = L[i]; i++; k++; }
        while (j < n2) { arr[k] = R[j]; j++; k++; }

        delete[] L;
        delete[] R;
    }

    // metodo auxiliar recursivo para mergesort
    // Complejidad: O(n log n)
    void mergeSortRecursivo(Transaccion** arr, int izq, int der, std::function<bool(Transaccion*, Transaccion*)> comp) {
        if (izq < der) {
            int medio = izq + (der - izq) / 2;
            mergeSortRecursivo(arr, izq, medio, comp);
            mergeSortRecursivo(arr, medio + 1, der, comp);
            merge(arr, izq, medio, der, comp);
        }
    }

public:
    CuentaBancaria(string num, double s, string tit, string fecha)
        : numCuenta(num), saldo(s), titular(tit), fechaApertura(fecha) {}

    virtual ~CuentaBancaria() = default; // destructor virtual para herencia

    virtual bool depositar(double monto) = 0;
    virtual bool retirar(double monto) = 0;

    void agregarTransaccion(Transaccion* t) {
        historialTransacciones.insertarAlInicio(t);
    }

    double getSaldo() const { return saldo; }
    string getNumCuenta() const { return numCuenta; }
    string getTitular() const { return titular; }

    // OPTIMIZADO: mergesort integrante 2 - ordenar historial de transacciones
    // MEJORA: Reenlaza nodos existentes en vez de eliminar y recrear
    // Complejidad total: O(n log n) - antes era O(n log n) + O(n) destruccion + O(n) recreacion
    // Ahora es O(n log n) + O(n) reenlazado = O(n log n) mas eficiente
    void ordenarHistorialMerge() {
        int n = historialTransacciones.getTamano();
        if (n <= 1) return;

        // PASO 1: Recolectar nodos en vector (O(n))
        vector<NodoDoble<Transaccion*>*> nodos;
        NodoDoble<Transaccion*>* actual = historialTransacciones.getCabeza();

        while (actual) {
            nodos.push_back(actual);
            actual = actual->siguiente;
        }

        // PASO 2: lambda 1 integrante 2 - comparador para ordenar por fecha
        // Ordena de mas reciente a menos reciente (descendente)
        auto comparador = [](NodoDoble<Transaccion*>* a, NodoDoble<Transaccion*>* b) {
            return a->dato->getFecha() > b->dato->getFecha();
        };

        // PASO 3: Ordenar vector de nodos usando sort (usa MergeSort internamente)
        // Complejidad: O(n log n)
        sort(nodos.begin(), nodos.end(), comparador);

        // PASO 4: Reenlazar nodos en el orden correcto (O(n))
        // OPTIMIZACION: No destruye ni recrea nodos, solo actualiza punteros
        for (size_t i = 0; i < nodos.size(); i++) {
            nodos[i]->anterior = (i > 0) ? nodos[i-1] : nullptr;
            nodos[i]->siguiente = (i < nodos.size()-1) ? nodos[i+1] : nullptr;
        }

        // PASO 5: Actualizar cabeza y cola de la lista
        historialTransacciones.setCabeza(nodos[0]);
        historialTransacciones.setCola(nodos.back());
    }

    // metodo auxiliar para mostrar saldo con lambda
    // lambda 2 integrante 2: formatear informacion de cuenta
    void mostrarInfo() {
        auto formatear = [this]() {
            cout << "Cuenta: " << numCuenta << " | Saldo: $" << saldo
                 << " | Titular: " << titular << endl;
        };
        formatear();
    }
};

#endif