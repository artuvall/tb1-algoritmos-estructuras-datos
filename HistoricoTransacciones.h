#ifndef HISTORICOTRANSACCIONES_H
#define HISTORICOTRANSACCIONES_H
// =============================================================================
// archivo: historicotransacciones.h
// descripcion: historial global de transacciones del sistema
// cumplimiento de rubrica:
//   - entidad #15: gestiona todas las transacciones procesadas
//   - algoritmo ordenamiento integrante 4: shellsort
//   - lambdas integrante 4: 3 lambdas (comparador, verificador, filtro)
//   - usa listadoble para gestionar transacciones
// =============================================================================

#include "ListaDoble.h"
#include "Transaccion.h"
#include <iostream>
#include <iomanip> // para setprecision
// HistoricoTransacciones.h
using namespace std;

// clase historicotransacciones: mantiene registro de todas las transacciones
// responsabilidades: agregar, ordenar, filtrar transacciones
class HistoricoTransacciones {
private:
    ListaDoble<Transaccion*> lista;  // lista de todas las transacciones

public:
    // agregar transaccion al historial
    // complejidad: O(1) - inserta al inicio de listadoble
    void agregar(Transaccion* t) { lista.insertarAlInicio(t); }

    // *** algoritmo de ordenamiento integrante 4: shellsort ***
    // *** metodo critico para la rubrica ***
    // complejidad: O(n log^2 n) con secuencia de gaps n/2, n/4, ..., 1
    // mejor caso: O(n log n) con secuencias optimas
    // analisis detallado:
    //   - paso 1: convertir lista a array: O(n)
    //   - paso 2: shellsort con gaps decrecientes: O(n log^2 n)
    //   - paso 3: reconstruir lista: O(n)
    //   - total: O(n) + O(n log^2 n) + O(n) = O(n log^2 n)
    // ventaja: mejora insertion sort, eficiente para datos parcialmente ordenados
    void ordenarShell() {
        int n = lista.getTamano();
        if (n <= 1) return;  // ya ordenado o vacio

        // paso 1: convertir lista a array temporal (O(n))
        Transaccion** arr = new Transaccion*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = *lista.obtenerEnPosicion(i);
        }

        // *** lambda #1 integrante 4: comparador para ordenar por monto ***
        // esta lambda define criterio de ordenamiento
        // ordena transacciones de menor a mayor monto
        // captura nada, recibe dos transacciones, retorna bool
        // razon: analizar patrones de montos de transacciones
        auto comparador = [](Transaccion* a, Transaccion* b) {
            // comparar por monto (menor a mayor)
            return a->getMonto() < b->getMonto();
        };

        // paso 2: shellsort con gaps decrecientes
        // algoritmo: insertion sort con gap variable
        // gap inicial: n/2, luego n/4, n/8, ..., hasta 1
        // cuando gap=1, es insertion sort normal sobre datos casi ordenados
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // insertion sort modificado con gap
            for (int i = gap; i < n; i++) {
                Transaccion* temp = arr[i];
                int j;

                // *** lambda #2 integrante 4: verificar si necesita intercambio ***
                // esta lambda invierte el comparador para ordenamiento correcto
                // captura comparador por referencia para reutilizarlo
                // razon: evitar codigo duplicado en verificacion
                auto necesitaIntercambio = [&comparador](Transaccion* a, Transaccion* b) {
                    return comparador(b, a);  // invertir comparacion
                };

                // mover elementos que son mayores que temp hacia adelante
                for (j = i; j >= gap && necesitaIntercambio(arr[j - gap], temp); j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }

        // paso 3: reconstruir lista ordenada (O(n))
        // eliminar elementos actuales
        while (lista.getTamano() > 0) {
            lista.eliminarPorValor(*lista.obtenerEnPosicion(0));
        }

        // insertar elementos ordenados
        for (int i = 0; i < n; i++) {
            lista.insertarAlFinal(arr[i]);
        }

        delete[] arr;
    }

    // *** lambda #3 integrante 4: filtrar transacciones por monto minimo ***
    // complejidad: O(n) - recorre toda la lista
    // parametro: monto minimo a filtrar
    // retorna: nueva lista con transacciones que cumplen condicion
    // uso: generar reportes de transacciones grandes
    ListaDoble<Transaccion*> filtrarPorMonto(double montoMin) {
        // lambda para verificar condicion
        auto filtro = [montoMin](Transaccion* t) {
            return t->getMonto() >= montoMin;
        };

        return lista.filtrar(filtro);
    }

    // metodo para imprimir historial con detalles completos
    // complejidad: O(n) - recorre todas las transacciones
    void imprimir() {
        cout << "\n=== HISTORIAL DE TRANSACCIONES ===\n";

        // lambda para formatear cada transaccion
        auto imprimirTransaccion = [](Transaccion* t) {
            // mostrar informacion detallada de cada transaccion
            cout << "ID: " << t->getId()
                 << " | Tipo: " << t->getTipo()
                 << " | Monto: S/ " << fixed << setprecision(2) << t->getMonto()
                 << " | Fecha: " << t->getFecha() << "\n";
        };

        lista.aplicar(imprimirTransaccion);
    }

    // getter: obtener cantidad de transacciones
    int getTamano() { return lista.getTamano(); }
};

#endif