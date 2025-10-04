#ifndef ARCHIVOMANAGER_H
#define ARCHIVOMANAGER_H
// ArchivoManager.h - Gestion de archivos de texto
// Incluye Selection Sort como algoritmo de ordenamiento adicional
#include "ListaSimple.h"
#include "Cliente.h"
#include "PersonaNatural.h"
#include "PersonaJuridica.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

class ArchivoManager {
public:
    // Guardar clientes en archivo de texto
    // Formato: id|nombre|apellido|email|codigo|fechaAlta|tipo|campo1|campo2
    // Complejidad: O(n) - recorre todos los clientes
    void guardarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {
        ofstream file(archivo);
        if (!file.is_open()) {
            cout << "Error: No se pudo abrir el archivo para escritura.\n";
            return;
        }

        int guardados = 0;
        for (int i = 0; i < lista.getTamano(); i++) {
            Cliente* cl = *lista.obtenerEnPosicion(i);
            if (!cl) continue;

            // Datos basicos del cliente
            file << cl->getId() << "|"
                 << cl->getNombre() << "|"
                 << cl->getApellido() << "|"
                 << cl->getEmail() << "|"
                 << cl->getCodigo() << "|"
                 << cl->getFechaAlta() << "|";

            // Determinar tipo y guardar campos especificos
            Persona* detalles = cl->getDetallesPersona();
            if (detalles) {
                PersonaNatural* pn = dynamic_cast<PersonaNatural*>(detalles);
                PersonaJuridica* pj = dynamic_cast<PersonaJuridica*>(detalles);

                if (pn) {
                    // Tipo Natural: guardar DNI y fecha nacimiento
                    file << "NATURAL|" << pn->getDni() << "|" << pn->getFechaNac();
                } else if (pj) {
                    // Tipo Juridica: guardar RUC y razon social
                    file << "JURIDICA|" << pj->getRuc() << "|" << pj->getRazonSocial();
                } else {
                    // Tipo desconocido
                    file << "DESCONOCIDO|NA|NA";
                }
            } else {
                file << "DESCONOCIDO|NA|NA";
            }

            file << "\n";
            guardados++;
        }

        file.close();
        cout << "=== DATOS GUARDADOS ===\n";
        cout << "Archivo: " << archivo << "\n";
        cout << "Clientes guardados: " << guardados << "\n";
    }

    // Cargar clientes desde archivo de texto
    // Complejidad: O(n) donde n es el numero de lineas en el archivo
    void cargarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {
        ifstream file(archivo);
        if (!file.is_open()) {
            cout << "Aviso: No se encontro archivo previo '" << archivo << "'.\n";
            cout << "Se iniciara con datos vacios.\n";
            return;
        }

        string linea;
        int cargados = 0;

        while (getline(file, linea)) {
            if (linea.empty()) continue;

            stringstream ss(linea);
            string id, nombre, apellido, email, codigo, fechaAlta, tipo, campo1, campo2;

            // Leer campos separados por '|'
            getline(ss, id, '|');
            getline(ss, nombre, '|');
            getline(ss, apellido, '|');
            getline(ss, email, '|');
            getline(ss, codigo, '|');
            getline(ss, fechaAlta, '|');
            getline(ss, tipo, '|');
            getline(ss, campo1, '|');
            getline(ss, campo2, '|');

            // Crear objeto Persona segun tipo
            Persona* detalles = nullptr;

            if (tipo == "NATURAL") {
                // campo1 = DNI, campo2 = FechaNac
                detalles = new PersonaNatural(id, nombre, apellido, email, campo1, campo2);
            } else if (tipo == "JURIDICA") {
                // campo1 = RUC, campo2 = RazonSocial
                detalles = new PersonaJuridica(id, nombre, apellido, email, campo1, campo2);
            } else {
                // Tipo desconocido: crear PersonaNatural por defecto
                detalles = new PersonaNatural(id, nombre, apellido, email, "00000000", "01/01/2000");
            }

            // Crear cliente con los datos cargados
            Cliente* cl = new Cliente(id, nombre, apellido, email, codigo, fechaAlta, detalles);
            lista.insertarAlFinal(cl);
            cargados++;
        }

        file.close();
        cout << "=== DATOS CARGADOS ===\n";
        cout << "Archivo: " << archivo << "\n";
        cout << "Clientes cargados: " << cargados << "\n";
    }

    // Selection Sort - Algoritmo de ordenamiento adicional
    // Ordena clientes por codigo antes de guardar
    // Complejidad: O(n^2) - dos bucles anidados
    // Justificacion: Simple de implementar, adecuado para listas pequeñas
    void ordenarClientesSelection(ListaSimple<Cliente*>& lista) {
        int n = lista.getTamano();
        if (n <= 1) return;

        cout << "\n=== ORDENANDO CON SELECTION SORT ===\n";

        // Algoritmo Selection Sort
        // En cada iteracion encuentra el minimo y lo coloca en su posicion
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            Cliente* minCliente = *lista.obtenerEnPosicion(minIdx);

            // Buscar el minimo en el resto de la lista
            for (int j = i + 1; j < n; j++) {
                Cliente* actualCliente = *lista.obtenerEnPosicion(j);

                // lambda para comparacion: ordenar por codigo ascendente
                auto comparar = [](const string& a, const string& b) {
                    return a < b;
                };

                if (comparar(actualCliente->getCodigo(), minCliente->getCodigo())) {
                    minIdx = j;
                    minCliente = actualCliente;
                }
            }

            // Intercambiar si se encontro un minimo diferente
            if (minIdx != i) {
                // Obtener punteros a ambos clientes
                Cliente** ptrI = lista.obtenerEnPosicion(i);
                Cliente** ptrMin = lista.obtenerEnPosicion(minIdx);

                // Intercambiar los punteros
                Cliente* temp = *ptrI;
                *ptrI = *ptrMin;
                *ptrMin = temp;
            }
        }

        cout << "Lista ordenada con Selection Sort (por codigo)\n";
    }

    // Metodo auxiliar: verificar si archivo existe
    // Complejidad: O(1) - operacion de sistema
    bool archivoExiste(const string& archivo) {
        ifstream file(archivo);
        bool existe = file.good();
        file.close();
        return existe;
    }

    // Metodo auxiliar: crear respaldo de archivo
    // Complejidad: O(n) donde n es el tamaño del archivo
    void crearRespaldo(const string& archivoOriginal) {
        if (!archivoExiste(archivoOriginal)) {
            cout << "No hay archivo para respaldar.\n";
            return;
        }

        string archivoRespaldo = archivoOriginal + ".bak";

        ifstream origen(archivoOriginal, ios::binary);
        ofstream destino(archivoRespaldo, ios::binary);

        if (!origen.is_open() || !destino.is_open()) {
            cout << "Error al crear respaldo.\n";
            return;
        }

        // Copiar contenido
        destino << origen.rdbuf();

        origen.close();
        destino.close();

        cout << "Respaldo creado: " << archivoRespaldo << "\n";
    }
};

#endif

