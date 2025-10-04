#ifndef TRANSACCION_H
#define TRANSACCION_H
// =============================================================================
// archivo: transaccion.h
// descripcion: clase base abstracta transaccion
// cumplimiento de rubrica:
//   - entidad #8: clase base para deposito y retiro
//   - paradigma poo: herencia, polimorfismo, abstraccion
//   - destructor virtual para manejo correcto de memoria
// =============================================================================

//Transaccion.h
#include <string>

using namespace std;

// clase abstracta transaccion: base para deposito y retiro
// representa cualquier movimiento de dinero en una cuenta
class Transaccion {
protected:
    // atributos protegidos: accesibles por clases derivadas
    string id;        // identificador unico de transaccion
    double monto;     // cantidad de dinero involucrada
    string fecha;     // fecha de la transaccion (DD/MM/AAAA)
    string tipo;      // tipo: "deposito" o "retiro"

public:
    // constructor: inicializa atributos basicos
    Transaccion(string i, double m, string f, string t)
        : id(i), monto(m), fecha(f), tipo(t) {
    }

    // destructor virtual: esencial para herencia
    // permite eliminar objetos derivados correctamente
    virtual ~Transaccion() {}

    // metodo abstracto puro: obliga a clases derivadas a implementarlo
    // cada tipo de transaccion (deposito/retiro) ejecutara de forma diferente
    virtual bool ejecutar() = 0;

    // getters publicos: encapsulamiento - acceso controlado a atributos
    string getId() const { return id; }
    double getMonto() const { return monto; }
    string getFecha() const { return fecha; }
    string getTipo() const { return tipo; }
};

#endif