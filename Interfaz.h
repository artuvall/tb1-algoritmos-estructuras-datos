#ifndef INTERFAZ_H
#define INTERFAZ_H
// Interfaz.h - Clase auxiliar para manejo de interfaz de usuario
// SEPARACION DE CAPAS: Separacion de logica de UI de la logica de negocio
// Mejora la legibilidad y mantenibilidad del codigo

#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Interfaz {
public:
    // Limpiar buffer de entrada despues de operaciones de cin
    // Util para evitar problemas con entradas mezcladas
    static void limpiarBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Mostrar separador visual
    static void mostrarSeparador(char caracter = '=', int longitud = 50) {
        cout << string(longitud, caracter) << "\n";
    }

    // Mostrar titulo centrado
    static void mostrarTitulo(const string& titulo, int ancho = 50) {
        mostrarSeparador('=', ancho);
        int espacios = (ancho - titulo.length()) / 2;
        cout << string(espacios, ' ') << titulo << "\n";
        mostrarSeparador('=', ancho);
    }

    // Solicitar codigo de cliente con validacion
    static string solicitarCodigo() {
        cout << "Ingrese codigo del cliente: ";
        string codigo;
        cin >> codigo;
        return codigo;
    }

    // Solicitar tipo de cuenta con validacion
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

    // Solicitar tipo de persona (Natural o Juridica)
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

    // Solicitar monto con validacion
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

    // Solicitar fecha en formato DD/MM/AAAA
    static string solicitarFecha(const string& concepto = "fecha") {
        cout << "Ingrese " << concepto << " (DD/MM/AAAA): ";
        string fecha;
        cin >> fecha;
        return fecha;
    }

    // Solicitar texto general
    static string solicitarTexto(const string& campo) {
        cout << "Ingrese " << campo << ": ";
        string texto;
        cin >> texto;
        return texto;
    }

    // Solicitar confirmacion (s/n)
    static bool solicitarConfirmacion(const string& mensaje) {
        cout << mensaje << " (s/n): ";
        char respuesta;
        cin >> respuesta;
        return (respuesta == 's' || respuesta == 'S');
    }

    // Mostrar mensaje de exito
    static void mostrarExito(const string& mensaje) {
        cout << "\n";
        mostrarSeparador('*', 40);
        cout << "EXITO: " << mensaje << "\n";
        mostrarSeparador('*', 40);
        cout << "\n";
    }

    // Mostrar mensaje de error
    static void mostrarError(const string& mensaje) {
        cout << "\n";
        mostrarSeparador('!', 40);
        cout << "ERROR: " << mensaje << "\n";
        mostrarSeparador('!', 40);
        cout << "\n";
    }

    // Mostrar mensaje de advertencia
    static void mostrarAdvertencia(const string& mensaje) {
        cout << "\n";
        mostrarSeparador('-', 40);
        cout << "AVISO: " << mensaje << "\n";
        mostrarSeparador('-', 40);
        cout << "\n";
    }

    // Pausar hasta que usuario presione Enter
    static void pausar() {
        cout << "\nPresione Enter para continuar...";
        limpiarBuffer();
        cin.get();
    }

    // Mostrar menu de operaciones
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

    // Solicitar indice con validacion
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

    // Mostrar estadisticas en formato tabla
    static void mostrarEstadistica(const string& concepto, int valor) {
        cout << "| " << concepto;
        int espacios = 35 - concepto.length();
        cout << string(espacios, ' ') << " | " << valor << "\n";
    }

    static void mostrarEstadistica(const string& concepto, double valor) {
        cout << "| " << concepto;
        int espacios = 35 - concepto.length();
        cout << string(espacios, ' ') << " | S/ " << valor << "\n";
    }

    static void mostrarEstadistica(const string& concepto, const string& valor) {
        cout << "| " << concepto;
        int espacios = 35 - concepto.length();
        cout << string(espacios, ' ') << " | " << valor << "\n";
    }
};

#endif
