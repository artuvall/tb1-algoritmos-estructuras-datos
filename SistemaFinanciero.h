#ifndef SISTEMAFINANCIERO_H
#define SISTEMAFINANCIERO_H
//SistemaFinanciero.h
#include "GestorClientes.h"
#include "ArchivoManager.h"
#include <iostream>

using namespace std;

class SistemaFinanciero {
private:
    GestorClientes gestor;
    ArchivoManager archiver;

public:
    void registrarNuevoCliente(Cliente* nuevo) { // Añadimos parámetro Cliente*
        if (nuevo->validar()) {
            gestor.registrarNuevoCliente(nuevo);
        }
    }

    void mostrarMenuPrincipal() {
        cout << string(40, '=') << "\n Sistema Caja Huancayo Minimal \n" << string(40, '=') << "\n";
        cout << "1. Registrar Cliente\n2. Abrir Cuenta\n3. Deposito/Retiro\n4. Solicitar Prestamo\n";
        cout << "5. Generar Reporte\n6. Guardar Datos\n0. Salir\n" << string(40, '-') << "\n";
    }

    void generarReporteOrdenado() { gestor.ordenarClientesHeap(); /* Imprimir. */ }

    bool incluirSesion(const string& cod) { // Lambda 3: Verificar sesión.
        auto check = [this, cod]() { return gestor.buscarPorCodigo(cod) != nullptr; };
        return check();
    }
};

#endif