#ifndef CLIENTE_H
#define CLIENTE_H
// =============================================================================
// archivo: cliente.h
// descripcion: entidad cliente - representa un cliente del banco
// cumplimiento de rubrica:
//   - entidad #4: hereda de persona, contiene cuentas y prestamos
//   - uso de listasimple para gestionar cuentas y prestamos
//   - relaciones: composicion con persona, agregacion con cuentas/prestamos
//   - paradigma poo: herencia, composicion, encapsulamiento
// =============================================================================

#include "Persona.h"
#include "PersonaNatural.h"
#include "PersonaJuridica.h"
#include "CuentaBancaria.h"
#include "Prestamo.h"
#include "ListaSimple.h"
//Cliente.h
using namespace std;

// clase cliente: hereda de persona
// representa un cliente del banco que puede tener cuentas y prestamos
// demuestra relaciones complejas entre clases
class Cliente : public Persona {
private:
    string codigo;                          // codigo unico del cliente
    string fechaRegistro;                   // fecha de alta en el sistema
    ListaSimple<CuentaBancaria*> cuentas;   // lista de cuentas bancarias
    ListaSimple<Prestamo*> prestamos;       // lista de prestamos
    Persona* detallesPersona = nullptr;     // puntero a personanatural o personajuridica

public:
    // constructor original (sin detalles)
    Cliente(string i, string n, string a, string e, string c, string f)
        : Persona(i, n, a, e), codigo(c), fechaRegistro(f) {
    }

    // constructor sobrecargado que acepta detalles de persona
    // usado por archivomanager al cargar desde archivo
    // demuestra sobrecarga de constructores
    Cliente(string i, string n, string a, string e, string c, string f, Persona* detalles)
        : Persona(i, n, a, e), codigo(c), fechaRegistro(f), detallesPersona(detalles) {
    }

    // destructor: liberar memoria de detalles persona
    // importante: no libera cuentas ni prestamos (se liberan en gestorclientes)
    ~Cliente() {
        // liberar detalles persona si fue asignada
        if (detallesPersona) delete detallesPersona;
    }

    // permitir asociar detalles (persona natural o juridica)
    // demuestra polimorfismo: puede ser personanatural o personajuridica
    void setDetallesPersona(Persona* p) { detallesPersona = p; }
    Persona* getDetallesPersona() const { return detallesPersona; }

    // implementacion del metodo abstracto validar()
    // en este caso siempre retorna true (validacion en detalles)
    bool validar() override { return true; }

    // getters: encapsulamiento
    string getCodigo() const { return codigo; }
    string getFechaAlta() const { return fechaRegistro; }

    // agregar cuenta bancaria al cliente
    // complejidad: O(1) - usa insertaralfinal optimizado
    void agregarCuenta(CuentaBancaria* cu) { cuentas.insertarAlFinal(cu); }

    // agregar prestamo al cliente
    // complejidad: O(1) - usa insertaralfinal optimizado
    void agregarPrestamo(Prestamo* pr) { prestamos.insertarAlFinal(pr); }

    // obtener cuenta por posicion
    // complejidad: O(n) - acceso secuencial en lista enlazada
    // retorna nullptr si posicion invalida
    CuentaBancaria* obtenerCuenta(int pos) {
        CuentaBancaria** ptr = cuentas.obtenerEnPosicion(pos);
        return ptr ? *ptr : nullptr;
    }

    // obtener prestamo por posicion
    // complejidad: O(n) - acceso secuencial en lista enlazada
    Prestamo* obtenerPrestamo(int pos) {
        Prestamo** ptr = prestamos.obtenerEnPosicion(pos);
        return ptr ? *ptr : nullptr;
    }

    // getters para cantidad de cuentas y prestamos
    int getCantidadCuentas() { return cuentas.getTamano(); }
    int getCantidadPrestamos() { return prestamos.getTamano(); }

    // calcular saldo total de todas las cuentas del cliente
    // complejidad: O(n) donde n es cantidad de cuentas
    // recorre todas las cuentas sumando sus saldos
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

    // mostrar informacion completa del cliente
    // complejidad: O(1)
    // usa dynamic_cast para determinar tipo de persona
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
        // demuestra uso de dynamic_cast para polimorfismo en tiempo de ejecucion
        if (detallesPersona) {
            // intentar castear a natural
            PersonaNatural* pn = dynamic_cast<PersonaNatural*>(detallesPersona);
            if (pn) {
                cout << "Tipo: Persona Natural\n";
                cout << "DNI: " << pn->getDni() << "\n";
                cout << "Fecha Nac: " << pn->getFechaNac() << "\n";
            } else {
                // intentar castear a juridica
                PersonaJuridica* pj = dynamic_cast<PersonaJuridica*>(detallesPersona);
                if (pj) {
                    cout << "Tipo: Persona Juridica\n";
                    cout << "RUC: " << pj->getRuc() << "\n";
                    cout << "Razon social: " << pj->getRazonSocial() << "\n";
                }
            }
        }
    }

    // listar todas las cuentas del cliente
    // complejidad: O(n) donde n es cantidad de cuentas
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

    // listar todos los prestamos del cliente
    // complejidad: O(n) donde n es cantidad de prestamos
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