#ifndef GESTORCLIENTES_H  
#define GESTORCLIENTES_H  
//GestorClientes.h
#include "Cliente.h"  
#include "ListaSimple.h"  
#include <iostream>

using namespace std;  

class GestorClientes {  
private:  
   ListaSimple<Cliente*> listaClientes;  

   // metodo auxiliar para heapsort: heapify
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
   void registrarNuevoCliente(Cliente* c) { listaClientes.insertarAlFinal(c); }  

   Cliente* buscarPorCodigo(const string& codigo) {  
       auto pred = [codigo](Cliente* cl) { return cl->getCodigo() == codigo; };
       Cliente** resultado = listaClientes.buscar(pred);
       return resultado ? *resultado : nullptr;
   }

   // heapsort integrante 3: ordenar clientes por codigo
   void ordenarClientesHeap() {
       int n = listaClientes.getTamano();
       if (n <= 1) return;

       // convertir lista a array temporal
       Cliente** arr = new Cliente*[n];
       for (int i = 0; i < n; i++) {
           arr[i] = *listaClientes.obtenerEnPosicion(i);
       }

       // lambda 1 integrante 3: comparador para ordenar por codigo
       auto comparador = [](Cliente* a, Cliente* b) {
           return a->getCodigo() > b->getCodigo(); // orden descendente para max-heap
       };

       // construir heap (reorganizar array)
       for (int i = n / 2 - 1; i >= 0; i--) {
           heapify(arr, n, i, comparador);
       }

       // extraer elementos del heap uno por uno
       for (int i = n - 1; i > 0; i--) {
           Cliente* temp = arr[0];
           arr[0] = arr[i];
           arr[i] = temp;
           heapify(arr, i, 0, comparador);
       }

       // reconstruir lista ordenada
       listaClientes.limpiar();
       for (int i = 0; i < n; i++) {
           listaClientes.insertarAlFinal(arr[i]);
       }

       delete[] arr;
   }

   // lambda 2 integrante 3: filtrar clientes con saldo total mayor a monto
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
   int contarClientesActivos() {
       int count = 0;
       auto contador = [&count](Cliente* cl) {
           if (cl != nullptr) count++;
       };
       listaClientes.imprimir(contador);
       return count;
   }

   // metodo para imprimir todos los clientes
   void imprimirClientes() {
       cout << "\n=== LISTA DE CLIENTES ===\n";
       auto imprimir = [](Cliente* cl) {
           cout << "ID: " << cl->getId() << " | Nombre: " << cl->getNombre()
                << " | Codigo: " << cl->getCodigo() << endl;
       };
       listaClientes.imprimir(imprimir);
   }

   ListaSimple<Cliente*>& getListaClientes() { return listaClientes; }
};

#endif