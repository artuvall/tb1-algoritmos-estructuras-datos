#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
//ListaSimple.h
#include <iostream>
#include <functional> // A�adido para std::function

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

    T* buscar(std::function<bool(T)> predicado) { // Cambiado a std::function
        Nodo<T>* temp = cabeza;
        while (temp) {
            if (predicado(temp->dato)) return &(temp->dato);
            temp = temp->siguiente;
        }
        return nullptr;
    }

    bool eliminar(int pos) { // Metodo custom: Eliminar por posicion.
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

    void imprimir(std::function<void(T)> formato) { // Cambiado a std::function
        Nodo<T>* temp = cabeza;
        while (temp) {
            formato(temp->dato);
            temp = temp->siguiente;
        }
        cout << endl;
    }

    int getTamano() { return tamano; }

    int contarRecursivo(Nodo<T>* nodo) { // Recursividad: Contar nodos.
        if (!nodo) return 0;
        return 1 + contarRecursivo(nodo->siguiente);
    }
    int contarRecursivo() { return contarRecursivo(cabeza); } // Integrante 1
};

#endif