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
#include "Interfaz.h"  // CAMBIADO: de UIHelper a Interfaz
#include <iostream>
#include <limits>
#include <iomanip> // para setprecision

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
        Interfaz::mostrarTitulo("CAJA HUANCAYO - Sistema Financiero", 60);
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
            cout << "3. Ver Reporte Ordenado de Clientes\n";
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
                case 3:
                    generarReporteOrdenado();
                    break;
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
            cout << "4. Demo de Algoritmos de Ordenamiento\n";
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
                case 4:
                    menuDemoAlgoritmos();
                    break;
                case 0:
                    cout << "Volviendo al menu principal...\n";
                    break;
                default:
                    Interfaz::mostrarError("Opcion invalida");
            }
        } while (opcion != 0);
    }

    // NUEVO: Menu de Demo de Algoritmos
    void menuDemoAlgoritmos() {
        Interfaz::mostrarTitulo("DEMOSTRACION DE ALGORITMOS", 50);
        cout << "1. QuickSort - Ordenar Cuotas de Prestamo\n";
        cout << "2. HeapSort - Ordenar Clientes por Codigo\n";
        cout << "3. ShellSort - Ordenar Transacciones\n";
        cout << "4. MergeSort - Ordenar Historial de Cuenta\n";
        cout << "5. Filtros Lambda - Clientes por Saldo\n";
        cout << "0. Volver\n";
        Interfaz::mostrarSeparador('-', 50);
        cout << "Seleccione demo: ";

        int demo;
        cin >> demo;

        switch (demo) {
            case 1:
                demoQuickSort();
                break;
            case 2:
                demoHeapSort();
                break;
            case 3:
                demoShellSort();
                break;
            case 4:
                demoMergeSort();
                break;
            case 5:
                demoFiltrosLambda();
                break;
            case 0:
                break;
            default:
                Interfaz::mostrarError("Opcion invalida");
        }
    }

    // NUEVO: Mostrar estado de cola de transacciones
    void mostrarEstadoCola() {
        Interfaz::mostrarTitulo("ESTADO DE COLA DE TRANSACCIONES", 50);
        Interfaz::mostrarEstadistica("Transacciones pendientes", colaTransacciones.getTamano());

        if (colaTransacciones.getTamano() > 0) {
            cout << "\nLas transacciones seran procesadas en orden FIFO (primero en entrar, primero en salir)\n";
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
            cout << "\nLas operaciones se deshacen en orden LIFO (ultima en entrar, primera en salir)\n";
            cout << "Use 'Deshacer Ultima Operacion' en el menu de Operaciones Bancarias\n";
        } else {
            cout << "\nNo hay operaciones para deshacer.\n";
        }
    }

    // NUEVO: Demos de algoritmos
    void demoQuickSort() {
        cout << "\n=== DEMO: QuickSort en Prestamos ===\n";
        cout << "El QuickSort ordena las cuotas de un prestamo por numero.\n";
        cout << "Esta implementacion usa recursion y particion.\n";
        cout << "Complejidad: O(n log n) promedio\n\n";

        gestor.imprimirClientes();
        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes para demostrar.");
            return;
        }

        string codigo = Interfaz::solicitarCodigo();
        Cliente* cliente = gestor.buscarPorCodigo(codigo);

        if (!cliente || cliente->getCantidadPrestamos() == 0) {
            Interfaz::mostrarAdvertencia("Cliente sin prestamos.");
            return;
        }

        cliente->listarPrestamos();
        int idx = Interfaz::solicitarIndice("prestamo", 1, cliente->getCantidadPrestamos());
        Prestamo* prestamo = cliente->obtenerPrestamo(idx - 1);

        if (prestamo) {
            cout << "\nOrdenando cuotas con QuickSort...\n";
            prestamo->ordenarCuotasQuick();
            prestamo->mostrarCronograma();
            Interfaz::mostrarExito("QuickSort ejecutado exitosamente!");
        }
    }

    void demoHeapSort() {
        cout << "\n=== DEMO: HeapSort en Clientes ===\n";
        cout << "El HeapSort ordena clientes por codigo usando un heap binario.\n";
        cout << "Complejidad: O(n log n) garantizado\n\n";

        cout << "ANTES del ordenamiento:\n";
        gestor.imprimirClientes();

        cout << "\nOrdenando con HeapSort...\n";
        gestor.ordenarClientesHeap();

        cout << "\nDESPUES del ordenamiento:\n";
        gestor.imprimirClientes();
        Interfaz::mostrarExito("HeapSort ejecutado exitosamente!");
    }

    void demoShellSort() {
        cout << "\n=== DEMO: ShellSort en Transacciones ===\n";
        cout << "El ShellSort ordena transacciones usando secuencia de gaps.\n";
        cout << "Complejidad: O(n log n) a O(n^1.5) segun secuencia\n\n";

        if (historicoGlobal.getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay transacciones en el historial.");
            return;
        }

        cout << "ANTES del ordenamiento:\n";
        historicoGlobal.imprimir();

        cout << "\nOrdenando con ShellSort...\n";
        historicoGlobal.ordenarShell();  // CORREGIDO: era ordenarPorMontoShell()

        cout << "\nDESPUES del ordenamiento:\n";
        historicoGlobal.imprimir();
        Interfaz::mostrarExito("ShellSort ejecutado exitosamente!");
    }

    void demoMergeSort() {
        cout << "\n=== DEMO: MergeSort en Historial de Cuenta ===\n";
        cout << "El MergeSort ordena transacciones de una cuenta por fecha.\n";
        cout << "Usa divide y conquista con fusion de sublistas.\n";
        cout << "Complejidad: O(n log n) garantizado\n\n";

        gestor.imprimirClientes();
        if (gestor.getListaClientes().getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay clientes registrados.");
            return;
        }

        string codigo = Interfaz::solicitarCodigo();
        Cliente* cliente = gestor.buscarPorCodigo(codigo);

        if (!cliente || cliente->getCantidadCuentas() == 0) {
            Interfaz::mostrarAdvertencia("Cliente sin cuentas.");
            return;
        }

        cliente->listarCuentas();
        int idx = Interfaz::solicitarIndice("cuenta", 1, cliente->getCantidadCuentas());
        CuentaBancaria* cuenta = cliente->obtenerCuenta(idx - 1);

        if (cuenta) {
            cout << "\nOrdenando historial con MergeSort...\n";
            cuenta->ordenarHistorialMerge();
            Interfaz::mostrarExito("MergeSort ejecutado exitosamente!");
        }
    }

    void demoFiltrosLambda() {
        cout << "\n=== DEMO: Filtros con Lambdas ===\n";
        cout << "Los lambdas permiten filtrar datos con expresiones concisas.\n\n";

        double montoMinimo = Interfaz::solicitarMonto("saldo minimo para filtrar");

        cout << "\nFiltrando clientes con saldo >= S/ " << montoMinimo << "...\n";
        ListaSimple<Cliente*> filtrados = gestor.filtrarPorSaldo(montoMinimo);

        cout << "\n=== CLIENTES FILTRADOS ===\n";
        if (filtrados.getTamano() == 0) {
            cout << "No se encontraron clientes con ese saldo.\n";
        } else {
            auto imprimir = [](Cliente* cl) {
                cout << "- " << cl->getNombre() << " (Codigo: " << cl->getCodigo()
                     << ") - Saldo Total: S/ " << cl->getSaldoTotal() << "\n";
            };
            filtrados.imprimir(imprimir);
            Interfaz::mostrarExito("Lambda ejecutado exitosamente!");
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

    // caso 9: ver historial global de transacciones
    // Complejidad: O(n) donde n es cantidad de transacciones
    void verHistorialGlobal() {
        Interfaz::mostrarTitulo("HISTORIAL GLOBAL", 50);

        if (historicoGlobal.getTamano() == 0) {
            Interfaz::mostrarAdvertencia("No hay transacciones procesadas aun.");
            return;
        }

        Interfaz::mostrarEstadistica("Total de transacciones", historicoGlobal.getTamano());
        cout << "\nDetalle de transacciones:\n";
        historicoGlobal.imprimir();
    }

    // caso 10: ver cronograma de prestamo
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

        if (prestamo) {
            prestamo->mostrarCronograma();
        }
    }

    // caso 11: pagar cuota de prestamo
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
