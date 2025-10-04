#ifndef ARCHIVOMANAGER_H
#define ARCHIVOMANAGER_H
// =============================================================================
// archivo: archivomanager.h
// descripcion: gestion de persistencia de datos en archivos de texto
// cumplimiento de rubrica:
//   - entidad #17: maneja lectura y escritura de archivos
//   - algoritmo ordenamiento adicional: selection sort
//   - uso de archivos de texto para persistencia (requisito de rubrica)
//   - permite cargar datos al iniciar y guardar al cerrar
// =============================================================================

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

// clase archivomanager: gestiona persistencia de datos
// responsabilidades: guardar y cargar clientes desde archivo
// formato archivo: texto plano con campos separados por '|'
class ArchivoManager {
public:
    // guardar clientes en archivo de texto
    // formato: id|nombre|apellido|email|codigo|fechaalta|tipo|campo1|campo2
    // complejidad: O(n) - recorre todos los clientes una vez
    // cada linea representa un cliente con todos sus datos
    void guardarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {
        ofstream file(archivo);
        if (!file.is_open()) {
            cout << "Error: No se pudo abrir el archivo para escritura.\n";
            return;
        }

        int guardados = 0;

        // recorrer lista de clientes
        for (int i = 0; i < lista.getTamano(); i++) {
            Cliente* cl = *lista.obtenerEnPosicion(i);
            if (!cl) continue;

            // escribir datos basicos del cliente
            file << cl->getId() << "|"
                 << cl->getNombre() << "|"
                 << cl->getApellido() << "|"
                 << cl->getEmail() << "|"
                 << cl->getCodigo() << "|"
                 << cl->getFechaAlta() << "|";

            // determinar tipo de persona y guardar campos especificos
            // usa dynamic_cast para identificar tipo en tiempo de ejecucion
            Persona* detalles = cl->getDetallesPersona();
            if (detalles) {
                PersonaNatural* pn = dynamic_cast<PersonaNatural*>(detalles);
                PersonaJuridica* pj = dynamic_cast<PersonaJuridica*>(detalles);

                if (pn) {
                    // tipo natural: guardar dni y fecha nacimiento
                    file << "NATURAL|" << pn->getDni() << "|" << pn->getFechaNac();
                } else if (pj) {
                    // tipo juridica: guardar ruc y razon social
                    file << "JURIDICA|" << pj->getRuc() << "|" << pj->getRazonSocial();
                } else {
                    // tipo desconocido (no deberia ocurrir)
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

    // cargar clientes desde archivo de texto
    // complejidad: O(n) donde n es el numero de lineas en el archivo
    // lee linea por linea y reconstruye objetos cliente
    void cargarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {
        ifstream file(archivo);
        if (!file.is_open()) {
            cout << "Aviso: No se encontro archivo previo '" << archivo << "'.\n";
            cout << "Se iniciara con datos vacios.\n";
            return;
        }

        string linea;
        int cargados = 0;

        // leer archivo linea por linea
        while (getline(file, linea)) {
            if (linea.empty()) continue;

            // usar stringstream para separar campos
            stringstream ss(linea);
            string id, nombre, apellido, email, codigo, fechaAlta, tipo, campo1, campo2;

            // leer campos separados por '|'
            getline(ss, id, '|');
            getline(ss, nombre, '|');
            getline(ss, apellido, '|');
            getline(ss, email, '|');
            getline(ss, codigo, '|');
            getline(ss, fechaAlta, '|');
            getline(ss, tipo, '|');
            getline(ss, campo1, '|');
            getline(ss, campo2, '|');

            // crear objeto persona segun tipo
            Persona* detalles = nullptr;

            if (tipo == "NATURAL") {
                // campo1 = dni, campo2 = fechanac
                detalles = new PersonaNatural(id, nombre, apellido, email, campo1, campo2);
            } else if (tipo == "JURIDICA") {
                // campo1 = ruc, campo2 = razonsocial
                detalles = new PersonaJuridica(id, nombre, apellido, email, campo1, campo2);
            } else {
                // tipo desconocido: crear personanatural por defecto
                detalles = new PersonaNatural(id, nombre, apellido, email, "00000000", "01/01/2000");
            }

            // crear cliente con los datos cargados
            Cliente* cl = new Cliente(id, nombre, apellido, email, codigo, fechaAlta, detalles);
            lista.insertarAlFinal(cl);
            cargados++;
        }

        file.close();
        cout << "=== DATOS CARGADOS ===\n";
        cout << "Archivo: " << archivo << "\n";
        cout << "Clientes cargados: " << cargados << "\n";
    }

    // *** algoritmo de ordenamiento adicional: selection sort ***
    // ordena clientes por codigo antes de guardar
    // complejidad: O(n^2) - dos bucles anidados
    // analisis detallado:
    //   - bucle externo: n iteraciones
    //   - bucle interno: (n-i) iteraciones promedio
    //   - total: n + (n-1) + (n-2) + ... + 1 = n(n+1)/2 = O(n^2)
    // justificacion de uso: simple de implementar, adecuado para listas pequeñas
    // no es el mas eficiente pero cumple proposito didactico
    void ordenarClientesSelection(ListaSimple<Cliente*>& lista) {
        int n = lista.getTamano();
        if (n <= 1) return;

        cout << "\n=== ORDENANDO ===\n";

        // algoritmo selection sort
        // en cada iteracion encuentra el minimo y lo coloca en su posicion
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            Cliente* minCliente = *lista.obtenerEnPosicion(minIdx);

            // buscar el minimo en el resto de la lista
            // recorre desde i+1 hasta n-1
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

            // intercambiar si se encontro un minimo diferente
            if (minIdx != i) {
                // obtener punteros a ambos clientes
                Cliente** ptrI = lista.obtenerEnPosicion(i);
                Cliente** ptrMin = lista.obtenerEnPosicion(minIdx);

                // intercambiar los punteros en la lista
                Cliente* temp = *ptrI;
                *ptrI = *ptrMin;
                *ptrMin = temp;
            }
        }

        cout << "Lista ordenada con Selection Sort (por codigo)\n";
    }

    // metodo auxiliar: verificar si archivo existe
    // complejidad: O(1) - operacion de sistema
    // util antes de intentar leer o respaldar
    bool archivoExiste(const string& archivo) {
        ifstream file(archivo);
        bool existe = file.good();
        file.close();
        return existe;
    }

    // metodo auxiliar: crear respaldo de archivo
    // complejidad: O(n) donde n es el tamaño del archivo
    // crea copia de seguridad con extension .bak
    void crearRespaldo(const string& archivoOriginal) {
        if (!archivoExiste(archivoOriginal)) {
            cout << "No hay archivo para respaldar.\n";
            return;
        }

        string archivoRespaldo = archivoOriginal + ".bak";

        // abrir archivos en modo binario para copia exacta
        ifstream origen(archivoOriginal, ios::binary);
        ofstream destino(archivoRespaldo, ios::binary);

        if (!origen.is_open() || !destino.is_open()) {
            cout << "Error al crear respaldo.\n";
            return;
        }

        // copiar contenido completo
        destino << origen.rdbuf();

        origen.close();
        destino.close();

        cout << "Respaldo creado: " << archivoRespaldo << "\n";
    }
};

#endif
