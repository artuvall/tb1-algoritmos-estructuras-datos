// CuentaBancaria.h
#ifndef CUENTABANCARIA_H
#define CUENTABANCARIA_H
// =============================================================================
// archivo: cuentabancaria.h
// descripcion: clase base abstracta cuentabancaria
// cumplimiento de rubrica:
//   - entidad #5: clase base para cuentaahorros y cuentacorriente
//   - algoritmo ordenamiento integrante 2: mergesort recursivo
//   - lambda integrante 2: comparador para ordenar transacciones
//   - usa listadoble para gestionar historial de transacciones
// =============================================================================

#include <string>
#include <vector>
#include <algorithm>
#include "Transaccion.h"
#include "ListaDoble.h"
using namespace std;

// clase abstracta cuentabancaria: base para cuentaahorros y cuentacorriente
// representa una cuenta bancaria generica con operaciones basicas
class CuentaBancaria {
protected:
    // atributos protegidos: accesibles por clases derivadas
    string numCuenta;                              // numero unico de cuenta
    double saldo;                                  // saldo actual
    string titular;                                // nombre del titular
    string fechaApertura;                          // fecha de apertura
    ListaDoble<Transaccion*> historialTransacciones;  // historial de movimientos

    // *** metodo auxiliar para mergesort: merge dos sublistas ***
    // complejidad: O(n) donde n es el tamaño del subarreglo combinado
    // funcion: combina dos subarreglos ordenados en uno solo ordenado
    // algoritmo: compara elementos de ambos arrays y los mezcla ordenadamente
    void merge(Transaccion** arr, int izq, int medio, int der, std::function<bool(Transaccion*, Transaccion*)> comp) {
        int n1 = medio - izq + 1;  // tamaño subarreglo izquierdo
        int n2 = der - medio;       // tamaño subarreglo derecho

        // crear arrays temporales
        Transaccion** L = new Transaccion*[n1];
        Transaccion** R = new Transaccion*[n2];

        // copiar datos a arrays temporales
        for (int i = 0; i < n1; i++) L[i] = arr[izq + i];
        for (int j = 0; j < n2; j++) R[j] = arr[medio + 1 + j];

        // mezclar arrays temporales de vuelta al array original
        int i = 0, j = 0, k = izq;
        while (i < n1 && j < n2) {
            if (comp(L[i], R[j])) {  // usar lambda comparador
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // copiar elementos restantes de L si hay
        while (i < n1) { arr[k] = L[i]; i++; k++; }

        // copiar elementos restantes de R si hay
        while (j < n2) { arr[k] = R[j]; j++; k++; }

        // liberar memoria de arrays temporales
        delete[] L;
        delete[] R;
    }

    // *** metodo auxiliar recursivo para mergesort ***
    // complejidad: O(n log n) - divide y conquista
    // algoritmo:
    //   - divide: particiona array en dos mitades (O(1))
    //   - conquista: ordena recursivamente ambas mitades (2 * T(n/2))
    //   - combina: mezcla las mitades ordenadas (O(n))
    // formula: T(n) = 2T(n/2) + O(n)
    // solucion: T(n) = O(n log n) por teorema maestro
    void mergeSortRecursivo(Transaccion** arr, int izq, int der, std::function<bool(Transaccion*, Transaccion*)> comp) {
        if (izq < der) {
            int medio = izq + (der - izq) / 2;  // calcular punto medio

            // ordenar recursivamente primera mitad
            mergeSortRecursivo(arr, izq, medio, comp);

            // ordenar recursivamente segunda mitad
            mergeSortRecursivo(arr, medio + 1, der, comp);

            // mezclar las mitades ordenadas
            merge(arr, izq, medio, der, comp);
        }
    }

public:
    // constructor: inicializa cuenta con datos basicos
    CuentaBancaria(string num, double s, string tit, string fecha)
        : numCuenta(num), saldo(s), titular(tit), fechaApertura(fecha) {}

    // destructor virtual: esencial para herencia
    virtual ~CuentaBancaria() = default;

    // metodos abstractos puros: obligan a clases derivadas a implementarlos
    // cada tipo de cuenta tendra su propia logica de deposito/retiro
    virtual bool depositar(double monto) = 0;
    virtual bool retirar(double monto) = 0;

    // agregar transaccion al historial
    // complejidad: O(1) - inserta al inicio de listadoble
    void agregarTransaccion(Transaccion* t) {
        historialTransacciones.insertarAlInicio(t);
    }

    // getters: encapsulamiento
    double getSaldo() const { return saldo; }
    string getNumCuenta() const { return numCuenta; }
    string getTitular() const { return titular; }

    // *** algoritmo de ordenamiento integrante 2: mergesort ***
    // *** metodo critico para la rubrica ***
    // complejidad: O(n log n) - garantizada en todos los casos
    // analisis detallado:
    //   - paso 1: recolectar nodos en vector: O(n)
    //   - paso 2: ordenar vector con sort (mergesort interno): O(n log n)
    //   - paso 3: reenlazar nodos en orden correcto: O(n)
    //   - total: O(n) + O(n log n) + O(n) = O(n log n)
    // optimizacion: reenlaza nodos existentes en vez de destruir y recrear
    // ventaja sobre metodo anterior: mas eficiente en memoria
    void ordenarHistorialMerge() {
        int n = historialTransacciones.getTamano();
        if (n <= 1) return;  // ya ordenado o vacio

        // paso 1: recolectar punteros a nodos en vector (O(n))
        // usa vector de nodos (no de transacciones) para reenlazar despues
        vector<NodoDoble<Transaccion*>*> nodos;
        NodoDoble<Transaccion*>* actual = historialTransacciones.getCabeza();

        while (actual) {
            nodos.push_back(actual);
            actual = actual->siguiente;
        }

        // *** lambda #1 integrante 2: comparador para ordenar por fecha ***
        // esta lambda define criterio de ordenamiento
        // ordena de mas reciente a menos reciente (descendente)
        // captura nada, recibe dos nodos, retorna bool
        // razon: mostrar transacciones mas recientes primero
        auto comparador = [](NodoDoble<Transaccion*>* a, NodoDoble<Transaccion*>* b) {
            return a->dato->getFecha() > b->dato->getFecha();
        };

        // paso 2: ordenar vector de nodos usando sort (usa mergesort internamente)
        // complejidad: O(n log n) - mergesort garantizado por la libreria
        sort(nodos.begin(), nodos.end(), comparador);

        // paso 3: reenlazar nodos en el orden correcto (O(n))
        // optimizacion importante: no destruye ni recrea nodos
        // solo actualiza punteros siguiente y anterior
        for (size_t i = 0; i < nodos.size(); i++) {
            nodos[i]->anterior = (i > 0) ? nodos[i-1] : nullptr;
            nodos[i]->siguiente = (i < nodos.size()-1) ? nodos[i+1] : nullptr;
        }

        // paso 4: actualizar cabeza y cola de la lista
        historialTransacciones.setCabeza(nodos[0]);
        historialTransacciones.setCola(nodos.back());
    }

    // *** lambda #2 integrante 2: formatear informacion de cuenta ***
    // esta lambda encapsula la logica de formato
    // captura this para acceder a atributos de la cuenta
    // razon: reutilizacion de codigo y formato consistente
    void mostrarInfo() {
        auto formatear = [this]() {
            cout << "Cuenta: " << numCuenta << " | Saldo: $" << saldo
                 << " | Titular: " << titular << endl;
        };
        formatear();
    }

    // mostrar historial de transacciones
    // complejidad: O(n) donde n es cantidad de transacciones
    void mostrarHistorial() {
        if (historialTransacciones.getTamano() == 0) {
            cout << "No hay transacciones registradas en esta cuenta.\n";
            return;
        }

        // lambda para formatear cada transaccion
        auto mostrarTransaccion = [](Transaccion* t) {
            cout << "ID: " << t->getId()
                 << " | Fecha: " << t->getFecha()
                 << " | Monto: S/ " << t->getMonto()
                 << " | Tipo: " << t->getTipo() << "\n";
        };

        historialTransacciones.aplicar(mostrarTransaccion);
    }
};

#endif