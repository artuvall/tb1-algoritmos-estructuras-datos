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
};

#endif