#include "SistemaFinanciero.h"
#include "PersonaNatural.h"
#include "PersonaJuridica.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    SistemaFinanciero sistema;
    int opcion;

    // contador para auto-generar IDs de clientes
    static int contadorID = 1;

    cout << "\n=== BIENVENIDO AL SISTEMA FINANCIERO CAJA HUANCAYO ===\n";

    do {
        sistema.mostrarMenuPrincipal();
        cout << "Seleccione categoria: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            // CATEGORIA 1: GESTION DE CLIENTES
            // Mostrar submenu primero
            int subopcion;
            Interfaz::mostrarTitulo("GESTION DE CLIENTES", 50);
            cout << "1. Registrar Nuevo Cliente\n";
            cout << "2. Abrir Cuenta Bancaria\n";
            cout << "3. Ver Reporte Ordenado de Clientes\n";
            cout << "4. Generar Clientes Aleatorios (Demo)\n";
            cout << "0. Volver al Menu Principal\n";
            Interfaz::mostrarSeparador('-', 50);
            cout << "Seleccione opcion: ";
            cin >> subopcion;

            if (subopcion == 1) {
                // Registrar cliente con ID auto-generado
                cout << "\n=== REGISTRAR NUEVO CLIENTE ===\n";

                string id = "CLI" + string(5 - to_string(contadorID).length(), '0') + to_string(contadorID);
                contadorID++;

                cout << "ID Auto-generado: " << id << "\n\n";

                string nombre, apellido, email, codigo, fecha;
                cout << "Nombre: "; cin >> nombre;
                cout << "Apellido: "; cin >> apellido;
                cout << "Email: "; cin >> email;
                cout << "Codigo de Cliente (ej: 121200): "; cin >> codigo;

                if (sistema.buscarPorCodigo(codigo) != nullptr) {
                    Interfaz::mostrarError("Ya existe un cliente con el codigo " + codigo);
                    contadorID--;
                    break;
                }

                cout << "Fecha Registro (DD/MM/AAAA): "; cin >> fecha;

                Cliente* nuevo = new Cliente(id, nombre, apellido, email, codigo, fecha);

                cout << "\nTipo de cliente (1 = persona natural, 2 = persona juridica): ";
                int tipo; cin >> tipo;

                if (tipo == 1) {
                    cout << "DNI: "; string dni; cin >> dni;
                    cout << "Fecha de nacimiento (DD/MM/AAAA): "; string fn; cin >> fn;
                    PersonaNatural* pn = new PersonaNatural(id, nombre, apellido, email, dni, fn);
                    nuevo->setDetallesPersona(pn);
                } else if (tipo == 2) {
                    cout << "RUC: "; string ruc; cin >> ruc;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Razon social: "; string razon; getline(cin, razon);
                    PersonaJuridica* pj = new PersonaJuridica(id, nombre, apellido, email, ruc, razon);
                    nuevo->setDetallesPersona(pj);
                }

                sistema.registrarNuevoCliente(nuevo);
            } else if (subopcion == 2) {
                sistema.abrirCuenta();
            } else if (subopcion == 3) {
                sistema.generarReporteOrdenado();
            } else if (subopcion == 4) {
                cout << "\nCuantos clientes desea generar? (1-50): ";
                int cantidad;
                cin >> cantidad;
                if (cantidad < 1 || cantidad > 50) {
                    Interfaz::mostrarAdvertencia("Cantidad invalida. Generando 10 clientes por defecto.");
                    cantidad = 10;
                }
                sistema.generarClientesAleatorios(cantidad);
                contadorID += cantidad; // Actualizar contador
            }
            break;
        }

        case 2: {
            // CATEGORIA 2: OPERACIONES BANCARIAS
            sistema.menuOperacionesBancarias();
            break;
        }

        case 3: {
            // CATEGORIA 3: PRESTAMOS
            sistema.menuPrestamos();
            break;
        }

        case 4: {
            // CATEGORIA 4: ADMINISTRACION
            sistema.menuAdministracion();
            break;
        }

        case 0: {
            Interfaz::mostrarTitulo("CERRANDO SISTEMA", 50);
            cout << "Gracias por usar el Sistema Financiero Caja Huancayo.\n";
            cout << "Hasta pronto!\n\n";
            break;
        }

        default:
            Interfaz::mostrarError("Opcion invalida. Intente nuevamente.");
        }


    } while (opcion != 0);

    return 0;
}