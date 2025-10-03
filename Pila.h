#ifndef PILA_H
#define PILA_H
//Pila.h
#include "ListaSimple.h"

using namespace std;

template <typename T>
class Pila {
private:
    ListaSimple<T> listaInterna;

public:
    void push(T dato) { listaInterna.insertarAlFinal(dato); }

    T pop() {
        int ultimo = listaInterna.getTamano() - 1;
        T* ptr = listaInterna.buscar([](T d) { return true; }); // Simpl, usa último.
        if (ptr) {
            T dato = *ptr;
            listaInterna.eliminar(ultimo);
            return dato;
        }
        throw "Pila vacía";
    }

    T top(auto check) { // Lambda 1: Ver cima con condición.
        return *listaInterna.buscar(check);
    }

    void invertir() { // Método custom: Invertir pila.
        Pila<T> temp;
        while (listaInterna.getTamano() > 0) temp.push(pop());
        listaInterna = temp.listaInterna;
    }

    bool buscar(auto pred) { // Lambda 2: Buscar en pila.
        return listaInterna.buscar(pred) != nullptr;
    }

    void vaciarRecursivo(Nodo<T>* nodo) { // Recursividad: Vaciar.
        if (!nodo) return;
        vaciarRecursivo(nodo->siguiente);
        delete nodo;
    }
    void vaciar() {
        vaciarRecursivo(listaInterna.cabeza);
        listaInterna.cabeza = nullptr;
    } // Integrante 4
};

#endif