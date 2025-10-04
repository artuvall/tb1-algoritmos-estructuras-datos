#ifndef LISTADOBLE_H  
#define LISTADOBLE_H  
// ListaDoble.h - Estructura generica con templates
// metodos implementados por integrante 2
// OPTIMIZACION: Mejorada gestion de memoria y comentarios de complejidad
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
    // Constructor: inicializar cabeza, cola y tamaño
    ListaDoble() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    // Destructor: liberar memoria de todos los nodos
    // Complejidad: O(n) - recorre y elimina cada nodo
    ~ListaDoble() {
        NodoDoble<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cabeza = cola = nullptr;  // MEJORA: asegurar punteros nulos
    }

    // Insertar al inicio de la lista
    // Complejidad: O(1) - acceso directo a cabeza
    void insertarAlInicio(T dato) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
        if (!cabeza) {
            // Lista vacia: cabeza y cola apuntan al mismo nodo
            cabeza = cola = nuevo;
        } else {
            // Lista no vacia: insertar antes de cabeza
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
            cabeza = nuevo;
        }
        tamano++;
    }

    // metodo custom 1 integrante 2: insertar al final
    // Complejidad: O(1) - acceso directo a cola
    void insertarAlFinal(T dato) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
        if (!cola) {
            // Lista vacia: cabeza y cola apuntan al mismo nodo
            cabeza = cola = nuevo;
        } else {
            // Lista no vacia: insertar despues de cola
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tamano++;
    }

    // metodo custom 2 integrante 2: eliminar por valor
    // Complejidad: O(n) - debe buscar el elemento en la lista
    bool eliminarPorValor(T valor) {
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            if (temp->dato == valor) {
                // Actualizar puntero anterior
                if (temp->anterior) {
                    temp->anterior->siguiente = temp->siguiente;
                } else {
                    // Es la cabeza
                    cabeza = temp->siguiente;
                }

                // Actualizar puntero siguiente
                if (temp->siguiente) {
                    temp->siguiente->anterior = temp->anterior;
                } else {
                    // Es la cola
                    cola = temp->anterior;
                }

                delete temp;
                tamano--;
                return true;
            }
            temp = temp->siguiente;
        }
        return false;
    }

    // metodo custom 3 integrante 2: obtener en posicion
    // Complejidad: O(n) - recorre hasta la posicion deseada
    T* obtenerEnPosicion(int pos) {
        if (pos < 0 || pos >= tamano) return nullptr;
        NodoDoble<T>* temp = cabeza;
        for (int i = 0; i < pos; i++) {
            temp = temp->siguiente;
        }
        return &(temp->dato);
    }

    // Filtrar elementos con predicado (lambda)
    // Complejidad: O(n) - recorre toda la lista
    ListaDoble<T> filtrar(std::function<bool(T)> filtro) {
        ListaDoble<T> resultado;
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            if (filtro(temp->dato)) resultado.insertarAlFinal(temp->dato);
            temp = temp->siguiente;
        }
        return resultado;
    }

    // Invertir lista completa
    // Complejidad: O(n) - recorre intercambiando punteros
    void invertir() {
        NodoDoble<T>* temp = nullptr;
        NodoDoble<T>* actual = cabeza;
        cola = cabeza;  // el antiguo cabeza sera la nueva cola

        while (actual) {
            temp = actual->anterior;
            actual->anterior = actual->siguiente;
            actual->siguiente = temp;
            actual = actual->anterior;
        }

        if (temp) cabeza = temp->anterior;
    }

    // Aplicar funcion a cada elemento (con lambda)
    // Complejidad: O(n) - recorre toda la lista
    void aplicar(std::function<void(T)> func) {
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            func(temp->dato);
            temp = temp->siguiente;
        }
    }

    // recursividad integrante 2: buscar valor recursivamente
    // Complejidad: O(n) - recorre hasta encontrar o llegar al final
    // Caso base: nodo nulo retorna false (no encontrado)
    // Caso recursivo: si coincide retorna true, sino busca en siguiente
    bool buscarRecursivo(T valor, NodoDoble<T>* nodo) {
        if (!nodo) return false;
        if (nodo->dato == valor) return true;
        return buscarRecursivo(valor, nodo->siguiente);
    }
    bool buscarRecursivo(T valor) { return buscarRecursivo(valor, cabeza); }

    // Getter: obtener tamaño de la lista
    // Complejidad: O(1)
    int getTamano() const { return tamano; }

    // Getters: acceso a cabeza y cola
    NodoDoble<T>* getCabeza() { return cabeza; }
    NodoDoble<T>* getCola() { return cola; }

    // NUEVO: Setters para cabeza y cola (necesarios para optimizaciones)
    void setCabeza(NodoDoble<T>* nuevaCabeza) { cabeza = nuevaCabeza; }
    void setCola(NodoDoble<T>* nuevaCola) { cola = nuevaCola; }
};

#endif