#include "SistemaFinanciero.h"
#include <iostream>

using namespace std;

int main() {
    SistemaFinanciero sistema;
    int opcion;

    cout << "\n=== BIENVENIDO AL SISTEMA FINANCIERO ===\n";

    do {
        sistema.mostrarMenuPrincipal();
        cout << "Seleccione opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            // caso 1: registrar cliente
            cout << "\n=== REGISTRAR NUEVO CLIENTE ===\n";
            string id, nombre, apellido, email, codigo, fecha;
            cout << "ID: ";
            cin >> id;
            cout << "Nombre: ";
            cin >> nombre;
            cout << "Apellido: ";
            cin >> apellido;
            cout << "Email: ";
            cin >> email;
            cout << "Codigo: ";
            cin >> codigo;
            cout << "Fecha Registro (YYYY-MM-DD): ";
            cin >> fecha;

            Cliente* nuevo = new Cliente(id, nombre, apellido, email, codigo, fecha);
            sistema.registrarNuevoCliente(nuevo);
            break;
        }
        case 2: {
            // caso 2: abrir cuenta
            sistema.abrirCuenta();
            break;
        }
        case 3: {
            // caso 3: deposito/retiro
            sistema.depositoRetiro();
            break;
        }
        case 4: {
            // caso 4: solicitar prestamo
            sistema.solicitarPrestamo();
            break;
        }
        case 5: {
            // caso 5: generar reporte
            sistema.generarReporteOrdenado();
            break;
        }
        case 6: {
            // caso 6: guardar datos
            sistema.guardarDatos();
            break;
        }
        case 0: {
            cout << "\n=== SALIENDO DEL SISTEMA ===\n";
            cout << "Desea guardar los cambios antes de salir? (s/n): ";
            char respuesta;
            cin >> respuesta;
            if (respuesta == 's' || respuesta == 'S') {
                sistema.guardarDatos();
            }
            cout << "Gracias por usar el Sistema Financiero!\n";
            break;
        }
        default: {
            cout << "Opcion invalida. Intente nuevamente.\n";
            break;
        }
        }

        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcion != 0);

    return 0;
}