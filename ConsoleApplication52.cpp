#include "SistemaFinanciero.h"
#include <iostream>

using namespace std;

int main() {
    SistemaFinanciero sistema;
    int opcion;
    do {
        sistema.mostrarMenuPrincipal();
        cin >> opcion;
        switch (opcion) {
        case 1: {
            string id, nombre, apellido, email, codigo, fecha;
            cout << "ID: "; cin >> id;
            cout << "Nombre: "; cin >> nombre;
            cout << "Apellido: "; cin >> apellido;
            cout << "Email: "; cin >> email;
            cout << "Codigo: "; cin >> codigo;
            cout << "Fecha Registro: "; cin >> fecha;
            Cliente* nuevo = new Cliente(id, nombre, apellido, email, codigo, fecha);
            if (nuevo->validar()) sistema.registrarNuevoCliente(nuevo); // Pasa el cliente creado
            break;
        }
        case 5: sistema.generarReporteOrdenado(); break;
        case 6: /* Implementa guardar con ArchivoManager */ break;
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opción inválida\n"; break;
        }
    } while (opcion != 0);
    return 0;
}