#ifndef LISTADOBLE_H  
#define LISTADOBLE_H  
//ListaDoble.h  
#include <iostream>  
#include <functional> // Anadido para std::function

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

    ListaDoble<T> filtrar(std::function<bool(T)> filtro) { // Cambiado a std::function
        ListaDoble<T> resultado;
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            if (filtro(temp->dato)) resultado.insertarAlInicio(temp->dato);
            temp = temp->siguiente;
        }
        return resultado;
    }

    void invertir() { // M�todo custom: Invertir lista.  
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

    void aplicar(std::function<void(T)> func) { // Cambiado a std::function
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            func(temp->dato);
            temp = temp->siguiente;
        }
    }

    bool buscarRecursivo(T valor, NodoDoble<T>* nodo) { // Recursividad: Buscar.  
        if (!nodo) return false;
        if (nodo->dato == valor) return true;
        return buscarRecursivo(valor, nodo->siguiente);
    }
    bool buscarRecursivo(T valor) { return buscarRecursivo(valor, cabeza); } // Integrante 2  
};

#endif