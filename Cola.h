#ifndef COLA_H
#define COLA_H
// Cola.h - Estructura de cola generica con templates
// metodos implementados por integrante 3
#include "ListaSimple.h"

using namespace std;

template <typename T>
class Cola {
private:
    ListaSimple<T> listaInterna;

public:
    void encolar(T dato) {
        listaInterna.insertarAlFinal(dato); // encolar al final O(n)
    }

    T desencolar() {
        if (listaInterna.getTamano() == 0) throw "cola vacia";
        T* ptr = listaInterna.obtenerEnPosicion(0);
        if (ptr) {
            T dato = *ptr;
            listaInterna.eliminar(0);
            return dato;
        }
        throw "cola vacia";
    }

    T frente() {
        if (listaInterna.getTamano() == 0) throw "cola vacia";
        T* ptr = listaInterna.obtenerEnPosicion(0);
        if (ptr) return *ptr;
        throw "cola vacia";
    }

    // metodo custom 1 integrante 3: buscar elemento con lambda
    T* buscar(std::function<bool(T)> predicado) {
        return listaInterna.buscar(predicado);
    }

    // metodo custom 2 integrante 3: vaciar cola
    void vaciar() {
        while (listaInterna.getTamano() > 0) {
            listaInterna.eliminar(0);
        }
    }

    // metodo custom 3 integrante 3: contar elementos que cumplen condicion
    int contar(std::function<bool(T)> condicion) {
        int count = 0;
        auto contador = [&count, condicion](T dato) {
            if (condicion(dato)) count++;
        };
        listaInterna.imprimir(contador);
        return count;
    }

    // recursividad integrante 3: tamano recursivo
    int tamanoRecursivo() {
        return listaInterna.contarRecursivo();
    }

    int getTamano() { return listaInterna.getTamano(); }

    bool estaVacia() { return listaInterna.getTamano() == 0; }
};

#endif