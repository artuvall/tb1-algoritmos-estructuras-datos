#ifndef LISTADOBLE_H  
#define LISTADOBLE_H  
// ListaDoble.h - Estructura generica con templates
// metodos implementados por integrante 2
#include <iostream>
#include <functional>

using namespace std;

template <typename T>
struct NodoDoble {
    T dato;
    NodoDoble* siguiente;
    NodoDoble* anterior;
    NodoDoble(T d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* cabeza;
    NodoDoble<T>* cola;
    int tamano;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr), tamano(0) {}
    ~ListaDoble() {
        NodoDoble<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void insertarAlInicio(T dato) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
        if (!cabeza) cabeza = cola = nuevo;
        else {
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
            cabeza = nuevo;
        }
        tamano++;
    }

    // metodo custom 1 integrante 2: insertar al final
    void insertarAlFinal(T dato) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
        if (!cola) cabeza = cola = nuevo;
        else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tamano++;
    }

    // metodo custom 2 integrante 2: eliminar por valor
    bool eliminarPorValor(T valor) {
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            if (temp->dato == valor) {
                if (temp->anterior) temp->anterior->siguiente = temp->siguiente;
                else cabeza = temp->siguiente;
                if (temp->siguiente) temp->siguiente->anterior = temp->anterior;
                else cola = temp->anterior;
                delete temp;
                tamano--;
                return true;
            }
            temp = temp->siguiente;
        }
        return false;
    }

    // metodo custom 3 integrante 2: obtener en posicion
    T* obtenerEnPosicion(int pos) {
        if (pos < 0 || pos >= tamano) return nullptr;
        NodoDoble<T>* temp = cabeza;
        for (int i = 0; i < pos; i++) {
            temp = temp->siguiente;
        }
        return &(temp->dato);
    }

    ListaDoble<T> filtrar(std::function<bool(T)> filtro) {
        ListaDoble<T> resultado;
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            if (filtro(temp->dato)) resultado.insertarAlFinal(temp->dato);
            temp = temp->siguiente;
        }
        return resultado;
    }

    void invertir() {
        NodoDoble<T>* temp = nullptr;
        NodoDoble<T>* actual = cabeza;
        cola = cabeza;
        while (actual) {
            temp = actual->anterior;
            actual->anterior = actual->siguiente;
            actual->siguiente = temp;
            actual = actual->anterior;
        }
        if (temp) cabeza = temp->anterior;
    }

    void aplicar(std::function<void(T)> func) {
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            func(temp->dato);
            temp = temp->siguiente;
        }
    }

    // recursividad integrante 2: buscar valor recursivamente
    bool buscarRecursivo(T valor, NodoDoble<T>* nodo) {
        if (!nodo) return false;
        if (nodo->dato == valor) return true;
        return buscarRecursivo(valor, nodo->siguiente);
    }
    bool buscarRecursivo(T valor) { return buscarRecursivo(valor, cabeza); }

    int getTamano() const { return tamano; }

    NodoDoble<T>* getCabeza() { return cabeza; }
    NodoDoble<T>* getCola() { return cola; }
};

#endif