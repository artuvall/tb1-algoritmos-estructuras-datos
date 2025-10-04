#ifndef PILA_H
#define PILA_H
// =============================================================================
// archivo: pila.h
// descripcion: estructura de datos pila (stack) generica - lifo
// cumplimiento de rubrica:
//   - estructura de datos #3 (integrante 4): pila
//   - usa listasimple internamente (reutilizacion de codigo)
//   - metodos personalizados: buscar, invertir, contarsi
//   - recursividad integrante 4: vaciarrecursivo
//   - principio lifo: last in, first out
// =============================================================================

// Pila.h - Estructura de pila generica con templates
// metodos implementados por integrante 4
#include "ListaSimple.h"

using namespace std;

// *** estructura de datos integrante 4: pila (stack) ***
// implementa principio lifo: ultimo en entrar, primero en salir
// ejemplo real: pila de platos, deshacer operaciones en editor
template <typename T>
class Pila {
private:
    ListaSimple<T> listaInterna;  // usa listasimple como contenedor interno

public:
    // push: agregar elemento al tope de la pila
    // complejidad: O(1) - inserta al inicio de lista
    // es O(1) porque insertaralinicio de listasimple es O(1)
    void push(T dato) {
        listaInterna.insertarAlInicio(dato); // insertar al inicio para push O(1)
    }

    // pop: remover y retornar elemento del tope
    // complejidad: O(1) - elimina primer elemento
    // lanza excepcion si pila esta vacia
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

    // top: ver elemento del tope sin removerlo
    // complejidad: O(1) - solo consulta primer elemento
    T top() {
        if (listaInterna.getTamano() == 0) throw "pila vacia";
        T* ptr = listaInterna.obtenerEnPosicion(0);
        if (ptr) return *ptr;
        throw "pila vacia";
    }

    // *** metodo personalizado #1 integrante 4: buscar con lambda ***
    // complejidad: O(n) - peor caso recorre toda la pila
    // parametro: predicado lambda que define criterio de busqueda
    // retorna: true si encuentra elemento que cumple predicado
    // uso de lambda: permite buscar con cualquier condicion personalizada
    bool buscar(std::function<bool(T)> predicado) {
        return listaInterna.buscar(predicado) != nullptr;
    }

    // *** metodo personalizado #2 integrante 4: invertir pila ***
    // complejidad: O(n) - invierte orden de todos los elementos
    // despues de invertir, el elemento del fondo pasa al tope
    // usa el metodo invertir de listasimple
    void invertir() {
        listaInterna.invertir();
    }

    // *** metodo personalizado #3 integrante 4: contar con condicion ***
    // complejidad: O(n) - recorre toda la pila contando
    // parametro: lambda que define condicion a evaluar
    // retorna: cantidad de elementos que cumplen la condicion
    // ejemplo de uso: contar elementos mayores a x, contar pares, etc
    int contarSi(std::function<bool(T)> condicion) {
        int count = 0;
        // lambda anidada: captura count por referencia para incrementarlo
        auto contador = [&count, condicion](T dato) {
            if (condicion(dato)) count++;
        };
        listaInterna.imprimir(contador);
        return count;
    }

    // *** recursividad integrante 4: vaciar pila recursivamente ***
    // complejidad: O(n) - elimina cada nodo recursivamente
    // caso base: nodo nulo, no hace nada
    // caso recursivo: procesa siguiente y luego elimina actual
    // formula: T(n) = T(n-1) + O(1), T(0) = O(1)
    // solucion: T(n) = n, por lo tanto O(n)
    void vaciarRecursivoAux(Nodo<T>* nodo) {
        if (!nodo) return;  // caso base
        vaciarRecursivoAux(nodo->siguiente);  // recursion primero
        delete nodo;  // eliminar despues (postorden)
    }

    // version publica: inicia recursion y actualiza cabeza
    void vaciarRecursivo() {
        vaciarRecursivoAux(listaInterna.getCabeza());
        listaInterna.setCabeza(nullptr);
    }

    // getter: obtener cantidad de elementos
    // complejidad: O(1)
    int getTamano() { return listaInterna.getTamano(); }

    // verificar si pila esta vacia
    // complejidad: O(1)
    bool estaVacia() { return listaInterna.getTamano() == 0; }
};

#endif