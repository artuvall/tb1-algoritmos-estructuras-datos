#ifndef CLIENTE_H
#define CLIENTE_H

#include "Persona.h"
#include "CuentaBancaria.h"
#include "Prestamo.h"
#include "ListaSimple.h"
//Cliente.h
using namespace std;

class Cliente : public Persona {
private:
    string codigo;
    string fechaRegistro;
    ListaSimple<CuentaBancaria*> cuentas;
    ListaSimple<Prestamo*> prestamos;

public:
    Cliente(string i, string n, string a, string e, string c, string f)
        : Persona(i, n, a, e), codigo(c), fechaRegistro(f) {
    }

    bool validar() override { return true; }

    string getCodigo() const { return codigo; }

    void agregarCuenta(CuentaBancaria* cu) { cuentas.insertarAlFinal(cu); }

    void agregarPrestamo(Prestamo* pr) { prestamos.insertarAlFinal(pr); }

    // metodo para obtener cuenta por posicion
    CuentaBancaria* obtenerCuenta(int pos) {
        CuentaBancaria** ptr = cuentas.obtenerEnPosicion(pos);
        return ptr ? *ptr : nullptr;
    }

    // metodo para obtener prestamo por posicion
    Prestamo* obtenerPrestamo(int pos) {
        Prestamo** ptr = prestamos.obtenerEnPosicion(pos);
        return ptr ? *ptr : nullptr;
    }

    int getCantidadCuentas() { return cuentas.getTamano(); }
    int getCantidadPrestamos() { return prestamos.getTamano(); }

    // metodo para mostrar informacion del cliente
    void mostrarInfo() {
        cout << "\n=== INFORMACION DEL CLIENTE ===\n";
        cout << "ID: " << id << "\n";
        cout << "Nombre: " << nombre << " " << apellido << "\n";
        cout << "Email: " << email << "\n";
        cout << "Codigo: " << codigo << "\n";
        cout << "Fecha Registro: " << fechaRegistro << "\n";
        cout << "Cuentas: " << cuentas.getTamano() << "\n";
        cout << "Prestamos: " << prestamos.getTamano() << "\n";
    }

    // metodo para listar cuentas
    void listarCuentas() {
        if (cuentas.getTamano() == 0) {
            cout << "Este cliente no tiene cuentas registradas.\n";
            return;
        }
        cout << "\n=== CUENTAS DEL CLIENTE ===\n";
        for (int i = 0; i < cuentas.getTamano(); i++) {
            CuentaBancaria* cuenta = *cuentas.obtenerEnPosicion(i);
            cout << i + 1 << ". Cuenta: " << cuenta->getNumCuenta()
                 << " | Saldo: $" << cuenta->getSaldo() << "\n";
        }
    }

    // metodo para listar prestamos
    void listarPrestamos() {
        if (prestamos.getTamano() == 0) {
            cout << "Este cliente no tiene prestamos registrados.\n";
            return;
        }
        cout << "\n=== PRESTAMOS DEL CLIENTE ===\n";
        for (int i = 0; i < prestamos.getTamano(); i++) {
            Prestamo* prestamo = *prestamos.obtenerEnPosicion(i);
            cout << i + 1 << ". ID: " << prestamo->getId()
                 << " | Monto: $" << prestamo->getMonto()
                 << " | Estatus: " << prestamo->getEstatus() << "\n";
        }
    }
};

#endif