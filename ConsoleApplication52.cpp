#include "SistemaFinanciero.h"
#include "PersonaNatural.h"
#include "PersonaJuridica.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {

    SistemaFinanciero sistema;
    int opcion;

    static int contadorID = 1;


    cout << "\n=== BIENVENIDO AL SISTEMA FINANCIERO BUENAVISTA ===\n";

    do {

        sistema.mostrarMenuPrincipal();
        cout << "Seleccione categoria: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {


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

                // solicitar tipo de persona: natural (1) o juridica (2)
                cout << "\nTipo de cliente (1 = persona natural, 2 = persona juridica): ";
                int tipo; cin >> tipo;

                if (tipo == 1) {
                    // persona natural: solicitar dni y fecha nacimiento
                    cout << "DNI: "; string dni; cin >> dni;
                    cout << "Fecha de nacimiento (DD/MM/AAAA): "; string fn; cin >> fn;
                    PersonaNatural* pn = new PersonaNatural(id, nombre, apellido, email, dni, fn);
                    nuevo->setDetallesPersona(pn);
                } else if (tipo == 2) {
                    // persona juridica: solicitar ruc y razon social
                    cout << "RUC: "; string ruc; cin >> ruc;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Razon social: "; string razon; getline(cin, razon);
                    PersonaJuridica* pj = new PersonaJuridica(id, nombre, apellido, email, ruc, razon);
                    nuevo->setDetallesPersona(pj);
                }

                // registrar cliente en el sistema
                // usa listasimple con insercion optimizada O(1)
                sistema.registrarNuevoCliente(nuevo);

            } else if (subopcion == 2) {
                // abrir cuenta bancaria para cliente existente
                sistema.abrirCuenta();

            } else if (subopcion == 3) {
                // generar reporte de clientes ordenado
                // usa heapsort del integrante 3 para ordenar
                sistema.generarReporteOrdenado();

            } else if (subopcion == 4) {
                // generar clientes aleatorios para pruebas
                // usa algoritmo fisher-yates para desordenar
                cout << "\nCuantos clientes desea generar? (1-50): ";
                int cantidad;
                cin >> cantidad;
                if (cantidad < 1 || cantidad > 50) {
                    Interfaz::mostrarAdvertencia("Cantidad invalida. Generando 10 clientes por defecto.");
                    cantidad = 10;
                }
                sistema.generarClientesAleatorios(cantidad);
                contadorID += cantidad; // actualizar contador
            }
            break;
        }

        case 2: {
            // ===================================================================
            // categoria 2: operaciones bancarias
            // ===================================================================
            // incluye: depositos, retiros, procesamiento de cola, deshacer con pila
            // demuestra uso de estructuras cola (integrante 3) y pila (integrante 4)
            sistema.menuOperacionesBancarias();
            break;
        }

        case 3: {
            // ===================================================================
            // categoria 3: prestamos
            // ===================================================================
            // incluye: solicitar prestamo, ver cronograma, pagar cuotas
            // demuestra uso de quicksort (integrante 1) para ordenar cuotas
            sistema.menuPrestamos();
            break;
        }

        case 4: {
            // ===================================================================
            // categoria 4: administracion
            // ===================================================================
            // incluye: guardar datos, ver estado de estructuras
            // demuestra uso de archivos y persistencia de datos
            sistema.menuAdministracion();
            break;
        }

        case 0: {
            // ===================================================================
            // opcion 0: salir del sistema
            // ===================================================================
            Interfaz::mostrarTitulo("CERRANDO SISTEMA", 50);
            cout << "Gracias por usar el Sistema Financiero Buenavista.\n";
            cout << "Hasta pronto!\n\n";
            break;
        }

        default:
            // opcion invalida
            Interfaz::mostrarError("Opcion invalida. Intente nuevamente.");
        }

    } while (opcion != 0);  // continuar hasta que usuario seleccione salir

    // al salir del bucle, el destructor de sistema se ejecuta automaticamente
    // esto libera toda la memoria asignada dinamicamente
    return 0;
}