#ifndef SISTEMAFINANCIERO_H
#define SISTEMAFINANCIERO_H
//SistemaFinanciero.h
#include "GestorClientes.h"
#include "ArchivoManager.h"
#include "CuentaAhorros.h"
#include "CuentaCorriente.h"
#include "Deposito.h"
#include "Retiro.h"
#include <iostream>
#include <limits>

using namespace std;

class SistemaFinanciero {
private:
    GestorClientes gestor;
    ArchivoManager archiver;

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
        cout << "1. Registrar Cliente\n2. Abrir Cuenta\n3. Deposito/Retiro\n4. Solicitar Prestamo\n";
        cout << "5. Generar Reporte\n6. Guardar Datos\n0. Salir\n" << string(40, '-') << "\n";
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

        cout << "Ingrese numero de cuenta: ";
        string numCuenta;
        cin >> numCuenta;

        cout << "Ingrese saldo inicial: ";
        double saldoInicial;
        cin >> saldoInicial;

        CuentaBancaria* nuevaCuenta = nullptr;

        if (tipo == 1) {
            // cuenta de ahorros
            nuevaCuenta = new CuentaAhorros(numCuenta, saldoInicial, cliente->getNombre(), "2025-01-01", 0.05);
        } else if (tipo == 2) {
            // cuenta corriente
            nuevaCuenta = new CuentaCorriente(numCuenta, saldoInicial, cliente->getNombre(), "2025-01-01", 1000.0);
        }

        if (nuevaCuenta) {
            cliente->agregarCuenta(nuevaCuenta);
            cout << "Cuenta abierta exitosamente!\n";
        }
    }

    // caso 3: realizar deposito o retiro
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

        cout << "\nSeleccione numero de cuenta (1-" << cliente->getCantidadCuentas() << "): ";
        int numCuenta;
        cin >> numCuenta;

        CuentaBancaria* cuenta = cliente->obtenerCuenta(numCuenta - 1);
        if (!cuenta) {
            cout << "Cuenta no valida.\n";
            return;
        }

        cout << "\n1. Deposito\n2. Retiro\nOpcion: ";
        int operacion;
        cin >> operacion;

        cout << "Ingrese monto: ";
        double monto;
        cin >> monto;

        if (operacion == 1) {
            if (cuenta->depositar(monto)) {
                cout << "Deposito realizado exitosamente!\n";
                cout << "Nuevo saldo: $" << cuenta->getSaldo() << "\n";
            } else {
                cout << "Error al realizar deposito.\n";
            }
        } else if (operacion == 2) {
            if (cuenta->retirar(monto)) {
                cout << "Retiro realizado exitosamente!\n";
                cout << "Nuevo saldo: $" << cuenta->getSaldo() << "\n";
            } else {
                cout << "Error: fondos insuficientes o monto invalido.\n";
            }
        }
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
            cout << "Monto: $" << monto << "\n";
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
};

#endif