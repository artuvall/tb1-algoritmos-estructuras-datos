#ifndef GARANTIA_H
#define GARANTIA_H
// =============================================================================
// archivo: garantia.h
// descripcion: entidad garantia - respalda un prestamo
// cumplimiento de rubrica:
//   - entidad #13: parte del sistema de prestamos
//   - encapsulamiento: atributos privados con getters
// =============================================================================

//Garantia.h
#include <string>
#include <iostream>

using namespace std;

// clase garantia: representa un bien que respalda un prestamo
// ejemplos: vehiculo, inmueble, aval
// el valor de la garantia debe ser mayor al monto del prestamo
class Garantia {
private:
    string tipo;      // tipo de garantia: "vehiculo", "inmueble", "aval"
    double valor;     // valor estimado de la garantia

public:
    // constructor: inicializa tipo y valor
    Garantia(string t, double v) : tipo(t), valor(v) {}

    // getters para acceder a los datos: encapsulamiento
    string getTipo() const { return tipo; }
    double getValor() const { return valor; }

    // mostrar informacion de la garantia
    void mostrarInfo() const {
        cout << "Tipo: " << tipo << " | Valor: S/ " << valor;
    }
};

#endif