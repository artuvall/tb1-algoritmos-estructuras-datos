// CuentaBancaria.h
#ifndef CUENTABANCARIA_H
#define CUENTABANCARIA_H
#include <string>
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

    // mergesort integrante 2: ordenar historial de transacciones
    void ordenarHistorialMerge() {
        int n = historialTransacciones.getTamano();
        if (n <= 1) return;

        // convertir lista a array temporal
        Transaccion** arr = new Transaccion*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = *historialTransacciones.obtenerEnPosicion(i);
        }

        // lambda 1 integrante 2: comparador para ordenar por fecha
        auto comparador = [](Transaccion* a, Transaccion* b) {
            // comparar por fecha (mas reciente primero)
            // asumiendo formato DD/MM/AAAA, ordenar de forma descendente
            return a->getFecha() > b->getFecha();
        };

        mergeSortRecursivo(arr, 0, n - 1, comparador);

        // reconstruir lista ordenada
        NodoDoble<Transaccion*>* temp = historialTransacciones.getCabeza();
        while (temp) {
            NodoDoble<Transaccion*>* sig = temp->siguiente;
            delete temp;
            temp = sig;
        }

        // reinsertar ordenado
        for (int i = n - 1; i >= 0; i--) {
            historialTransacciones.insertarAlInicio(arr[i]);
        }

        delete[] arr;
    }

    // metodo auxiliar para mostrar saldo con lambda
    void mostrarInfo() {
        // lambda 2 integrante 2: formatear informacion de cuenta
        auto formatear = [this]() {
            cout << "Cuenta: " << numCuenta << " | Saldo: $" << saldo
                 << " | Titular: " << titular << endl;
        };
        formatear();
    }
};

#endif