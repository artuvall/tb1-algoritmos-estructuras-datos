#ifndef LISTADOBLE_H  
#define LISTADOBLE_H  
// =============================================================================
// archivo: listadoble.h
// descripcion: estructura de datos lista doblemente enlazada generica
// cumplimiento de rubrica:
//   - estructura de datos #2 (integrante 2): lista doblemente enlazada
//   - uso de templates: estructura generica <T>
//   - metodos personalizados: insertaralfinal, eliminarporvalor, obtenerenposicion
//   - recursividad integrante 2: buscarrecursivo
//   - navegacion bidireccional: punteros siguiente y anterior
// =============================================================================

// ListaDoble.h - Estructura generica con templates
// metodos implementados por integrante 2
// OPTIMIZACION: Mejorada gestion de memoria y comentarios de complejidad
#include <iostream>
#include <functional>

using namespace std;

// nodo doble: estructura para lista doblemente enlazada
// tiene punteros al siguiente y al anterior (bidireccional)
template <typename T>
struct NodoDoble {
    T dato;                    // dato almacenado (tipo generico)
    NodoDoble* siguiente;      // puntero al siguiente nodo
    NodoDoble* anterior;       // puntero al nodo anterior (diferencia clave con nodo simple)

    // constructor: inicializa dato y punteros en null
    NodoDoble(T d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

// *** estructura de datos integrante 2: lista doblemente enlazada ***
// implementacion generica usando templates (cumple requisito de programacion generica)
// ventaja sobre lista simple: permite recorrer en ambas direcciones
template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* cabeza;     // puntero al primer nodo
    NodoDoble<T>* cola;       // puntero al ultimo nodo
    int tamano;               // contador de elementos

public:
    // constructor: inicializa lista vacia
    // complejidad: O(1)
    ListaDoble() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    // destructor: liberar memoria de todos los nodos
    // complejidad: O(n) - recorre y elimina cada nodo
    // importante para evitar memory leaks
    ~ListaDoble() {
        NodoDoble<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cabeza = cola = nullptr;
    }

    // insertar al inicio de la lista
    // complejidad: O(1) - acceso directo a cabeza, no recorre lista
    // es O(1) porque:
    //   1. crear nuevo nodo: O(1)
    //   2. actualizar punteros (maximo 4 asignaciones): O(1)
    //   3. incrementar tamano: O(1)
    void insertarAlInicio(T dato) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
        if (!cabeza) {
            // lista vacia: cabeza y cola apuntan al mismo nodo
            cabeza = cola = nuevo;
        } else {
            // lista no vacia: insertar antes de cabeza
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
            cabeza = nuevo;
        }
        tamano++;
    }

    // *** metodo personalizado #1 integrante 2: insertar al final ***
    // complejidad: O(1) - acceso directo a cola
    // es O(1) porque:
    //   1. tiene puntero directo a cola (no necesita recorrer)
    //   2. solo actualiza punteros: O(1)
    //   3. actualizar cola: O(1)
    // ventaja sobre lista simple sin puntero cola: antes era O(n), ahora O(1)
    void insertarAlFinal(T dato) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
        if (!cola) {
            // lista vacia: cabeza y cola apuntan al mismo nodo
            cabeza = cola = nuevo;
        } else {
            // lista no vacia: insertar despues de cola
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tamano++;
    }

    // *** metodo personalizado #2 integrante 2: eliminar por valor ***
    // complejidad: O(n) - debe buscar el elemento en la lista
    // es O(n) porque:
    //   - peor caso: elemento esta al final o no existe
    //   - debe recorrer hasta n elementos
    //   - por cada nodo: comparacion O(1)
    // ventaja de lista doble: actualizar anterior es O(1) (no necesita segundo puntero)
    bool eliminarPorValor(T valor) {
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            if (temp->dato == valor) {
                // encontrado: actualizar punteros

                // actualizar puntero del nodo anterior
                if (temp->anterior) {
                    temp->anterior->siguiente = temp->siguiente;
                } else {
                    // es la cabeza
                    cabeza = temp->siguiente;
                }

                // actualizar puntero del nodo siguiente
                if (temp->siguiente) {
                    temp->siguiente->anterior = temp->anterior;
                } else {
                    // es la cola
                    cola = temp->anterior;
                }

                delete temp;
                tamano--;
                return true;
            }
            temp = temp->siguiente;
        }
        return false;  // no encontrado
    }

    // *** metodo personalizado #3 integrante 2: obtener en posicion ***
    // complejidad: O(n) - recorre hasta la posicion deseada
    // es O(n) porque en peor caso (pos = n-1) recorre n-1 nodos
    // optimizacion posible: si pos > n/2, recorrer desde cola hacia atras
    T* obtenerEnPosicion(int pos) {
        if (pos < 0 || pos >= tamano) return nullptr;
        NodoDoble<T>* temp = cabeza;
        for (int i = 0; i < pos; i++) {
            temp = temp->siguiente;
        }
        return &(temp->dato);
    }

    // filtrar elementos con predicado (lambda)
    // complejidad: O(n) - recorre toda la lista una vez
    // crea nueva lista con elementos que cumplen condicion
    ListaDoble<T> filtrar(std::function<bool(T)> filtro) {
        ListaDoble<T> resultado;
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            if (filtro(temp->dato)) resultado.insertarAlFinal(temp->dato);
            temp = temp->siguiente;
        }
        return resultado;
    }

    // invertir lista completa
    // complejidad: O(n) - recorre intercambiando punteros
    // algoritmo: intercambia los punteros siguiente y anterior de cada nodo
    void invertir() {
        NodoDoble<T>* temp = nullptr;
        NodoDoble<T>* actual = cabeza;
        cola = cabeza;  // el antiguo cabeza sera la nueva cola

        while (actual) {
            temp = actual->anterior;
            actual->anterior = actual->siguiente;  // intercambiar punteros
            actual->siguiente = temp;
            actual = actual->anterior;  // avanzar (ahora anterior apunta al siguiente)
        }

        if (temp) cabeza = temp->anterior;
    }

    // aplicar funcion a cada elemento (con lambda)
    // complejidad: O(n) - recorre toda la lista
    // permite ejecutar cualquier operacion sobre cada elemento
    void aplicar(std::function<void(T)> func) {
        NodoDoble<T>* temp = cabeza;
        while (temp) {
            func(temp->dato);
            temp = temp->siguiente;
        }
    }

    // *** recursividad integrante 2: buscar valor recursivamente ***
    // complejidad: O(n) - recorre hasta encontrar o llegar al final
    // caso base: nodo nulo retorna false (no encontrado, fin de lista)
    // caso recursivo: si dato coincide retorna true, sino busca en siguiente
    // formula: T(n) = 1 + T(n-1) en peor caso, T(0) = 1
    // solucion: T(n) = n, por lo tanto O(n)
    bool buscarRecursivo(T valor, NodoDoble<T>* nodo) {
        if (!nodo) return false;  // caso base: fin de lista
        if (nodo->dato == valor) return true;  // encontrado
        return buscarRecursivo(valor, nodo->siguiente);  // caso recursivo
    }

    // version publica: inicia recursion desde cabeza
    bool buscarRecursivo(T valor) { return buscarRecursivo(valor, cabeza); }

    // getter: obtener tamaño de la lista
    // complejidad: O(1) - retorna variable miembro
    int getTamano() const { return tamano; }

    // getters: acceso a cabeza y cola
    // necesarios para algoritmos de ordenamiento que reorganizan nodos
    NodoDoble<T>* getCabeza() { return cabeza; }
    NodoDoble<T>* getCola() { return cola; }

    // setters para cabeza y cola
    // usados en algoritmos de ordenamiento para actualizar lista
    void setCabeza(NodoDoble<T>* nuevaCabeza) { cabeza = nuevaCabeza; }
    void setCola(NodoDoble<T>* nuevaCola) { cola = nuevaCola; }
};

#endif