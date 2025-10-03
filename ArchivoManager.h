#ifndef ARCHIVOMANAGER_H  
#define ARCHIVOMANAGER_H  
// ArchivoManager.h
#include <fstream>
#include <sstream>
#include "ListaSimple.h"
#include "Cliente.h"  

using namespace std;  

class ArchivoManager {  
private:
    // metodo auxiliar para selectionsort
    void selectionSortRecursivo(Cliente** arr, int n, int index, std::function<bool(Cliente*, Cliente*)> comp) {
        if (index >= n - 1) return;

        int minIndex = index;
        for (int j = index + 1; j < n; j++) {
            if (comp(arr[j], arr[minIndex])) {
                minIndex = j;
            }
        }

        if (minIndex != index) {
            Cliente* temp = arr[index];
            arr[index] = arr[minIndex];
            arr[minIndex] = temp;
        }

        selectionSortRecursivo(arr, n, index + 1, comp);
    }

public:
    // selectionsort integrante 5: ordenar clientes antes de guardar
    void ordenarClientesSelection(ListaSimple<Cliente*>& lista) {
        int n = lista.getTamano();
        if (n <= 1) return;

        Cliente** arr = new Cliente*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = *lista.obtenerEnPosicion(i);
        }

        // lambda 1 integrante 5: comparador por nombre
        auto comparador = [](Cliente* a, Cliente* b) {
            return a->getNombre() < b->getNombre();
        };

        selectionSortRecursivo(arr, n, 0, comparador);

        lista.limpiar();
        for (int i = 0; i < n; i++) {
            lista.insertarAlFinal(arr[i]);
        }

        delete[] arr;
    }

    void guardarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {
        ofstream out(archivo);
        if (!out.is_open()) {
            cout << "Error: no se pudo abrir archivo para guardar.\n";
            return;
        }

        // lambda 2 integrante 5: formatear y escribir cliente
        auto escribir = [&out](Cliente* cl) {
            out << cl->getId() << ","
                << cl->getNombre() << ","
                << cl->getCodigo() << endl;
        };

        lista.imprimir(escribir);
        out.close();
        cout << "Datos guardados exitosamente en: " << archivo << endl;
    }

    void cargarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {
        ifstream in(archivo);
        if (!in.is_open()) {
            cout << "Aviso: archivo no encontrado, se creara uno nuevo al guardar.\n";
            return;
        }

        string line;
        int count = 0;

        while (getline(in, line)) {
            stringstream ss(line);
            string id, nombre, codigo;

            // lambda 3 integrante 5: parsear linea
            auto parsear = [&ss, &id, &nombre, &codigo]() {
                getline(ss, id, ',');
                getline(ss, nombre, ',');
                getline(ss, codigo, ',');
                return !id.empty() && !nombre.empty() && !codigo.empty();
            };

            if (parsear()) {
                // crear cliente basico (sin todos los datos)
                Cliente* cl = new Cliente(id, nombre, "", "", codigo, "");
                lista.insertarAlFinal(cl);
                count++;
            }
        }

        in.close();
        cout << "Se cargaron " << count << " clientes desde: " << archivo << endl;
    }
};

#endif