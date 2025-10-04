#ifndef COLA_H
#define COLA_H
// =============================================================================
// archivo: cola.h
// descripcion: estructura de datos cola (queue) generica - fifo
// cumplimiento de rubrica:
//   - estructura de datos #4 (integrante 3): cola
//   - usa listasimple internamente (reutilizacion de codigo)
//   - metodos personalizados: buscar, vaciar, contar
//   - recursividad integrante 3: tamanorecursivo
//   - principio fifo: first in, first out
// =============================================================================

// Cola.h - Estructura de cola generica con templates
// metodos implementados por integrante 3
#include "ListaSimple.h"

using namespace std;

// *** estructura de datos integrante 3: cola (queue) ***
// implementa principio fifo: primero en entrar, primero en salir
// ejemplo real: cola de atencion en banco, cola de impresion
template <typename T>
class Cola {
private:
    ListaSimple<T> listaInterna;  // usa listasimple como contenedor interno

public:
    // encolar: agregar elemento al final de la cola
    // complejidad: O(1) - gracias a puntero cola en listasimple
    // antes de optimizacion era O(n), ahora O(1)
    void encolar(T dato) {
        listaInterna.insertarAlFinal(dato); // encolar al final O(1) optimizado
    }

    // desencolar: remover y retornar elemento del frente
    // complejidad: O(1) - elimina primer elemento
    // lanza excepcion si cola esta vacia
    T desencolar() {
        if (listaInterna.getTamano() == 0) throw "cola vacia";
        T* ptr = listaInterna.obtenerEnPosicion(0);
        if (ptr) {
            T dato = *ptr;
            listaInterna.eliminar(0);
            return dato;
        }
        throw "cola vacia";
    }

    // frente: ver elemento del frente sin removerlo
    // complejidad: O(1) - solo consulta primer elemento
    T frente() {
        if (listaInterna.getTamano() == 0) throw "cola vacia";
        T* ptr = listaInterna.obtenerEnPosicion(0);
        if (ptr) return *ptr;
        throw "cola vacia";
    }

    // *** metodo personalizado #1 integrante 3: buscar con lambda ***
    // complejidad: O(n) - peor caso recorre toda la cola
    // parametro: predicado lambda que define criterio de busqueda
    // retorna: puntero al elemento encontrado o nullptr
    // uso de lambda: permite buscar con cualquier condicion personalizada
    T* buscar(std::function<bool(T)> predicado) {
        return listaInterna.buscar(predicado);
    }

    // *** metodo personalizado #2 integrante 3: vaciar cola ***
    // complejidad: O(n) - elimina todos los elementos uno por uno
    // es O(n) porque:
    //   - while ejecuta n veces (una por elemento)
    //   - eliminar(0) es O(1)
    //   - total: n * O(1) = O(n)
    void vaciar() {
        while (listaInterna.getTamano() > 0) {
            listaInterna.eliminar(0);
        }
    }

    // *** metodo personalizado #3 integrante 3: contar con condicion ***
    // complejidad: O(n) - recorre toda la cola una vez
    // parametro: lambda que define condicion a evaluar
    // retorna: cantidad de elementos que cumplen la condicion
    // ejemplo: contar transacciones mayores a monto, contar clientes activos
    int contar(std::function<bool(T)> condicion) {
        int count = 0;
        // lambda anidada: captura count por referencia para incrementarlo
        auto contador = [&count, condicion](T dato) {
            if (condicion(dato)) count++;
        };
        listaInterna.imprimir(contador);
        return count;
    }

    // *** recursividad integrante 3: contar tamaño recursivamente ***
    // complejidad: O(n) - delega a contarrecursivo de listasimple
    // demuestra reutilizacion de recursividad implementada en listasimple
    int tamanoRecursivo() {
        return listaInterna.contarRecursivo();
    }

    // getter: obtener cantidad de elementos
    // complejidad: O(1)
    int getTamano() { return listaInterna.getTamano(); }

    // verificar si cola esta vacia
    // complejidad: O(1)
    bool estaVacia() { return listaInterna.getTamano() == 0; }
};

#endif