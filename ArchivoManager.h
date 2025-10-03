#ifndef ARCHIVOMANAGER_H  
#define ARCHIVOMANAGER_H  
// ArchivoManager.h
#include <fstream>  
#include "ListaSimple.h"  
#include "Cliente.h"  

using namespace std;  

class ArchivoManager {  
public:  
   void guardarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {  
       ofstream out(archivo);  
       auto impr = [&out](Cliente* cl) { out << cl->getId() << "," << cl->getNombre() << "," << cl->getCodigo() << endl; };  
       lista.imprimir(impr);  
       out.close();  
   }  

   void cargarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {  
       ifstream in(archivo);  
       string line;  
       while (getline(in, line)) {  
           // Parse: id,nombre,codigo con stringstream.  
       }  
       in.close();  
   }  
};  

#endif