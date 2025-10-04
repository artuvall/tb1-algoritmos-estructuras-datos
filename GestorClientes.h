#ifndef GESTORCLIENTES_H  
#define GESTORCLIENTES_H  
//GestorClientes.h - Gestion de clientes con HeapSort
// OPTIMIZACION: Mejorado HeapSort para reenlazar nodos en vez de recrear lista
#include "Cliente.h"
#include "ListaSimple.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;  

class GestorClientes {  
private:  
   ListaSimple<Cliente*> listaClientes;  

   // metodo auxiliar para heapsort: heapify (convertir subarbol en heap)
   // Complejidad: O(log n) - desciende por la altura del arbol
   void heapify(Cliente** arr, int n, int i, std::function<bool(Cliente*, Cliente*)> comp) {
       int mayor = i;
       int izq = 2 * i + 1;
       int der = 2 * i + 2;

       if (izq < n && comp(arr[izq], arr[mayor])) mayor = izq;
       if (der < n && comp(arr[der], arr[mayor])) mayor = der;

       if (mayor != i) {
           Cliente* temp = arr[i];
           arr[i] = arr[mayor];
           arr[mayor] = temp;
           heapify(arr, n, mayor, comp);
       }
   }

public:
   // Registrar nuevo cliente al final de la lista
   // Complejidad: O(1) - gracias a puntero cola optimizado
   void registrarNuevoCliente(Cliente* c) { listaClientes.insertarAlFinal(c); }

   // Buscar cliente por codigo usando lambda
   // Complejidad: O(n) - recorre hasta encontrar
   Cliente* buscarPorCodigo(const string& codigo) {
       auto pred = [codigo](Cliente* cl) { return cl->getCodigo() == codigo; };
       Cliente** resultado = listaClientes.buscar(pred);
       return resultado ? *resultado : nullptr;
   }

   // OPTIMIZADO: heapsort integrante 3 - ordenar clientes por codigo
   // MEJORA: Reenlaza nodos existentes en vez de limpiar y recrear lista completa
   // Complejidad: O(n log n) - construccion heap O(n) + extracciones O(n log n)
   void ordenarClientesHeap() {
       int n = listaClientes.getTamano();
       if (n <= 1) return;

       // PASO 1: Recolectar nodos en vector (O(n))
       vector<Nodo<Cliente*>*> nodos;
       Nodo<Cliente*>* actual = listaClientes.getCabeza();

       while (actual) {
           nodos.push_back(actual);
           actual = actual->siguiente;
       }

       // PASO 2: Extraer punteros a clientes para ordenar
       Cliente** arr = new Cliente*[n];
       for (int i = 0; i < n; i++) {
           arr[i] = nodos[i]->dato;
       }

       // PASO 3: lambda 1 integrante 3 - comparador para ordenar por codigo
       // Usa orden descendente para crear max-heap
       auto comparador = [](Cliente* a, Cliente* b) {
           return a->getCodigo() > b->getCodigo();
       };

       // PASO 4: Construir heap (reorganizar array)
       // Complejidad: O(n) - contrario a lo que parece
       for (int i = n / 2 - 1; i >= 0; i--) {
           heapify(arr, n, i, comparador);
       }

       // PASO 5: Extraer elementos del heap uno por uno
       // Complejidad: O(n log n)
       for (int i = n - 1; i > 0; i--) {
           Cliente* temp = arr[0];
           arr[0] = arr[i];
           arr[i] = temp;
           heapify(arr, i, 0, comparador);
       }

       // PASO 6: Actualizar datos de nodos con clientes ordenados (O(n))
       // OPTIMIZACION: No destruye ni recrea nodos, solo actualiza el dato
       for (int i = 0; i < n; i++) {
           nodos[i]->dato = arr[i];
       }

       // PASO 7: Reenlazar nodos en secuencia correcta (O(n))
       for (int i = 0; i < n; i++) {
           nodos[i]->siguiente = (i < n-1) ? nodos[i+1] : nullptr;
       }

       // PASO 8: Actualizar cabeza y cola
       listaClientes.setCabeza(nodos[0]);
       listaClientes.setCola(nodos[n-1]);

       delete[] arr;
   }

   // lambda 2 integrante 3: filtrar clientes con saldo total mayor a monto
   // Complejidad: O(n) - recorre toda la lista una vez
   ListaSimple<Cliente*> filtrarPorSaldo(double montoMinimo) {
       ListaSimple<Cliente*> resultado;
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

   // lambda 3 integrante 3: contar clientes activos
   // Complejidad: O(n) - recorre toda la lista
   int contarClientesActivos() {
       int count = 0;
       auto contador = [&count](Cliente* cl) {
           if (cl != nullptr) count++;
       };
       listaClientes.imprimir(contador);
       return count;
   }

   // metodo para imprimir todos los clientes
   // Complejidad: O(n)
   void imprimirClientes() {
       cout << "\n=== LISTA DE CLIENTES ===\n";
       auto imprimir = [](Cliente* cl) {
           cout << "ID: " << cl->getId() << " | Nombre: " << cl->getNombre()
                << " | Codigo: " << cl->getCodigo() << endl;
       };
       listaClientes.imprimir(imprimir);
   }

   // Getter: acceso a lista de clientes
   ListaSimple<Cliente*>& getListaClientes() { return listaClientes; }
};

#endif