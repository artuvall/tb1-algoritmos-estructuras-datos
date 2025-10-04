#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
// ListaSimple.h - Estructura generica con templates
// metodos implementados por integrante 1
// OPTIMIZACION: Agregado puntero a cola para O(1) en insertarAlFinal()
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
    Nodo<T>* cola;  // NUEVO: puntero a cola para optimizacion O(1)
    int tamano;

public:
    // Constructor: inicializar cabeza y cola
    ListaSimple() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    // Destructor: liberar memoria de todos los nodos
    ~ListaSimple() {
        Nodo<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cabeza = cola = nullptr;  // MEJORA: asegurar que cola tambien sea nullptr
    }

    // OPTIMIZADO: Complejidad mejorada de O(n) a O(1)
    // Ahora usa puntero directo a cola en vez de recorrer toda la lista
    void insertarAlFinal(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (!cabeza) {
            // Lista vacia: cabeza y cola apuntan al mismo nodo
            cabeza = cola = nuevo;
        } else {
            // Lista no vacia: agregar al final usando puntero cola
            cola->siguiente = nuevo;
            cola = nuevo;  // actualizar puntero cola
        }
        tamano++;
    }

    // metodo custom 1 integrante 1: insertar al inicio
    // Complejidad: O(1)
    void insertarAlInicio(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;

        // MEJORA: actualizar cola si lista estaba vacia
        if (!cola) {
            cola = nuevo;
        }

        tamano++;
    }

    // Buscar elemento con predicado (lambda)
    // Complejidad: O(n) - recorre hasta encontrar o llegar al final
    T* buscar(std::function<bool(T)> predicado) {
        Nodo<T>* temp = cabeza;
        while (temp) {
            if (predicado(temp->dato)) return &(temp->dato);
            temp = temp->siguiente;
        }
        return nullptr;
    }

    // Eliminar nodo en posicion especifica
    // Complejidad: O(n) - necesita recorrer hasta la posicion
    bool eliminar(int pos) {
        if (pos < 0 || pos >= tamano) return false;

        Nodo<T>* temp = cabeza;
        if (pos == 0) {
            // Eliminar primer nodo
            cabeza = cabeza->siguiente;

            // MEJORA: actualizar cola si la lista queda vacia
            if (!cabeza) {
                cola = nullptr;
            }

            delete temp;
        }
        else {
            // Eliminar nodo intermedio o final
            for (int i = 0; i < pos - 1; i++) temp = temp->siguiente;
            Nodo<T>* aEliminar = temp->siguiente;
            temp->siguiente = aEliminar->siguiente;

            // MEJORA: actualizar cola si eliminamos el ultimo nodo
            if (aEliminar == cola) {
                cola = temp;
            }

            delete aEliminar;
        }
        tamano--;
        return true;
    }

    // metodo custom 2 integrante 1: obtener elemento en posicion
    // Complejidad: O(n) - recorre hasta la posicion deseada
    T* obtenerEnPosicion(int pos) const {
        if (pos < 0 || pos >= tamano) return nullptr;
        Nodo<T>* temp = cabeza;
        for (int i = 0; i < pos; i++) {
            temp = temp->siguiente;
        }
        return &(temp->dato);
    }

    // metodo custom 3 integrante 1: invertir lista
    // Complejidad: O(n) - recorre una vez invirtiendo punteros
    void invertir() {
        if (!cabeza || !cabeza->siguiente) return;

        // MEJORA: actualizar puntero cola antes de invertir
        cola = cabeza;

        Nodo<T>* anterior = nullptr;
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;

        while (actual) {
            siguiente = actual->siguiente;
            actual->siguiente = anterior;
            anterior = actual;
            actual = siguiente;
        }

        cabeza = anterior;  // nuevo cabeza es el antiguo ultimo nodo
    }

    // Aplicar funcion a cada elemento (con lambda)
    // Complejidad: O(n)
    void imprimir(std::function<void(T)> formato) {
        Nodo<T>* temp = cabeza;
        while (temp) {
            formato(temp->dato);
            temp = temp->siguiente;
        }
    }

    // Getter: obtener tamaño de la lista
    // Complejidad: O(1)
    int getTamano() const { return tamano; }

    // metodo auxiliar para obtener cabeza (necesario para pila y otras estructuras)
    Nodo<T>* getCabeza() { return cabeza; }

    // metodo auxiliar para obtener cola
    Nodo<T>* getCola() { return cola; }

    // metodo auxiliar para establecer cabeza (necesario para pila)
    void setCabeza(Nodo<T>* nuevaCabeza) { cabeza = nuevaCabeza; }

    // NUEVO: metodo auxiliar para establecer cola
    void setCola(Nodo<T>* nuevaCola) { cola = nuevaCola; }

    // recursividad integrante 1: contar nodos recursivamente
    // Complejidad: O(n) - recorre todos los nodos
    // Caso base: nodo nulo retorna 0
    // Caso recursivo: 1 + contar resto de la lista
    int contarRecursivo(Nodo<T>* nodo) {
        if (!nodo) return 0;
        return 1 + contarRecursivo(nodo->siguiente);
    }
    int contarRecursivo() { return contarRecursivo(cabeza); }

    // metodo auxiliar para limpiar sin destruir
    // MEJORADO: Actualiza cola tambien
    // Complejidad: O(n)
    void limpiar() {
        Nodo<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cabeza = cola = nullptr;  // MEJORA: asegurar que cola tambien sea nullptr
        tamano = 0;
    }
};

#endif