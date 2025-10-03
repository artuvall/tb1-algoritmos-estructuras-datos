#ifndef GESTORCLIENTES_H  
#define GESTORCLIENTES_H  
//GestorClientes.h
#include "Cliente.h"  
#include "ListaSimple.h"  

using namespace std;  

class GestorClientes {  
private:  
   ListaSimple<Cliente*> listaClientes;  

public:  
   void registrarNuevoCliente(Cliente* c) { listaClientes.insertarAlFinal(c); }  

   Cliente* buscarPorCodigo(const string& codigo) {  
       auto pred = [codigo](Cliente* cl) { return cl->getCodigo() == codigo; };  
       return *listaClientes.buscar(pred);  
   }  

   void ordenarClientesHeap() { // Heapsort: Integrante 3  
       // Nota: Build heap, extract max, O(n log n).  
   }  
};  

#endif