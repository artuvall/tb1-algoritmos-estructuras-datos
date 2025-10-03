#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
// ListaSimple.h - Estructura generica con templates
// metodos implementados por integrante 1
#include <iostream>
#include <functional>

using namespace std;

template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(T d) : dato(d), siguiente(nullptr) {}
};

template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;
    int tamano;

public:
    ListaSimple() : cabeza(nullptr), tamano(0) {}
    ~ListaSimple() {
        Nodo<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void insertarAlFinal(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (!cabeza) cabeza = nuevo;
        else {
            Nodo<T>* temp = cabeza;
            while (temp->siguiente) temp = temp->siguiente;
            temp->siguiente = nuevo;
        }
        tamano++;
    }

    // metodo custom 1 integrante 1: insertar al inicio
    void insertarAlInicio(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        tamano++;
    }

    T* buscar(std::function<bool(T)> predicado) {
        Nodo<T>* temp = cabeza;
        while (temp) {
            if (predicado(temp->dato)) return &(temp->dato);
            temp = temp->siguiente;
        }
        return nullptr;
    }

    bool eliminar(int pos) {
        if (pos < 0 || pos >= tamano) return false;
        Nodo<T>* temp = cabeza;
        if (pos == 0) {
            cabeza = cabeza->siguiente;
            delete temp;
        }
        else {
            for (int i = 0; i < pos - 1; i++) temp = temp->siguiente;
            Nodo<T>* aEliminar = temp->siguiente;
            temp->siguiente = aEliminar->siguiente;
            delete aEliminar;
        }
        tamano--;
        return true;
    }

    // metodo custom 2 integrante 1: obtener elemento en posicion
    T* obtenerEnPosicion(int pos) const {
        if (pos < 0 || pos >= tamano) return nullptr;
        Nodo<T>* temp = cabeza;
        for (int i = 0; i < pos; i++) {
            temp = temp->siguiente;
        }
        return &(temp->dato);
    }

    // metodo custom 3 integrante 1: invertir lista
    void invertir() {
        if (!cabeza || !cabeza->siguiente) return;
        Nodo<T>* anterior = nullptr;
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while (actual) {
            siguiente = actual->siguiente;
            actual->siguiente = anterior;
            anterior = actual;
            actual = siguiente;
        }
        cabeza = anterior;
    }

    void imprimir(std::function<void(T)> formato) {
        Nodo<T>* temp = cabeza;
        while (temp) {
            formato(temp->dato);
            temp = temp->siguiente;
        }
    }

    int getTamano() const { return tamano; }

    // metodo auxiliar para obtener cabeza (necesario para pila)
    Nodo<T>* getCabeza() { return cabeza; }

    // metodo auxiliar para establecer cabeza (necesario para pila)
    void setCabeza(Nodo<T>* nuevaCabeza) { cabeza = nuevaCabeza; }

    // recursividad integrante 1: contar nodos recursivamente
    int contarRecursivo(Nodo<T>* nodo) {
        if (!nodo) return 0;
        return 1 + contarRecursivo(nodo->siguiente);
    }
    int contarRecursivo() { return contarRecursivo(cabeza); }

    // metodo auxiliar para limpiar sin destruir
    void limpiar() {
        Nodo<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        tamano = 0;
    }
};

#endif