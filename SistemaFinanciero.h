#ifndef SISTEMAFINANCIERO_H
#define SISTEMAFINANCIERO_H
//SistemaFinanciero.h - Controlador principal del sistema
// OPTIMIZACION: Refactorizado para usar Interfaz y mejorar separacion de capas
#include "GestorClientes.h"
#include "ArchivoManager.h"
#include "CuentaAhorros.h"
#include "CuentaCorriente.h"
#include "Deposito.h"
#include "Retiro.h"
#include "Cola.h"
#include "Pila.h"
#include "HistoricoTransacciones.h"
#include "Interfaz.h"
#include "PersonaNatural.h"
#include "PersonaJuridica.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// estructura auxiliar para almacenar operacion deshacible
// MEJORA: Mejor gestion de memoria con comentarios claros
struct OperacionDeshacible {
    CuentaBancaria* cuenta;  // No se posee: pertenece al cliente
    Transaccion* transaccion;  // SE POSEE: debe liberarse en destructor
    bool esDeposito; // true = deposito, false = retiro

    OperacionDeshacible(CuentaBancaria* c, Transaccion* t, bool dep)
        : cuenta(c), transaccion(t), esDeposito(dep) {}

    // Destructor: liberar transaccion (cuenta no se libera)
    ~OperacionDeshacible() {
        // IMPORTANTE: Solo liberar transaccion, no cuenta
        // La cuenta pertenece al cliente y sera liberada alli
        delete transaccion;
    }
};

class SistemaFinanciero {
private:
    GestorClientes gestor;
    ArchivoManager archiver;

    // estructuras para manejo de transacciones (integrante 3 y 4)
    Cola<OperacionDeshacible*> colaTransacciones;  // transacciones pendientes
    Pila<OperacionDeshacible*> pilaDeshacer;       // operaciones deshacibles
    HistoricoTransacciones historicoGlobal;         // historial completo

public:
    // constructor: cargar datos existentes del archivo
    // Complejidad: O(n) donde n es cantidad de clientes en archivo
    SistemaFinanciero() {
        cout << "\n=== INICIANDO SISTEMA ===\n";
        archiver.cargarClientesArchivo("clientes.txt", gestor.getListaClientes());
        srand(time(0)); // Inicializar seed para numeros aleatorios
    }

    // NUEVO: Generar clientes aleatorios para pruebas
    // Complejidad: O(n) donde n es cantidad de clientes a generar
    void generarClientesAleatorios(int cantidad = 10) {
        Interfaz::mostrarTitulo("GENERADOR DE CLIENTES ALEATORIOS", 50);

        string nombres[] = {"Juan", "Maria", "Pedro", "Ana", "Carlos", "Lucia", "Jorge", "Sofia", "Luis", "Carmen",
                           "Diego", "Elena", "Miguel", "Rosa", "Fernando", "Isabel", "Roberto", "Patricia"};
        string apellidos[] = {"Garcia", "Rodriguez", "Martinez", "Lopez", "Gonzalez", "Perez", "Sanchez", "Ramirez",
                             "Torres", "Flores", "Rivera", "Gomez", "Diaz", "Cruz", "Morales", "Reyes"};
        string empresas[] = {"Tecnologia", "Construcciones", "Comercial", "Servicios", "Telecomunicaciones",
                            "Inversiones", "Logistica", "Consultoria", "Industrias", "Distribuidora"};

        cout << "Generando " << cantidad << " clientes aleatorios...\n\n";

        // crear array temporal para almacenar clientes antes de desordenar
        Cliente** tempClientes = new Cliente*[cantidad];
        int clientesCreados = 0;

        for (int i = 0; i < cantidad; i++) {
            // Generar ID unico
            static int contadorID = 1000;
            string id = "CLI" + to_string(contadorID++);

            // Seleccionar nombre y apellido aleatorio
            string nombre = nombres[rand() % 18];
            string apellido = apellidos[rand() % 16];

            // Generar email
            string email = nombre + apellido + to_string(rand() % 1000) + "@mail.com";
            for (auto& c : email) c = tolower(c);

            // Generar codigo de cliente (6 digitos)
            string codigo = to_string(100000 + rand() % 900000);

            // Fecha aleatoria entre 2020-2025
            int dia = 1 + rand() % 28;
            int mes = 1 + rand() % 12;
            int anio = 2020 + rand() % 6;
            string fecha = (dia < 10 ? "0" : "") + to_string(dia) + "/" +
                          (mes < 10 ? "0" : "") + to_string(mes) + "/" + to_string(anio);

            // Crear cliente base primero
            Cliente* nuevoCliente = new Cliente(id, nombre, apellido, email, codigo, fecha);

            // 70% personas naturales, 30% juridicas
            if (rand() % 10 < 7) {
                // Persona Natural
                string dni = to_string(10000000 + rand() % 90000000);
                string fechaNac = to_string(1 + rand() % 28) + "/" + to_string(1 + rand() % 12) + "/" +
                                 to_string(1960 + rand() % 40);
                PersonaNatural* pn = new PersonaNatural(id, nombre, apellido, email, dni, fechaNac);
                nuevoCliente->setDetallesPersona(pn);
            } else {
                // Persona Juridica
                string ruc = to_string(20000000000LL + rand() % 10000000000LL);
                string razonSocial = empresas[rand() % 10] + " " + apellido + " SAC";
                PersonaJuridica* pj = new PersonaJuridica(id, nombre, apellido, email, ruc, razonSocial);
                nuevoCliente->setDetallesPersona(pj);
            }

            if (nuevoCliente->validar()) {
                // 80% tienen al menos una cuenta
                if (rand() % 10 < 8) {
                    static int contadorCuenta = 50000;
                    string numCuenta = to_string(contadorCuenta++);
                    double saldoInicial = (rand() % 50000) + 500.0; // Entre S/ 500 y S/ 50,500

                    CuentaBancaria* cuenta = nullptr;
                    if (rand() % 2 == 0) {
                        cuenta = new CuentaAhorros(numCuenta, saldoInicial, nuevoCliente->getNombre(), fecha, 0.05);
                    } else {
                        cuenta = new CuentaCorriente(numCuenta, saldoInicial, nuevoCliente->getNombre(), fecha, 1000.0);
                    }
                    nuevoCliente->agregarCuenta(cuenta);
                }

                tempClientes[clientesCreados] = nuevoCliente;
                clientesCreados++;
            }
        }

        // algoritmo fisher-yates shuffle para desordenar clientes antes de registrarlos
        // esto hace que los clientes no se registren en orden de creacion
        for (int i = clientesCreados - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            // intercambiar tempClientes[i] con tempClientes[j]
            Cliente* temp = tempClientes[i];
            tempClientes[i] = tempClientes[j];
            tempClientes[j] = temp;
        }

        // registrar clientes en orden desordenado
        for (int i = 0; i < clientesCreados; i++) {
            gestor.registrarNuevoCliente(tempClientes[i]);
            cout << "[" << (i+1) << "/" << clientesCreados << "] "
                 << tempClientes[i]->getNombre() << " " << tempClientes[i]->getApellido()
                 << " (Codigo: " << tempClientes[i]->getCodigo() << ")\n";
        }

        delete[] tempClientes;

        Interfaz::mostrarExito("Clientes generados exitosamente!");
        Interfaz::mostrarEstadistica("Total generados", clientesCreados);
        Interfaz::mostrarEstadistica("Total en sistema", gestor.getListaClientes().getTamano());

    }

    // NUEVO: Generar transacciones aleatorias para pruebas
    // Complejidad: O(n * m) donde n es cantidad de transacciones, m es busqueda de clientes
    void generarTransaccionesAleatorias(int cantidad = 10) {
        Interfaz::mostrarTitulo("GENERADOR DE TRANSACCIONES ALEATORIAS", 50);

        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados. Registre clientes primero.");
            return;
        }

        // contar clientes con cuentas
        int clientesConCuentas = 0;
        auto contarCuentas = [&clientesConCuentas](Cliente* c) {
            if (c->getCantidadCuentas() > 0) clientesConCuentas++;
        };
        gestor.getListaClientes().imprimir(contarCuentas);

        if (clientesConCuentas == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes con cuentas. Abra cuentas primero.");
            return;
        }

        cout << "Generando " << cantidad << " transacciones aleatorias...\n\n";

        string metodos[] = {"Efectivo", "Transferencia", "Cheque", "Cajero"};
        int transaccionesGeneradas = 0;

        for (int i = 0; i < cantidad; i++) {
            // seleccionar cliente aleatorio con cuentas
            Cliente* cliente = nullptr;
            int intentos = 0;
            while (!cliente || cliente->getCantidadCuentas() == 0) {
                if (intentos++ > 100) {
                    Interfaz::mostrarAdvertencia("No se pudieron generar todas las transacciones.");
                    break;
                }
                int indiceCliente = rand() % gestor.getListaClientes().getTamano();
                cliente = *gestor.getListaClientes().obtenerEnPosicion(indiceCliente);
            }

            if (!cliente || cliente->getCantidadCuentas() == 0) continue;

            // seleccionar cuenta aleatoria del cliente
            int indiceCuenta = rand() % cliente->getCantidadCuentas();
            CuentaBancaria* cuenta = cliente->obtenerCuenta(indiceCuenta);

            if (!cuenta) continue;

            // generar tipo de transaccion (60% depositos, 40% retiros)
            bool esDeposito = (rand() % 10 < 6);

            // generar monto aleatorio
            double monto;
            if (esDeposito) {
                monto = (rand() % 10000) + 100.0; // entre s/ 100 y s/ 10,100
            } else {
                // para retiros, usar un porcentaje del saldo
                double maxRetiro = cuenta->getSaldo() * 0.5; // hasta 50% del saldo
                if (maxRetiro < 100) maxRetiro = 100;
                monto = (rand() % (int)maxRetiro) + 50.0;
            }

            // generar fecha completamente aleatoria entre 2000 y 2025
            // esto garantiza maxima diversidad de fechas para que mergesort sea muy visible
            int anio = 2000 + rand() % 26; // año entre 2000 y 2025
            int mes = 1 + rand() % 12; // mes entre 1 y 12
            int dia = 1 + rand() % 28; // dia entre 1 y 28 (evita problemas con febrero)

            string fecha = (dia < 10 ? "0" : "") + to_string(dia) + "/" +
                          (mes < 10 ? "0" : "") + to_string(mes) + "/" + to_string(anio);

            // seleccionar metodo aleatorio
            string metodo = metodos[rand() % 4];

            // crear y encolar transaccion
            Transaccion* nuevaTransaccion = nullptr;
            string tipoOperacion = esDeposito ? "Deposito" : "Retiro";

            if (esDeposito) {
                string idTrans = "DEP-" + cuenta->getNumCuenta() + "-" + to_string(colaTransacciones.getTamano() + 1);
                nuevaTransaccion = new Deposito(idTrans, monto, fecha, tipoOperacion, metodo);
            } else {
                string idTrans = "RET-" + cuenta->getNumCuenta() + "-" + to_string(colaTransacciones.getTamano() + 1);
                nuevaTransaccion = new Retiro(idTrans, monto, fecha, tipoOperacion, metodo);
            }

            OperacionDeshacible* op = new OperacionDeshacible(cuenta, nuevaTransaccion, esDeposito);
            colaTransacciones.encolar(op);

            transaccionesGeneradas++;
            cout << "[" << (i+1) << "/" << cantidad << "] "
                 << tipoOperacion << " S/ " << fixed << setprecision(2) << monto
                 << " en cuenta " << cuenta->getNumCuenta()
                 << " (Fecha: " << fecha << ")\n";
        }

        Interfaz::mostrarExito("Transacciones generadas exitosamente!");
        Interfaz::mostrarEstadistica("Total generadas", transaccionesGeneradas);
        Interfaz::mostrarEstadistica("En cola de procesamiento", colaTransacciones.getTamano());

    }

    // NUEVO: Generar prestamos aleatorios para pruebas
    // Complejidad: O(n * m) donde n es cantidad de prestamos, m es generacion de cuotas
    void generarPrestamosAleatorios(int cantidad = 5) {
        Interfaz::mostrarTitulo("GENERADOR DE PRESTAMOS ALEATORIOS", 50);

        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados. Registre clientes primero.");
            return;
        }

        cout << "Generando " << cantidad << " prestamos aleatorios...\n\n";

        string tiposGarantia[] = {"Vehiculo", "Inmueble", "Aval", "Hipoteca"};
        int prestamosGenerados = 0;

        for (int i = 0; i < cantidad; i++) {
            // Seleccionar cliente aleatorio
            int indiceCliente = rand() % gestor.getListaClientes().getTamano();
            Cliente* cliente = *gestor.getListaClientes().obtenerEnPosicion(indiceCliente);

            if (!cliente) continue;

            // Generar monto aleatorio (entre S/ 1,000 y S/ 50,000)
            double monto = (rand() % 49000) + 1000.0;

            // Generar plazo aleatorio (entre 6 y 48 meses)
            int plazo = 6 + (rand() % 43); // 6 a 48 meses

            // Generar tasa aleatoria (entre 8% y 25%)
            double tasa = 0.08 + (rand() % 18) / 100.0;

            // Generar ID unico
            string idPrestamo = "PREST-" + cliente->getCodigo() + "-" + to_string(cliente->getCantidadPrestamos() + 1);

            Prestamo* nuevoPrestamo = new Prestamo(idPrestamo, monto, tasa, plazo, "Aprobado");

            // 70% tienen garantia
            if (rand() % 10 < 7) {
                string tipo = tiposGarantia[rand() % 4];
                double valorGarantia = monto * (1.2 + (rand() % 5) / 10.0); // 120% a 170% del monto
                Garantia* g = new Garantia(tipo, valorGarantia);
                nuevoPrestamo->setGarantia(g);
            }

            // Generar cuotas
            nuevoPrestamo->generarCuotas();

            // Agregar al cliente
            cliente->agregarPrestamo(nuevoPrestamo);

            prestamosGenerados++;
            cout << "[" << (i+1) << "/" << cantidad << "] "
                 << "Prestamo S/ " << monto << " a " << plazo << " meses para "
                 << cliente->getNombre() << "\n";
        }

        Interfaz::mostrarExito("Prestamos generados exitosamente!");
        Interfaz::mostrarEstadistica("Total generados", prestamosGenerados);
        Interfaz::mostrarEstadistica("Clientes con prestamos", gestor.getListaClientes().getTamano());

        cout << "\nPuede ver los prestamos en el menu de Gestion de Prestamos.\n";
    }

    // Registrar nuevo cliente con validacion
    // Complejidad: O(1) - insercion al final optimizada
    void registrarNuevoCliente(Cliente* nuevo) {
        if (nuevo->validar()) {
            gestor.registrarNuevoCliente(nuevo);
            Interfaz::mostrarExito("Cliente registrado exitosamente!");
        } else {
            Interfaz::mostrarError("Cliente no valido. Verifique los datos.");
        }
    }

    // metodo para buscar cliente por codigo (expone funcionalidad del gestor)
    // Complejidad: O(n) - busqueda lineal
    Cliente* buscarPorCodigo(const string& codigo) {
        return gestor.buscarPorCodigo(codigo);
    }

    // NUEVO: Mostrar menu principal reorganizado por categorias
    void mostrarMenuPrincipal() {
        Interfaz::mostrarTitulo("CAJA BUENAVISTA - Sistema Financiero", 60);
        cout << "\n";
        cout << "  [1] GESTION DE CLIENTES\n";
        cout << "      - Registrar Cliente\n";
        cout << "      - Abrir Cuenta\n";
        cout << "      - Ver Reporte de Clientes\n";
        cout << "\n";
        cout << "  [2] OPERACIONES BANCARIAS\n";
        cout << "      - Depositos y Retiros\n";
        cout << "      - Historial de Transacciones\n";
        cout << "\n";
        cout << "  [3] PRESTAMOS\n";
        cout << "      - Solicitar Prestamo\n";
        cout << "      - Ver Cronograma\n";
        cout << "      - Pagar Cuota\n";
        cout << "\n";
        cout << "  [4] ADMINISTRACION\n";
        cout << "      - Procesar Transacciones\n";
        cout << "      - Guardar Datos\n";
        cout << "      - Configuracion Avanzada\n";
        cout << "\n";
        cout << "  [0] Salir del Sistema\n";
        Interfaz::mostrarSeparador('-', 60);
    }

    // NUEVO: Menu de Gestion de Clientes
    void menuGestionClientes() {
        int opcion;
        do {
            Interfaz::mostrarTitulo("GESTION DE CLIENTES", 50);
            cout << "1. Registrar Nuevo Cliente\n";
            cout << "2. Abrir Cuenta Bancaria\n";
            cout << "3. Ver Reporte de Clientes\n";
            cout << "0. Volver al Menu Principal\n";
            Interfaz::mostrarSeparador('-', 50);
            cout << "Seleccione opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    // Esta funcion se llama desde main con toda la logica
                    Interfaz::mostrarAdvertencia("Por favor use la opcion 1 del menu principal");
                    break;
                case 2:
                    abrirCuenta();
                    break;
                case 3: {
                    // Submenu de reporte
                    Interfaz::mostrarTitulo("REPORTE DE CLIENTES", 50);
                    cout << "1. Ver clientes (orden actual)\n";
                    cout << "2. Ordenar por codigo\n";
                    cout << "Seleccione opcion: ";
                    int subopcion;
                    cin >> subopcion;

                    if (subopcion == 1) {
                        gestor.imprimirClientes();
                        Interfaz::mostrarEstadistica("Total de clientes", gestor.contarClientesActivos());
                    } else if (subopcion == 2) {
                        cout << "\nOrdenando clientes por codigo...\n";
                        gestor.ordenarClientesHeap(); // HeapSort
                        cout << "\n=== CLIENTES ORDENADOS ===\n";
                        gestor.imprimirClientes();
                        Interfaz::mostrarEstadistica("Total de clientes", gestor.contarClientesActivos());
                        Interfaz::mostrarExito("Clientes ordenados exitosamente!");
                    }
                    break;
                }
                case 0:
                    cout << "Volviendo al menu principal...\n";
                    break;
                default:
                    Interfaz::mostrarError("Opcion invalida");
            }
        } while (opcion != 0);
    }

    // NUEVO: Menu de Operaciones Bancarias
    void menuOperacionesBancarias() {
        int opcion;
        do {
            Interfaz::mostrarTitulo("OPERACIONES BANCARIAS", 50);
            cout << "1. Realizar Deposito o Retiro\n";
            cout << "2. Procesar Siguiente Transaccion\n";
            cout << "3. Deshacer Ultima Operacion\n";
            cout << "4. Ver Historial Global\n";
            cout << "5. Ver Historial de Cuenta\n";
            cout << "6. Generar Transacciones Aleatorias (Demo)\n";
            cout << "0. Volver al Menu Principal\n";
            Interfaz::mostrarSeparador('-', 50);
            cout << "Seleccione opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    depositoRetiro();
                    break;
                case 2:
                    procesarSiguienteTransaccion();
                    break;
                case 3:
                    deshacerUltimaOperacion();
                    break;
                case 4:
                    verHistorialGlobal();
                    break;
                case 5:
                    verHistorialCuenta();
                    break;
                case 6: {
                    cout << "\nCuantas transacciones desea generar? (1-50): ";
                    int cantidad;
                    cin >> cantidad;
                    if (cantidad < 1 || cantidad > 50) {
                        Interfaz::mostrarAdvertencia("Cantidad invalida. Generando 10 transacciones por defecto.");
                        cantidad = 10;
                    }
                    generarTransaccionesAleatorias(cantidad);
                    break;
                }
                case 0:
                    cout << "Volviendo al menu principal...\n";
                    break;
                default:
                    Interfaz::mostrarError("Opcion invalida");
            }
        } while (opcion != 0);
    }

    // NUEVO: Menu de Prestamos
    void menuPrestamos() {
        int opcion;
        do {
            Interfaz::mostrarTitulo("GESTION DE PRESTAMOS", 50);
            cout << "1. Solicitar Prestamo\n";
            cout << "2. Ver Cronograma de Pagos\n";
            cout << "3. Pagar Cuota de Prestamo\n";
            cout << "4. Generar Prestamos Aleatorios (Demo)\n";
            cout << "0. Volver al Menu Principal\n";
            Interfaz::mostrarSeparador('-', 50);
            cout << "Seleccione opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    solicitarPrestamo();
                    break;
                case 2:
                    verCronograma();
                    break;
                case 3:
                    pagarCuotaPrestamo();
                    break;
                case 4: {
                    cout << "\nCuantos prestamos desea generar? (1-20): ";
                    int cantidad;
                    cin >> cantidad;
                    if (cantidad < 1 || cantidad > 20) {
                        Interfaz::mostrarAdvertencia("Cantidad invalida. Generando 5 prestamos por defecto.");
                        cantidad = 5;
                    }
                    generarPrestamosAleatorios(cantidad);
                    break;
                }
                case 0:
                    cout << "Volviendo al menu principal...\n";
                    break;
                default:
                    Interfaz::mostrarError("Opcion invalida");
            }
        } while (opcion != 0);
    }

    // NUEVO: Menu de Administracion
    void menuAdministracion() {
        int opcion;
        do {
            Interfaz::mostrarTitulo("ADMINISTRACION DEL SISTEMA", 50);
            cout << "1. Guardar Datos en Archivo\n";
            cout << "2. Ver Estado de Cola de Transacciones\n";
            cout << "3. Ver Estado de Pila de Deshacer\n";
            cout << "0. Volver al Menu Principal\n";
            Interfaz::mostrarSeparador('-', 50);
            cout << "Seleccione opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    guardarDatos();
                    break;
                case 2:
                    mostrarEstadoCola();
                    break;
                case 3:
                    mostrarEstadoPila();
                    break;
                case 0:
                    cout << "Volviendo al menu principal...\n";
                    break;
                default:
                    Interfaz::mostrarError("Opcion invalida");
            }
        } while (opcion != 0);
    }


    // NUEVO: Mostrar estado de cola de transacciones
    void mostrarEstadoCola() {
        Interfaz::mostrarTitulo("ESTADO DE COLA DE TRANSACCIONES", 50);
        Interfaz::mostrarEstadistica("Transacciones pendientes", colaTransacciones.getTamano());

        if (colaTransacciones.getTamano() > 0) {
            cout << "\nLas transacciones seran procesadas en orden primero en entrar, primero en salir\n";
            cout << "Use 'Procesar Siguiente Transaccion' en el menu de Operaciones Bancarias\n";
        } else {
            cout << "\nNo hay transacciones pendientes en la cola.\n";
        }
    }

    // NUEVO: Mostrar estado de pila de deshacer
    void mostrarEstadoPila() {
        Interfaz::mostrarTitulo("ESTADO DE PILA DE DESHACER", 50);
        Interfaz::mostrarEstadistica("Operaciones deshacibles", pilaDeshacer.getTamano());

        if (pilaDeshacer.getTamano() > 0) {
            cout << "\nLas operaciones se deshacen en orden ultima en entrar, primera en salir\n";
            cout << "Use 'Deshacer Ultima Operacion' en el menu de Operaciones Bancarias\n";
        } else {
            cout << "\nNo hay operaciones para deshacer.\n";
        }
    }

    // REFACTORIZADO: caso 2 - abrir cuenta para cliente existente
    // Logica de UI extraida a Interfaz para mayor claridad
    // Complejidad: O(n) por busqueda de cliente
    void abrirCuenta() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados. Registre un cliente primero.");
            return;
        }

        // Usar Interfaz para solicitar datos
        string codigo = Interfaz::solicitarCodigo();
        Cliente* cliente = gestor.buscarPorCodigo(codigo);

        if (!cliente) {
            Interfaz::mostrarError("Cliente no encontrado.");
            return;
        }

        int tipo = Interfaz::solicitarTipoCuenta();

        // auto-generar numero de cuenta unico
        static int contadorCuenta = 10000;
        string numCuenta = to_string(contadorCuenta);
        contadorCuenta++;

        cout << "\nNumero de cuenta auto-generado: " << numCuenta << "\n";

        double saldoInicial = Interfaz::solicitarMonto("saldo inicial");

        CuentaBancaria* nuevaCuenta = nullptr;

        if (tipo == 1) {
            // cuenta de ahorros con 5% de interes anual
            nuevaCuenta = new CuentaAhorros(numCuenta, saldoInicial, cliente->getNombre(), "01/01/2025", 0.05);
        } else if (tipo == 2) {
            // cuenta corriente con sobregiro de S/ 1000
            nuevaCuenta = new CuentaCorriente(numCuenta, saldoInicial, cliente->getNombre(), "01/01/2025", 1000.0);
        }

        if (nuevaCuenta) {
            cliente->agregarCuenta(nuevaCuenta);
            Interfaz::mostrarExito("Cuenta abierta exitosamente!");
            Interfaz::mostrarEstadistica("Numero de Cuenta", numCuenta);
            Interfaz::mostrarEstadistica("Saldo Inicial", saldoInicial);
        }
    }

    // REFACTORIZADO: caso 3 - realizar deposito o retiro (encola en vez de ejecutar)
    // Complejidad: O(n) por busqueda de cliente + O(1) encolar
    void depositoRetiro() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados.");
            return;
        }

        string codigo = Interfaz::solicitarCodigo();
        Cliente* cliente = gestor.buscarPorCodigo(codigo);

        if (!cliente) {
            Interfaz::mostrarError("Cliente no encontrado.");
            return;
        }

        cliente->listarCuentas();
        if (cliente->getCantidadCuentas() == 0) {
            Interfaz::mostrarAdvertencia("Este cliente no tiene cuentas. Abra una cuenta primero.");
            return;
        }

        int indiceCuenta = Interfaz::solicitarIndice("cuenta", 1, cliente->getCantidadCuentas());
        CuentaBancaria* cuenta = cliente->obtenerCuenta(indiceCuenta - 1);

        if (!cuenta) {
            Interfaz::mostrarError("Cuenta no valida.");
            return;
        }

        int operacion = Interfaz::mostrarMenuOperaciones();
        double monto = Interfaz::solicitarMonto();
        string fechaTransaccion = Interfaz::solicitarFecha("transaccion");
        string metodo = Interfaz::solicitarTexto("metodo (Efectivo/Transferencia/Cheque/Cajero)");

        // crear la transaccion segun tipo
        Transaccion* nuevaTransaccion = nullptr;
        bool esDeposito = (operacion == 1);
        string tipoOperacion = esDeposito ? "Deposito" : "Retiro";

        if (esDeposito) {
            string idTrans = "DEP-" + cuenta->getNumCuenta() + "-" + to_string(colaTransacciones.getTamano() + 1);
            nuevaTransaccion = new Deposito(idTrans, monto, fechaTransaccion, tipoOperacion, metodo);
        } else {
            string idTrans = "RET-" + cuenta->getNumCuenta() + "-" + to_string(colaTransacciones.getTamano() + 1);
            nuevaTransaccion = new Retiro(idTrans, monto, fechaTransaccion, tipoOperacion, metodo);
        }

        // encolar operacion pendiente
        OperacionDeshacible* op = new OperacionDeshacible(cuenta, nuevaTransaccion, esDeposito);
        colaTransacciones.encolar(op);

        Interfaz::mostrarExito("Transaccion encolada exitosamente!");
        Interfaz::mostrarEstadistica("ID Transaccion", nuevaTransaccion->getId());
        Interfaz::mostrarEstadistica("Tipo", tipoOperacion);
        Interfaz::mostrarEstadistica("Monto", monto);
        Interfaz::mostrarEstadistica("Transacciones pendientes", colaTransacciones.getTamano());

        cout << "\nUse 'Procesar Siguiente Transaccion' en Operaciones Bancarias.\n";
    }

    // caso 4: solicitar prestamo (actualizado con cuotas y garantia)
    // Complejidad: O(n) por busqueda + O(m) por generacion de cuotas
    void solicitarPrestamo() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados.");
            return;
        }

        string codigo = Interfaz::solicitarCodigo();
        Cliente* cliente = gestor.buscarPorCodigo(codigo);

        if (!cliente) {
            Interfaz::mostrarError("Cliente no encontrado.");
            return;
        }

        Interfaz::mostrarTitulo("SOLICITUD DE PRESTAMO", 40);

        double monto = Interfaz::solicitarMonto("prestamo");

        if (monto <= 0) {
            Interfaz::mostrarError("Monto invalido.");
            return;
        }

        cout << "Ingrese plazo en meses (6-48): ";
        int plazo;
        cin >> plazo;

        if (plazo < 6 || plazo > 48) {
            Interfaz::mostrarError("Plazo invalido. Debe estar entre 6 y 48 meses.");
            return;
        }

        cout << "Ingrese tasa de interes anual (ej: 0.12 para 12%): ";
        double tasa;
        cin >> tasa;

        if (tasa < 0.05 || tasa > 0.30) {
            Interfaz::mostrarError("Tasa invalida. Debe estar entre 5% y 30% (0.05 - 0.30).");
            return;
        }

        // generar id unico para prestamo
        string idPrestamo = "PREST" + to_string(cliente->getCantidadPrestamos() + 1);
        Prestamo* nuevoPrestamo = new Prestamo(idPrestamo, monto, tasa, plazo, "Pendiente");

        // verificar aprobacion con lambda
        if (!nuevoPrestamo->solicitar()) {
            Interfaz::mostrarAdvertencia("Prestamo rechazado. El monto excede el limite permitido (S/ 10,000).");
            delete nuevoPrestamo;
            return;
        }

        // solicitar garantia opcional
        if (Interfaz::solicitarConfirmacion("Desea adjuntar garantia?")) {
            string tipoGarantia = Interfaz::solicitarTexto("tipo de garantia (Vehiculo/Inmueble/Aval)");
            double valorGarantia = Interfaz::solicitarMonto("valor de la garantia");

            if (valorGarantia < monto * 1.2) {
                Interfaz::mostrarAdvertencia("El valor de la garantia es menor al 120% del prestamo.");
                cout << "Se recomienda una garantia de al menos S/ " << (monto * 1.2) << "\n";
            }

            Garantia* g = new Garantia(tipoGarantia, valorGarantia);
            nuevoPrestamo->setGarantia(g);
            cout << "Garantia adjuntada exitosamente.\n";
        }

        // generar cuotas automaticamente
        nuevoPrestamo->generarCuotas();
        cliente->agregarPrestamo(nuevoPrestamo);

        Interfaz::mostrarExito("Prestamo aprobado exitosamente!");
        Interfaz::mostrarEstadistica("ID Prestamo", idPrestamo);
        Interfaz::mostrarEstadistica("Monto", monto);
        cout << "| Tasa                               | " << (tasa * 100) << "% anual\n";
        cout << "| Plazo                              | " << plazo << " meses\n";
        Interfaz::mostrarEstadistica("Monto Total a Pagar", nuevoPrestamo->calcularMontoTotal());
        Interfaz::mostrarEstadistica("Cuota Mensual", nuevoPrestamo->calcularMontoTotal() / plazo);
        Interfaz::mostrarEstadistica("Cantidad de Cuotas", nuevoPrestamo->getCantidadCuotas());

        if (nuevoPrestamo->getGarantia()) {
            cout << "\nGarantia: ";
            nuevoPrestamo->getGarantia()->mostrarInfo();
            cout << "\n";
        }

        cout << "\nUse la opcion 10 para ver el cronograma completo de pagos.\n";
    }

    // caso 5: generar reporte ordenado con HeapSort
    // Complejidad: O(n log n) por ordenamiento
    void generarReporteOrdenado() {
        Interfaz::mostrarTitulo("REPORTE ORDENADO DE CLIENTES", 50);
        gestor.ordenarClientesHeap(); // ordenar con heapsort integrante 3
        gestor.imprimirClientes();
        Interfaz::mostrarEstadistica("Total de clientes", gestor.contarClientesActivos());
    }

    // caso 6: guardar datos en archivo
    // Complejidad: O(n log n) por Selection Sort + O(n) por escritura
    void guardarDatos() {
        Interfaz::mostrarTitulo("GUARDANDO DATOS", 40);
        archiver.ordenarClientesSelection(gestor.getListaClientes()); // ordenar antes de guardar
        archiver.guardarClientesArchivo("clientes.txt", gestor.getListaClientes());
    }

    // caso 7: procesar siguiente transaccion de la cola
    // Complejidad: O(1) - desencolar y ejecutar son operaciones constantes
    void procesarSiguienteTransaccion() {
        if (colaTransacciones.estaVacia()) {
            Interfaz::mostrarAdvertencia("No hay transacciones pendientes en la cola.");
            return;
        }

        Interfaz::mostrarTitulo("PROCESANDO TRANSACCION", 40);

        // desencolar siguiente operacion (O(1))
        OperacionDeshacible* op = colaTransacciones.desencolar();

        cout << "Procesando: " << op->transaccion->getId() << "\n";
        cout << "Tipo: " << (op->esDeposito ? "Deposito" : "Retiro") << "\n";
        cout << "Monto: S/ " << op->transaccion->getMonto() << "\n";

        // ejecutar segun tipo
        bool exito = false;
        if (op->esDeposito) {
            exito = op->cuenta->depositar(op->transaccion->getMonto());
        } else {
            exito = op->cuenta->retirar(op->transaccion->getMonto());
        }

        if (exito) {
            // agregar transaccion al historial de la cuenta (con la fecha correcta)
            op->cuenta->agregarTransaccion(op->transaccion);

            // agregar a historial global
            historicoGlobal.agregar(op->transaccion);

            // guardar en pila para deshacer (transferir propiedad)
            pilaDeshacer.push(op);

            Interfaz::mostrarExito("Transaccion procesada exitosamente!");
            Interfaz::mostrarEstadistica("Nuevo saldo", op->cuenta->getSaldo());
            Interfaz::mostrarEstadistica("Transacciones en cola", colaTransacciones.getTamano());
            Interfaz::mostrarEstadistica("Operaciones deshacibles", pilaDeshacer.getTamano());
        } else {
            Interfaz::mostrarError("La transaccion no pudo ejecutarse.");
            cout << "Posibles causas: fondos insuficientes o limites excedidos.\n";
            // IMPORTANTE: liberar memoria si fallo
            delete op; // el destructor de OperacionDeshacible libera la transaccion
        }
    }

    // caso 8: deshacer ultima operacion procesada
    // Complejidad: O(1) - pop y operacion inversa son constantes
    void deshacerUltimaOperacion() {
        if (pilaDeshacer.estaVacia()) {
            Interfaz::mostrarAdvertencia("No hay operaciones para deshacer.");
            return;
        }

        Interfaz::mostrarTitulo("DESHACIENDO OPERACION", 40);

        // obtener ultima operacion
        OperacionDeshacible* op = pilaDeshacer.pop();

        cout << "Deshaciendo: " << op->transaccion->getId() << "\n";
        cout << "Monto: S/ " << op->transaccion->getMonto() << "\n";

        // revertir segun tipo (deposito se convierte en retiro y viceversa)
        bool exito = false;
        if (op->esDeposito) {
            // deshacer deposito = retirar el monto
            exito = op->cuenta->retirar(op->transaccion->getMonto());
            cout << "Revirtiendo deposito...\n";
        } else {
            // deshacer retiro = depositar el monto
            exito = op->cuenta->depositar(op->transaccion->getMonto());
            cout << "Revirtiendo retiro...\n";
        }

        if (exito) {
            Interfaz::mostrarExito("Operacion deshecha exitosamente!");
            Interfaz::mostrarEstadistica("Nuevo saldo", op->cuenta->getSaldo());
            Interfaz::mostrarEstadistica("Operaciones restantes", pilaDeshacer.getTamano());

            // IMPORTANTE: liberar memoria
            delete op; // el destructor libera la transaccion
        } else {
            Interfaz::mostrarError("No se pudo deshacer la operacion.");
            // devolver a la pila si fallo
            pilaDeshacer.push(op);
        }
    }

    // caso 9: ver historial global de transacciones (con ShellSort)
    // Complejidad: O(n) donde n es cantidad de transacciones
    void verHistorialGlobal() {
        Interfaz::mostrarTitulo("HISTORIAL GLOBAL", 50);

        if (historicoGlobal.getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay transacciones procesadas aun.");
            return;
        }

        // Submenu para ordenar
        cout << "1. Ver historial (orden actual)\n";
        cout << "2. Ordenar por monto\n";
        cout << "Seleccione opcion: ";
        int subopcion;
        cin >> subopcion;

        if (subopcion == 2) {
            cout << "\nOrdenando transacciones por monto...\n";
            historicoGlobal.ordenarShell(); // ShellSort
            Interfaz::mostrarExito("Transacciones ordenadas!");
        }

        Interfaz::mostrarEstadistica("Total de transacciones", historicoGlobal.getTamano());
        cout << "\nDetalle de transacciones:\n";
        historicoGlobal.imprimir();
    }

    // NUEVO: Ver historial de cuenta especifica (con MergeSort)
    // Complejidad: O(n) busqueda + O(m log m) ordenamiento
    void verHistorialCuenta() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados.");
            return;
        }

        string codigo = Interfaz::solicitarCodigo();
        Cliente* cliente = gestor.buscarPorCodigo(codigo);

        if (!cliente) {
            Interfaz::mostrarError("Cliente no encontrado.");
            return;
        }

        cliente->listarCuentas();

        if (cliente->getCantidadCuentas() == 0) {
            Interfaz::mostrarAdvertencia("Este cliente no tiene cuentas.");
            return;
        }

        int idx = Interfaz::solicitarIndice("cuenta", 1, cliente->getCantidadCuentas());
        CuentaBancaria* cuenta = cliente->obtenerCuenta(idx - 1);

        if (!cuenta) {
            Interfaz::mostrarError("Cuenta no valida.");
            return;
        }

        Interfaz::mostrarTitulo("HISTORIAL DE CUENTA " + cuenta->getNumCuenta(), 50);

        // Submenu para ordenar
        cout << "1. Ver historial (orden actual)\n";
        cout << "2. Ordenar por fecha\n";
        cout << "Seleccione opcion: ";
        int subopcion;
        cin >> subopcion;

        if (subopcion == 2) {
            cout << "\nOrdenando transacciones por fecha...\n";
            cuenta->ordenarHistorialMerge(); // MergeSort
            Interfaz::mostrarExito("Historial ordenado!");
        }

        cout << "\n=== TRANSACCIONES DE LA CUENTA ===\n";
        cuenta->mostrarHistorial();
        Interfaz::mostrarEstadistica("Saldo actual", cuenta->getSaldo());
    }

    // caso 10: ver cronograma de prestamo (con QuickSort)
    void verCronograma() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados.");
            return;
        }

        string codigo = Interfaz::solicitarCodigo();
        Cliente* cliente = gestor.buscarPorCodigo(codigo);

        if (!cliente) {
            Interfaz::mostrarError("Cliente no encontrado.");
            return;
        }

        cliente->listarPrestamos();

        if (cliente->getCantidadPrestamos() == 0) {
            Interfaz::mostrarAdvertencia("Este cliente no tiene prestamos.");
            return;
        }

        int idx = Interfaz::solicitarIndice("prestamo", 1, cliente->getCantidadPrestamos());
        Prestamo* prestamo = cliente->obtenerPrestamo(idx - 1);

        if (!prestamo) {
            Interfaz::mostrarError("Prestamo no valido.");
            return;
        }

        // Submenu para ordenar
        cout << "\n1. Ver cronograma\n";
        cout << "2. Ordenar cuotas por numero\n";
        cout << "Seleccione opcion: ";
        int subopcion;
        cin >> subopcion;

        if (subopcion == 2) {
            cout << "\nOrdenando cuotas por numero...\n";
            prestamo->ordenarCuotasQuick(); // QuickSort
            Interfaz::mostrarExito("Cuotas ordenadas!");
        }

        prestamo->mostrarCronograma();
    }

    // NUEVO: Pagar cuota de prestamo
    // Complejidad: O(n) por busqueda de cliente + O(1) para marcar cuota
    void pagarCuotaPrestamo() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados.");
            return;
        }

        string codigo = Interfaz::solicitarCodigo();
        Cliente* cliente = gestor.buscarPorCodigo(codigo);

        if (!cliente) {
            Interfaz::mostrarError("Cliente no encontrado.");
            return;
        }

        cliente->listarPrestamos();

        if (cliente->getCantidadPrestamos() == 0) {
            Interfaz::mostrarAdvertencia("Este cliente no tiene prestamos.");
            return;
        }

        int idx = Interfaz::solicitarIndice("prestamo", 1, cliente->getCantidadPrestamos());
        Prestamo* prestamo = cliente->obtenerPrestamo(idx - 1);

        if (!prestamo) {
            Interfaz::mostrarError("Prestamo no valido.");
            return;
        }

        // mostrar cronograma antes de pagar
        prestamo->mostrarCronograma();

        int numCuota = Interfaz::solicitarIndice("cuota", 1, prestamo->getCantidadCuotas());

        if (prestamo->pagarCuota(numCuota)) {
            Interfaz::mostrarExito("Pago registrado exitosamente!");
            cout << "La cuota #" << numCuota << " ha sido marcada como pagada.\n";
        } else {
            Interfaz::mostrarError("Error al procesar el pago de la cuota.");
        }
    }

    // Getters para acceso a componentes internos
    HistoricoTransacciones& getHistoricoGlobal() { return historicoGlobal; }
    GestorClientes& getGestorClientes() { return gestor; }

    // Destructor: liberar memoria de cola y pila
    // MEJORA: Ahora usa destructor de OperacionDeshacible para liberar transacciones
    // Complejidad: O(n + m) donde n = cola, m = pila
    ~SistemaFinanciero() {
        // vaciar cola pendiente
        while (!colaTransacciones.estaVacia()) {
            OperacionDeshacible* op = colaTransacciones.desencolar();
            delete op; // el destructor libera la transaccion
        }

        // vaciar pila de deshacer
        while (!pilaDeshacer.estaVacia()) {
            OperacionDeshacible* op = pilaDeshacer.pop();
            delete op; // el destructor libera la transaccion
        }
    }
};

#endif
