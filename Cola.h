#ifndef COLA_H
#define COLA_H
// Cola.h
#include "ListaSimple.h"

using namespace std;

template <typename T>
class Cola {
private:
    ListaSimple<T> listaInterna;

public:
    void encolar(T dato) { listaInterna.insertarAlFinal(dato); }

    T desencolar() {
        T* ptr = listaInterna.buscar([](T d) { return true; }); // Dummy para primer elemento.
        if (ptr) {
            T dato = *ptr;
            listaInterna.eliminar(0);
            return dato;
        }
        throw "Cola vacía";
    }

    T peek(auto check) { // Lambda 1: Ver elemento con condición.
        T* ptr = listaInterna.buscar(check);
        if (ptr) return *ptr;
        throw "No encontrado";
    }

    void vaciar() { // Método custom: Vaciar cola.
        while (listaInterna.getTamano() > 0) listaInterna.eliminar(0);
    }

    int contar(auto cond) { // Lambda 2: Contar con condición.
        int count = 0;
        auto counter = [&count, cond](T d) { if (cond(d)) count++; };
        listaInterna.imprimir(counter);
        return count;
    }

    int tamanoRecursivo() { return listaInterna.contarRecursivo(); } // Recursividad: Integrante 3
};

#endif