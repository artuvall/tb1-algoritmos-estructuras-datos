#ifndef CLIENTE_H
#define CLIENTE_H

#include "Persona.h"
#include "PersonaNatural.h"
#include "PersonaJuridica.h"
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
    Persona* detallesPersona = nullptr; // puntero a persona natural o juridica

public:
    // Constructor original (sin detalles)
    Cliente(string i, string n, string a, string e, string c, string f)
        : Persona(i, n, a, e), codigo(c), fechaRegistro(f) {
    }

    // NUEVO: Constructor sobrecargado que acepta detalles de persona
    // Usado por ArchivoManager al cargar desde archivo
    Cliente(string i, string n, string a, string e, string c, string f, Persona* detalles)
        : Persona(i, n, a, e), codigo(c), fechaRegistro(f), detallesPersona(detalles) {
    }

    ~Cliente() {
        // liberar detalles persona si fue asignada
        if (detallesPersona) delete detallesPersona;
    }

    // permitir asociar detalles (persona natural o juridica)
    void setDetallesPersona(Persona* p) { detallesPersona = p; }
    Persona* getDetallesPersona() const { return detallesPersona; }

    bool validar() override { return true; }

    string getCodigo() const { return codigo; }
    string getFechaAlta() const { return fechaRegistro; }  // AGREGADO: alias para fecha

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

    // metodo para calcular saldo total de todas las cuentas
    double getSaldoTotal() const {
        double total = 0.0;
        for (int i = 0; i < cuentas.getTamano(); i++) {
            CuentaBancaria* cuenta = *cuentas.obtenerEnPosicion(i);
            if (cuenta) {
                total += cuenta->getSaldo();
            }
        }
        return total;
    }

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
        // mostrar detalles especificos segun tipo si existen
        if (detallesPersona) {
            // intentar caster a natural
            PersonaNatural* pn = dynamic_cast<PersonaNatural*>(detallesPersona);
            if (pn) {
                cout << "Tipo: Persona Natural\n";
                cout << "DNI: " << pn->getDni() << "\n";
                cout << "Fecha Nac: " << pn->getFechaNac() << "\n";
            } else {
                PersonaJuridica* pj = dynamic_cast<PersonaJuridica*>(detallesPersona);
                if (pj) {
                    cout << "Tipo: Persona Juridica\n";
                    cout << "RUC: " << pj->getRuc() << "\n";
                    cout << "Razon social: " << pj->getRazonSocial() << "\n";
                }
            }
        }
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
            cout << (i + 1) << ". Numero Cuenta: " << cuenta->getNumCuenta()
                 << " | Saldo: S/ " << cuenta->getSaldo() << "\n";
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