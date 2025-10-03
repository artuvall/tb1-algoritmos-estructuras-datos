#ifndef PILA_H
#define PILA_H
// Pila.h - Estructura de pila generica con templates
// metodos implementados por integrante 4
#include "ListaSimple.h"

using namespace std;

template <typename T>
class Pila {
private:
    ListaSimple<T> listaInterna;

public:
    void push(T dato) {
        listaInterna.insertarAlInicio(dato); // insertar al inicio para push O(1)
    }

    T pop() {
        if (listaInterna.getTamano() == 0) throw "pila vacia";
        T* ptr = listaInterna.obtenerEnPosicion(0);
        if (ptr) {
            T dato = *ptr;
            listaInterna.eliminar(0);
            return dato;
        }
        throw "pila vacia";
    }

    T top() {
        if (listaInterna.getTamano() == 0) throw "pila vacia";
        T* ptr = listaInterna.obtenerEnPosicion(0);
        if (ptr) return *ptr;
        throw "pila vacia";
    }

    // metodo custom 1 integrante 4: buscar elemento con lambda
    bool buscar(std::function<bool(T)> predicado) {
        return listaInterna.buscar(predicado) != nullptr;
    }

    // metodo custom 2 integrante 4: invertir pila
    void invertir() {
        listaInterna.invertir();
    }

    // metodo custom 3 integrante 4: contar elementos que cumplen condicion
    int contarSi(std::function<bool(T)> condicion) {
        int count = 0;
        auto contador = [&count, condicion](T dato) {
            if (condicion(dato)) count++;
        };
        listaInterna.imprimir(contador);
        return count;
    }

    // recursividad integrante 4: vaciar pila recursivamente
    void vaciarRecursivoAux(Nodo<T>* nodo) {
        if (!nodo) return;
        vaciarRecursivoAux(nodo->siguiente);
        delete nodo;
    }

    void vaciarRecursivo() {
        vaciarRecursivoAux(listaInterna.getCabeza());
        listaInterna.setCabeza(nullptr);
    }

    int getTamano() { return listaInterna.getTamano(); }

    bool estaVacia() { return listaInterna.getTamano() == 0; }
};

#endif