#ifndef INTERFAZ_H
#define INTERFAZ_H
// =============================================================================
// archivo: interfaz.h
// descripcion: clase auxiliar para manejo de interfaz de usuario en consola
// cumplimiento de rubrica:
//   - entidad #16: separacion de capas (ui vs logica de negocio)
//   - principio solid: single responsibility principle
//   - mejora legibilidad y mantenibilidad del codigo
//   - interfaz amigable para usuario (requisito de rubrica)
// =============================================================================

// Interfaz.h - Clase auxiliar para manejo de interfaz de usuario
// SEPARACION DE CAPAS: Separacion de logica de UI de la logica de negocio
// Mejora la legibilidad y mantenibilidad del codigo

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// clase interfaz: maneja toda la interaccion con el usuario
// patron de diseño: utility class (solo metodos estaticos)
// ventaja: reutilizable, consistente, facil de mantener
class Interfaz {
public:
    // limpiar buffer de entrada despues de operaciones de cin
    // util para evitar problemas con entradas mezcladas (int + string)
    // complejidad: O(1)
    static void limpiarBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // mostrar separador visual en consola
    // parametros: caracter a usar, longitud del separador
    // uso: mejorar legibilidad visual de la interfaz
    static void mostrarSeparador(char caracter = '=', int longitud = 50) {
        cout << string(longitud, caracter) << "\n";
    }

    // mostrar titulo centrado con separadores
    // mejora estetica de la interfaz (requisito de rubrica)
    static void mostrarTitulo(const string& titulo, int ancho = 50) {
        mostrarSeparador('=', ancho);
        int espacios = (ancho - titulo.length()) / 2;
        cout << string(espacios, ' ') << titulo << "\n";
        mostrarSeparador('=', ancho);
    }

    // solicitar codigo de cliente con validacion
    // encapsula logica de entrada para reutilizacion
    static string solicitarCodigo() {
        cout << "Ingrese codigo del cliente: ";
        string codigo;
        cin >> codigo;
        return codigo;
    }

    // solicitar tipo de cuenta con validacion
    // valida que opcion sea 1 o 2
    static int solicitarTipoCuenta() {
        cout << "\n=== TIPO DE CUENTA ===\n";
        cout << "1. Cuenta de Ahorros\n";
        cout << "2. Cuenta Corriente\n";
        cout << "Seleccione opcion: ";
        int tipo;
        cin >> tipo;

        while (tipo < 1 || tipo > 2) {
            cout << "Opcion invalida. Ingrese 1 o 2: ";
            cin >> tipo;
        }

        return tipo;
    }

    // solicitar tipo de persona (natural o juridica)
    // valida entrada del usuario
    static int solicitarTipoPersona() {
        cout << "\n=== TIPO DE PERSONA ===\n";
        cout << "1. Persona Natural\n";
        cout << "2. Persona Juridica\n";
        cout << "Seleccione opcion: ";
        int tipo;
        cin >> tipo;

        while (tipo < 1 || tipo > 2) {
            cout << "Opcion invalida. Ingrese 1 o 2: ";
            cin >> tipo;
        }

        return tipo;
    }

    // solicitar monto con validacion
    // valida que monto sea positivo
    static double solicitarMonto(const string& concepto = "monto") {
        cout << "Ingrese " << concepto << " (S/): ";
        double monto;
        cin >> monto;

        while (monto <= 0) {
            cout << "Monto invalido. Debe ser mayor a 0: ";
            cin >> monto;
        }

        return monto;
    }

    // solicitar fecha en formato DD/MM/AAAA
    // no valida formato, solo solicita entrada
    static string solicitarFecha(const string& concepto = "fecha") {
        cout << "Ingrese " << concepto << " (DD/MM/AAAA): ";
        string fecha;
        cin >> fecha;
        return fecha;
    }

    // solicitar texto general
    // metodo generico para cualquier campo de texto
    static string solicitarTexto(const string& campo) {
        cout << "Ingrese " << campo << ": ";
        string texto;
        cin >> texto;
        return texto;
    }

    // solicitar confirmacion (s/n)
    // retorna true si usuario confirma, false si no
    static bool solicitarConfirmacion(const string& mensaje) {
        cout << mensaje << " (s/n): ";
        char respuesta;
        cin >> respuesta;
        return (respuesta == 's' || respuesta == 'S');
    }

    // mostrar mensaje de exito con formato destacado
    // mejora feedback visual al usuario
    static void mostrarExito(const string& mensaje) {
        cout << "\n";
        mostrarSeparador('*', 40);
        cout << "EXITO: " << mensaje << "\n";
        mostrarSeparador('*', 40);
        cout << "\n";
    }

    // mostrar mensaje de error con formato destacado
    // ayuda a identificar problemas rapidamente
    static void mostrarError(const string& mensaje) {
        cout << "\n";
        mostrarSeparador('!', 40);
        cout << "ERROR: " << mensaje << "\n";
        mostrarSeparador('!', 40);
        cout << "\n";
    }

    // mostrar mensaje de advertencia con formato destacado
    // para notificaciones importantes pero no criticas
    static void mostrarAdvertencia(const string& mensaje) {
        cout << "\n";
        mostrarSeparador('-', 40);
        cout << "AVISO: " << mensaje << "\n";
        mostrarSeparador('-', 40);
        cout << "\n";
    }

    // pausar hasta que usuario presione enter
    // util para que usuario pueda leer mensajes antes de continuar
    static void pausar() {
        cout << "\nPresione Enter para continuar...";
        limpiarBuffer();
        cin.get();
    }

    // mostrar menu de operaciones bancarias
    // retorna opcion seleccionada validada
    static int mostrarMenuOperaciones() {
        cout << "\n=== TIPO DE OPERACION ===\n";
        cout << "1. Deposito\n";
        cout << "2. Retiro\n";
        cout << "Seleccione opcion: ";
        int opcion;
        cin >> opcion;

        while (opcion < 1 || opcion > 2) {
            cout << "Opcion invalida. Ingrese 1 o 2: ";
            cin >> opcion;
        }

        return opcion;
    }

    // solicitar indice con validacion de rango
    // valida que indice este entre minimo y maximo
    static int solicitarIndice(const string& concepto, int minimo, int maximo) {
        cout << "Seleccione numero de " << concepto
             << " (" << minimo << "-" << maximo << "): ";
        int indice;
        cin >> indice;

        while (indice < minimo || indice > maximo) {
            cout << "Indice invalido. Ingrese valor entre "
                 << minimo << " y " << maximo << ": ";
            cin >> indice;
        }

        return indice;
    }

    // mostrar estadisticas en formato tabla
    // sobrecarga para diferentes tipos de datos
    // version para enteros
    static void mostrarEstadistica(const string& concepto, int valor) {
        cout << "| " << concepto;
        int espacios = 35 - concepto.length();
        cout << string(espacios, ' ') << " | " << valor << "\n";
    }

    // version para doubles (montos)
    static void mostrarEstadistica(const string& concepto, double valor) {
        cout << "| " << concepto;
        int espacios = 35 - concepto.length();
        cout << string(espacios, ' ') << " | S/ " << valor << "\n";
    }

    // version para strings (textos)
    static void mostrarEstadistica(const string& concepto, const string& valor) {
        cout << "| " << concepto;
        int espacios = 35 - concepto.length();
        cout << string(espacios, ' ') << " | " << valor << "\n";
    }
};

#endif
