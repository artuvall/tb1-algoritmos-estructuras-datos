#ifndef SISTEMAFINANCIERO_H
#define SISTEMAFINANCIERO_H
//SistemaFinanciero.h
#include "GestorClientes.h"
#include "ArchivoManager.h"
#include "CuentaAhorros.h"
#include "CuentaCorriente.h"
#include "Deposito.h"
#include "Retiro.h"
#include "Cola.h"
#include "Pila.h"
#include "HistoricoTransacciones.h"
#include <iostream>
#include <limits>

using namespace std;

// estructura auxiliar para almacenar operacion deshacible
struct OperacionDeshacible {
    CuentaBancaria* cuenta;
    Transaccion* transaccion;
    bool esDeposito; // true = deposito, false = retiro

    OperacionDeshacible(CuentaBancaria* c, Transaccion* t, bool dep)
        : cuenta(c), transaccion(t), esDeposito(dep) {}
};

class SistemaFinanciero {
private:
    GestorClientes gestor;
    ArchivoManager archiver;

    // estructuras para manejo de transacciones (integrante 3 y 4)
    Cola<OperacionDeshacible*> colaTransacciones;  // transacciones pendientes
    Pila<OperacionDeshacible*> pilaDeshacer;       // operaciones deshacibles
    HistoricoTransacciones historicoGlobal;         // historial completo

    // metodo auxiliar para limpiar buffer
    void limpiarBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    // constructor: cargar datos existentes
    SistemaFinanciero() {
        archiver.cargarClientesArchivo("clientes.txt", gestor.getListaClientes());
    }

    void registrarNuevoCliente(Cliente* nuevo) {
        if (nuevo->validar()) {
            gestor.registrarNuevoCliente(nuevo);
            cout << "Cliente registrado exitosamente!\n";
        } else {
            cout << "Error: cliente no valido.\n";
        }
    }

    void mostrarMenuPrincipal() {
        cout << string(40, '=') << "\n Sistema Caja Huancayo Minimal \n" << string(40, '=') << "\n";
        cout << "1. Registrar Cliente\n";
        cout << "2. Abrir Cuenta\n";
        cout << "3. Deposito/Retiro (Encolar)\n";
        cout << "4. Solicitar Prestamo\n";
        cout << "5. Generar Reporte\n";
        cout << "6. Guardar Datos\n";
        cout << "7. Procesar Siguiente Transaccion\n";
        cout << "8. Deshacer Ultima Operacion\n";
        cout << "9. Ver Historial Global\n";
        cout << "0. Salir\n";
        cout << string(40, '-') << "\n";
    }

    // caso 2: abrir cuenta para cliente existente
    void abrirCuenta() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            cout << "No hay clientes registrados. Registre un cliente primero.\n";
            return;
        }

        cout << "\nIngrese codigo del cliente: ";
        string codigo;
        cin >> codigo;

        Cliente* cliente = gestor.buscarPorCodigo(codigo);
        if (!cliente) {
            cout << "Cliente no encontrado.\n";
            return;
        }

        cout << "\nSeleccione tipo de cuenta:\n";
        cout << "1. Cuenta de Ahorros\n";
        cout << "2. Cuenta Corriente\n";
        cout << "Opcion: ";
        int tipo;
        cin >> tipo;

        // auto-generar numero de cuenta unico
        static int contadorCuenta = 10000;
        string numCuenta = to_string(contadorCuenta);
        contadorCuenta++;

        cout << "\nNumero de cuenta auto-generado: " << numCuenta << "\n";

        cout << "Ingrese saldo inicial (S/): ";
        double saldoInicial;
        cin >> saldoInicial;

        CuentaBancaria* nuevaCuenta = nullptr;

        if (tipo == 1) {
            // cuenta de ahorros
            nuevaCuenta = new CuentaAhorros(numCuenta, saldoInicial, cliente->getNombre(), "01/01/2025", 0.05);
        } else if (tipo == 2) {
            // cuenta corriente
            nuevaCuenta = new CuentaCorriente(numCuenta, saldoInicial, cliente->getNombre(), "01/01/2025", 1000.0);
        }

        if (nuevaCuenta) {
            cliente->agregarCuenta(nuevaCuenta);
            cout << "\n=== CUENTA ABIERTA EXITOSAMENTE ===\n";
            cout << "Numero de Cuenta: " << numCuenta << "\n";
            cout << "Saldo Inicial: S/ " << saldoInicial << "\n";
        }
    }

    // caso 3: realizar deposito o retiro (ahora encola en vez de ejecutar)
    void depositoRetiro() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            cout << "No hay clientes registrados.\n";
            return;
        }

        cout << "\nIngrese codigo del cliente: ";
        string codigo;
        cin >> codigo;

        Cliente* cliente = gestor.buscarPorCodigo(codigo);
        if (!cliente) {
            cout << "Cliente no encontrado.\n";
            return;
        }

        cliente->listarCuentas();
        if (cliente->getCantidadCuentas() == 0) {
            cout << "Este cliente no tiene cuentas. Abra una cuenta primero.\n";
            return;
        }

        cout << "\nSeleccione cuenta (ingrese el número de la lista 1-"
     << cliente->getCantidadCuentas() << "): ";
        int indiceCuenta;
        cin >> indiceCuenta;

        if (indiceCuenta < 1 || indiceCuenta > cliente->getCantidadCuentas()) {
            cout << "Indice invalido.\n";
            return;
        }

        CuentaBancaria* cuenta = cliente->obtenerCuenta(indiceCuenta - 1);

        if (!cuenta) {
            cout << "Cuenta no valida.\n";
            return;
        }

        cout << "\n1. Deposito\n2. Retiro\nOpcion: ";
        int operacion;
        cin >> operacion;

        cout << "Ingrese monto (S/): ";
        double monto;
        cin >> monto;

        // solicitar fecha de la transaccion
        cout << "Ingrese fecha de transaccion (DD/MM/AAAA): ";
        string fechaTransaccion;
        cin >> fechaTransaccion;

        // solicitar metodo de la transaccion
        cout << "Metodo (Efectivo/Transferencia/Cheque/Cajero): ";
        string metodo;
        cin >> metodo;

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

        cout << "\n=== TRANSACCION ENCOLADA ===\n";
        cout << "ID: " << nuevaTransaccion->getId() << "\n";
        cout << "Tipo: " << tipoOperacion << "\n";
        cout << "Monto: S/ " << monto << "\n";
        cout << "Transacciones pendientes en cola: " << colaTransacciones.getTamano() << "\n";
        cout << "\nUse la opcion 7 para procesar transacciones pendientes.\n";
    }

    // caso 4: solicitar prestamo
    void solicitarPrestamo() {
        gestor.imprimirClientes();

        if (gestor.getListaClientes().getTamano() == 0) {
            cout << "No hay clientes registrados.\n";
            return;
        }

        cout << "\nIngrese codigo del cliente: ";
        string codigo;
        cin >> codigo;

        Cliente* cliente = gestor.buscarPorCodigo(codigo);
        if (!cliente) {
            cout << "Cliente no encontrado.\n";
            return;
        }

        cout << "\nIngrese monto del prestamo: ";
        double monto;
        cin >> monto;

        cout << "Ingrese plazo (meses): ";
        int plazo;
        cin >> plazo;

        // generar id unico para prestamo
        string idPrestamo = "PREST" + to_string(cliente->getCantidadPrestamos() + 1);

        Prestamo* nuevoPrestamo = new Prestamo(idPrestamo, monto, plazo, "Pendiente");

        // verificar aprobacion con lambda
        if (nuevoPrestamo->solicitar()) {
            cliente->agregarPrestamo(nuevoPrestamo);
            cout << "Prestamo aprobado exitosamente!\n";
            cout << "ID Prestamo: " << idPrestamo << "\n";
            cout << "Monto: S/" << monto << "\n";
            cout << "Plazo: " << plazo << " meses\n";
        } else {
            cout << "Prestamo rechazado. El monto excede el limite permitido.\n";
            delete nuevoPrestamo;
        }
    }

    // caso 5: generar reporte ordenado
    void generarReporteOrdenado() {
        cout << "\n=== GENERANDO REPORTE ORDENADO ===\n";
        gestor.ordenarClientesHeap(); // ordenar con heapsort integrante 3
        gestor.imprimirClientes();
        cout << "\nTotal de clientes: " << gestor.contarClientesActivos() << "\n";
    }

    // caso 6: guardar datos en archivo
    void guardarDatos() {
        cout << "\n=== GUARDANDO DATOS ===\n";
        archiver.ordenarClientesSelection(gestor.getListaClientes()); // ordenar antes de guardar
        archiver.guardarClientesArchivo("clientes.txt", gestor.getListaClientes());
    }

    // metodo auxiliar: verificar sesion con lambda (integrante 5)
    bool incluirSesion(const string& cod) {
        // lambda integrante 5: verificar sesion
        auto check = [this, cod]() {
            return gestor.buscarPorCodigo(cod) != nullptr;
        };
        return check();
    }

    // caso 7: procesar siguiente transaccion de la cola
    void procesarSiguienteTransaccion() {
        if (colaTransacciones.estaVacia()) {
            cout << "\nNo hay transacciones pendientes en la cola.\n";
            return;
        }

        cout << "\n=== PROCESANDO SIGUIENTE TRANSACCION ===\n";

        // desencolar siguiente operacion
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

            // guardar en pila para deshacer
            pilaDeshacer.push(op);

            cout << "\n=== TRANSACCION PROCESADA EXITOSAMENTE ===\n";
            cout << "Nuevo saldo: S/ " << op->cuenta->getSaldo() << "\n";
            cout << "Transacciones en cola: " << colaTransacciones.getTamano() << "\n";
            cout << "Operaciones deshacibles: " << pilaDeshacer.getTamano() << "\n";
        } else {
            cout << "\nError: la transaccion no pudo ejecutarse.\n";
            cout << "Posibles causas: fondos insuficientes o limites excedidos.\n";
            // liberar memoria si fallo
            delete op->transaccion;
            delete op;
        }
    }

    // caso 8: deshacer ultima operacion procesada
    void deshacerUltimaOperacion() {
        if (pilaDeshacer.estaVacia()) {
            cout << "\nNo hay operaciones para deshacer.\n";
            return;
        }

        cout << "\n=== DESHACIENDO ULTIMA OPERACION ===\n";

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
            cout << "\n=== OPERACION DESHECHA EXITOSAMENTE ===\n";
            cout << "Nuevo saldo: S/ " << op->cuenta->getSaldo() << "\n";
            cout << "Operaciones restantes en pila: " << pilaDeshacer.getTamano() << "\n";

            // liberar memoria
            delete op->transaccion;
            delete op;
        } else {
            cout << "\nError: no se pudo deshacer la operacion.\n";
            // devolver a la pila si fallo
            pilaDeshacer.push(op);
        }
    }

    // caso 9: ver historial global de transacciones
    void verHistorialGlobal() {
        cout << "\n=== HISTORIAL GLOBAL DE TRANSACCIONES ===\n";

        if (historicoGlobal.getTamano() == 0) {
            cout << "No hay transacciones procesadas aun.\n";
            return;
        }

        cout << "Total de transacciones procesadas: " << historicoGlobal.getTamano() << "\n";
        cout << "\nDetalle de transacciones:\n";
        historicoGlobal.imprimir();
    }

    // getter para acceder al historico (usado por caso 9)
    HistoricoTransacciones& getHistoricoGlobal() {
        return historicoGlobal;
    }

    // destructor: liberar memoria de cola y pila
    ~SistemaFinanciero() {
        // vaciar cola pendiente
        while (!colaTransacciones.estaVacia()) {
            OperacionDeshacible* op = colaTransacciones.desencolar();
            delete op->transaccion;
            delete op;
        }

        // vaciar pila de deshacer
        while (!pilaDeshacer.estaVacia()) {
            OperacionDeshacible* op = pilaDeshacer.pop();
            delete op->transaccion;
            delete op;
        }
    }
};

#endif
