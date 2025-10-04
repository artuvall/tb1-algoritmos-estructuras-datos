#ifndef GESTORCLIENTES_H  
#define GESTORCLIENTES_H  
// =============================================================================
// archivo: gestorclientes.h
// descripcion: gestor de clientes del sistema bancario
// cumplimiento de rubrica:
//   - entidad #14: gestiona lista de clientes
//   - algoritmo ordenamiento integrante 3: heapsort recursivo
//   - lambdas integrante 3: 3 lambdas (comparador, filtro, contador)
//   - usa listasimple para gestionar clientes
// =============================================================================

//GestorClientes.h - Gestion de clientes con HeapSort
// OPTIMIZACION: Mejorado HeapSort para reenlazar nodos en vez de recrear lista
#include "Cliente.h"
#include "ListaSimple.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;  

// clase gestorclientes: administra todos los clientes del banco
// responsabilidades: registrar, buscar, ordenar clientes
class GestorClientes {
private:  
   ListaSimple<Cliente*> listaClientes;  // lista de todos los clientes

   // *** metodo auxiliar para heapsort: heapify (convertir subarbol en heap) ***
   // complejidad: O(log n) - desciende por la altura del arbol
   // funcion: reorganiza subarbol para mantener propiedad de max-heap
   // algoritmo: compara nodo con hijos y hace swap si es necesario
   void heapify(Cliente** arr, int n, int i, std::function<bool(Cliente*, Cliente*)> comp) {
       int mayor = i;           // inicializar mayor como raiz
       int izq = 2 * i + 1;     // hijo izquierdo
       int der = 2 * i + 2;     // hijo derecho

       // si hijo izquierdo es mayor que raiz
       if (izq < n && comp(arr[izq], arr[mayor])) mayor = izq;

       // si hijo derecho es mayor que el mayor actual
       if (der < n && comp(arr[der], arr[mayor])) mayor = der;

       // si mayor no es raiz
       if (mayor != i) {
           // intercambiar
           Cliente* temp = arr[i];
           arr[i] = arr[mayor];
           arr[mayor] = temp;

           // recursivamente heapify el subarbol afectado
           heapify(arr, n, mayor, comp);
       }
   }

public:
   // registrar nuevo cliente al final de la lista
   // complejidad: O(1) - gracias a puntero cola optimizado en listasimple
   void registrarNuevoCliente(Cliente* c) { listaClientes.insertarAlFinal(c); }

   // buscar cliente por codigo usando lambda
   // complejidad: O(n) - busqueda lineal en lista enlazada
   // parametro: codigo del cliente a buscar
   // retorna: puntero al cliente o nullptr si no existe
   Cliente* buscarPorCodigo(const string& codigo) {
       // lambda como predicado de busqueda
       auto pred = [codigo](Cliente* cl) { return cl->getCodigo() == codigo; };
       Cliente** resultado = listaClientes.buscar(pred);
       return resultado ? *resultado : nullptr;
   }

   // *** algoritmo de ordenamiento integrante 3: heapsort ***
   // *** metodo critico para la rubrica ***
   // complejidad: O(n log n) - garantizada en todos los casos
   // analisis detallado:
   //   - paso 1: recolectar nodos: O(n)
   //   - paso 2: construir heap: O(n) - sorprendentemente lineal
   //   - paso 3: extracciones repetidas: O(n log n)
   //   - paso 4: reenlazar nodos: O(n)
   //   - total: O(n) + O(n) + O(n log n) + O(n) = O(n log n)
   // optimizacion: reenlaza nodos existentes en vez de recrear lista
   // ventaja: no destruye ni recrea memoria, solo actualiza punteros
   void ordenarClientesHeap() {
       int n = listaClientes.getTamano();
       if (n <= 1) return;  // ya ordenado o vacio

       // paso 1: recolectar punteros a nodos en vector (O(n))
       vector<Nodo<Cliente*>*> nodos;
       Nodo<Cliente*>* actual = listaClientes.getCabeza();

       while (actual) {
           nodos.push_back(actual);
           actual = actual->siguiente;
       }

       // paso 2: extraer punteros a clientes para ordenar
       Cliente** arr = new Cliente*[n];
       for (int i = 0; i < n; i++) {
           arr[i] = nodos[i]->dato;
       }

       // *** lambda #1 integrante 3: comparador para ordenar por codigo ***
       // esta lambda define criterio de ordenamiento
       // usa orden descendente para crear max-heap
       // captura nada, recibe dos clientes, retorna bool
       // razon: ordenar clientes alfabeticamente por codigo
       auto comparador = [](Cliente* a, Cliente* b) {
           return a->getCodigo() > b->getCodigo();
       };

       // paso 3: construir heap (reorganizar array) - O(n)
       // construccion bottom-up: comienza desde ultimo nodo interno
       // teorema: construir heap es O(n), no O(n log n)
       // razon: suma de alturas ponderadas = O(n)
       for (int i = n / 2 - 1; i >= 0; i--) {
           heapify(arr, n, i, comparador);
       }

       // paso 4: extraer elementos del heap uno por uno - O(n log n)
       // en cada iteracion:
       //   - intercambia raiz (maximo) con ultimo elemento: O(1)
       //   - reduce tamaño del heap: O(1)
       //   - restaura propiedad heap con heapify: O(log n)
       // total: n iteraciones * O(log n) = O(n log n)
       for (int i = n - 1; i > 0; i--) {
           // mover raiz actual al final
           Cliente* temp = arr[0];
           arr[0] = arr[i];
           arr[i] = temp;

           // heapify raiz reducida
           heapify(arr, i, 0, comparador);
       }

       // paso 5: actualizar datos de nodos con clientes ordenados (O(n))
       // optimizacion importante: no destruye ni recrea nodos
       // solo actualiza el dato de cada nodo existente
       for (int i = 0; i < n; i++) {
           nodos[i]->dato = arr[i];
       }

       // paso 6: reenlazar nodos en secuencia correcta (O(n))
       for (int i = 0; i < n; i++) {
           nodos[i]->siguiente = (i < n-1) ? nodos[i+1] : nullptr;
       }

       // paso 7: actualizar cabeza y cola de la lista
       listaClientes.setCabeza(nodos[0]);
       listaClientes.setCola(nodos[n-1]);

       delete[] arr;
   }

   // *** lambda #2 integrante 3: filtrar clientes con saldo mayor a monto ***
   // complejidad: O(n) - recorre toda la lista una vez
   // parametro: monto minimo de saldo total
   // retorna: nueva lista con clientes que cumplen condicion
   // uso: generar reportes de clientes premium
   ListaSimple<Cliente*> filtrarPorSaldo(double montoMinimo) {
       ListaSimple<Cliente*> resultado;

       // lambda para verificar condicion
       auto filtro = [montoMinimo](Cliente* cl) {
           // verificar si el saldo total de todas las cuentas es mayor al minimo
           return cl->getSaldoTotal() >= montoMinimo;
       };

       // recorrer lista y agregar clientes que cumplan filtro
       for (int i = 0; i < listaClientes.getTamano(); i++) {
           Cliente* cl = *listaClientes.obtenerEnPosicion(i);
           if (filtro(cl)) {
               resultado.insertarAlFinal(cl);
           }
       }
       return resultado;
   }

   // *** lambda #3 integrante 3: contar clientes activos ***
   // complejidad: O(n) - recorre toda la lista
   // retorna: cantidad total de clientes no nulos
   // uso: estadisticas del sistema
   int contarClientesActivos() {
       int count = 0;

       // lambda contador: captura count por referencia
       auto contador = [&count](Cliente* cl) {
           if (cl != nullptr) count++;
       };

       listaClientes.imprimir(contador);
       return count;
   }

   // metodo para imprimir todos los clientes
   // complejidad: O(n) - recorre e imprime cada cliente
   void imprimirClientes() {
       cout << "\n=== LISTA DE CLIENTES ===\n";

       // lambda para formatear cada cliente
       auto imprimir = [](Cliente* cl) {
           cout << "ID: " << cl->getId()
                << " | Nombre: " << cl->getNombre()
                << " | Codigo: " << cl->getCodigo()
                << " | Cuentas: " << cl->getCantidadCuentas() << "\n";
       };

       listaClientes.imprimir(imprimir);
   }

   // getter: acceso a lista de clientes
   // usado por sistemafinanciero para persistencia
   ListaSimple<Cliente*>& getListaClientes() { return listaClientes; }
};

#endif