#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
// =============================================================================
// archivo: listasimple.h
// descripcion: estructura de datos lista enlazada simple generica
// cumplimiento de rubrica:
//   - estructura de datos #1 (integrante 1): lista enlazada simple
//   - uso de templates: estructura generica <T>
//   - metodos personalizados: insertaralinicio, obtenerenposicion, invertir
//   - recursividad integrante 1: contarrecursivo
//   - optimizacion critica: puntero cola para insertar al final en O(1)
//   - uso de lambdas: en buscar() e imprimir()
// =============================================================================

// ListaSimple.h - Estructura generica con templates
// metodos implementados por integrante 1
// OPTIMIZACION: Agregado puntero a cola para O(1) en insertarAlFinal()
#include <iostream>
#include <functional>

using namespace std;

// nodo simple: estructura basica para lista enlazada simple
// solo tiene puntero al siguiente (unidireccional)
template <typename T>
struct Nodo {
    T dato;              // dato almacenado (puede ser cualquier tipo)
    Nodo* siguiente;     // puntero al siguiente nodo

    // constructor: inicializa dato y siguiente en null
    Nodo(T d) : dato(d), siguiente(nullptr) {}
};

// *** estructura de datos integrante 1: lista enlazada simple ***
// implementacion generica usando templates (cumple requisito de programacion generica)
template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;     // puntero al primer nodo
    Nodo<T>* cola;       // *** optimizacion: puntero al ultimo nodo para O(1) ***
    int tamano;          // contador de elementos

public:
    // constructor: inicializa lista vacia
    // complejidad: O(1)
    ListaSimple() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    // destructor: liberar memoria de todos los nodos
    // complejidad: O(n) - debe recorrer y eliminar cada nodo
    // importante para evitar memory leaks
    ~ListaSimple() {
        Nodo<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cabeza = cola = nullptr;
    }

    // *** metodo optimizado - cambio critico de O(n) a O(1) ***
    // antes: recorria toda la lista hasta el final (O(n))
    // ahora: usa puntero directo a cola (O(1))
    // justificacion: operacion muy frecuente en el sistema
    // analisis de complejidad: O(1) constante
    void insertarAlFinal(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (!cabeza) {
            // lista vacia: cabeza y cola apuntan al mismo nodo
            cabeza = cola = nuevo;
        } else {
            // lista no vacia: agregar al final usando puntero cola
            cola->siguiente = nuevo;
            cola = nuevo;  // actualizar puntero cola en O(1)
        }
        tamano++;
    }

    // *** metodo personalizado #1 integrante 1: insertar al inicio ***
    // complejidad: O(1) - solo actualiza punteros, no recorre lista
    // es O(1) porque:
    //   1. crear nodo nuevo: O(1)
    //   2. asignar siguiente = cabeza: O(1)
    //   3. actualizar cabeza: O(1)
    // total: O(1) + O(1) + O(1) = O(1)
    void insertarAlInicio(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;

        // actualizar cola si lista estaba vacia
        if (!cola) {
            cola = nuevo;
        }

        tamano++;
    }

    // buscar elemento con predicado (lambda)
    // complejidad: O(n) - peor caso recorre toda la lista
    // parametro: funcion lambda que define criterio de busqueda
    // retorna: puntero al dato encontrado o nullptr
    T* buscar(std::function<bool(T)> predicado) {
        Nodo<T>* temp = cabeza;
        while (temp) {
            if (predicado(temp->dato)) return &(temp->dato);
            temp = temp->siguiente;
        }
        return nullptr;
    }

    // eliminar nodo en posicion especifica
    // complejidad: O(n) - necesita recorrer hasta la posicion
    // actualiza puntero cola si se elimina el ultimo elemento
    bool eliminar(int pos) {
        if (pos < 0 || pos >= tamano) return false;

        Nodo<T>* temp = cabeza;
        if (pos == 0) {
            // eliminar primer nodo
            cabeza = cabeza->siguiente;

            // actualizar cola si la lista queda vacia
            if (!cabeza) {
                cola = nullptr;
            }

            delete temp;
        }
        else {
            // eliminar nodo intermedio o final
            for (int i = 0; i < pos - 1; i++) temp = temp->siguiente;
            Nodo<T>* aEliminar = temp->siguiente;
            temp->siguiente = aEliminar->siguiente;

            // actualizar cola si eliminamos el ultimo nodo
            if (aEliminar == cola) {
                cola = temp;
            }

            delete aEliminar;
        }
        tamano--;
        return true;
    }

    // *** metodo personalizado #2 integrante 1: obtener elemento en posicion ***
    // complejidad: O(n) - recorre hasta la posicion deseada
    // es O(n) porque en peor caso (pos = n-1) recorre n-1 nodos
    // no se puede optimizar mas en lista enlazada simple (no hay acceso directo)
    T* obtenerEnPosicion(int pos) const {
        if (pos < 0 || pos >= tamano) return nullptr;
        Nodo<T>* temp = cabeza;
        for (int i = 0; i < pos; i++) {
            temp = temp->siguiente;
        }
        return &(temp->dato);
    }

    // *** metodo personalizado #3 integrante 1: invertir lista ***
    // complejidad: O(n) - recorre una vez invirtiendo punteros
    // algoritmo: invierte direccion de todos los punteros siguientes
    // es O(n) porque:
    //   - recorre cada nodo exactamente una vez
    //   - por cada nodo hace operaciones O(1)
    //   - total: n * O(1) = O(n)
    void invertir() {
        if (!cabeza || !cabeza->siguiente) return;

        // actualizar puntero cola antes de invertir
        cola = cabeza;

        Nodo<T>* anterior = nullptr;
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;

        // invertir punteros uno por uno
        while (actual) {
            siguiente = actual->siguiente;     // guardar siguiente
            actual->siguiente = anterior;      // invertir puntero
            anterior = actual;                 // avanzar anterior
            actual = siguiente;                // avanzar actual
        }

        cabeza = anterior;  // nuevo cabeza es el antiguo ultimo nodo
    }

    // aplicar funcion a cada elemento (con lambda)
    // complejidad: O(n) - recorre toda la lista
    // permite aplicar cualquier operacion a cada elemento via lambda
    void imprimir(std::function<void(T)> formato) {
        Nodo<T>* temp = cabeza;
        while (temp) {
            formato(temp->dato);
            temp = temp->siguiente;
        }
    }

    // getter: obtener tamaño de la lista
    // complejidad: O(1) - retorna variable miembro
    int getTamano() const { return tamano; }

    // metodos auxiliares para obtener/establecer cabeza y cola
    // necesarios para estructuras que usan listasimple internamente (pila, cola)
    Nodo<T>* getCabeza() { return cabeza; }
    Nodo<T>* getCola() { return cola; }
    void setCabeza(Nodo<T>* nuevaCabeza) { cabeza = nuevaCabeza; }
    void setCola(Nodo<T>* nuevaCola) { cola = nuevaCola; }

    // *** recursividad integrante 1: contar nodos recursivamente ***
    // complejidad: O(n) - recorre todos los nodos
    // caso base: nodo nulo retorna 0 (fin de lista)
    // caso recursivo: 1 (nodo actual) + contar resto de la lista
    // formula: T(n) = 1 + T(n-1), caso base: T(0) = 0
    // solucion: T(n) = n, por lo tanto O(n)
    int contarRecursivo(Nodo<T>* nodo) {
        if (!nodo) return 0;  // caso base
        return 1 + contarRecursivo(nodo->siguiente);  // caso recursivo
    }

    // version publica: inicia recursion desde cabeza
    int contarRecursivo() { return contarRecursivo(cabeza); }

    // metodo auxiliar para limpiar sin destruir objeto
    // complejidad: O(n)
    void limpiar() {
        Nodo<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cabeza = cola = nullptr;
        tamano = 0;
    }
};

#endif