#ifndef PRESTAMO_H
#define PRESTAMO_H
//Prestamo.h
#include "Cuota.h"
#include "Garantia.h"
#include "ListaSimple.h"
#include <iostream>
#include <iomanip>

using namespace std;

class Prestamo {
private:
    string id;
    double monto;
    double tasaInteres; // tasa anual (ej: 0.12 = 12%)
    int plazo; // en meses
    string estatus;
    ListaSimple<Cuota*> historialCuotas;
    Garantia* garantia;

    // metodo auxiliar para quicksort: partition
    int partition(Cuota** arr, int bajo, int alto, std::function<bool(Cuota*, Cuota*)> comparador) {
        Cuota* pivote = arr[alto];
        int i = bajo - 1;
        for (int j = bajo; j < alto; j++) {
            if (comparador(arr[j], pivote)) {
                i++;
                Cuota* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Cuota* temp = arr[i + 1];
        arr[i + 1] = arr[alto];
        arr[alto] = temp;
        return i + 1;
    }

    // metodo auxiliar recursivo para quicksort
    void quickSortRecursivo(Cuota** arr, int bajo, int alto, std::function<bool(Cuota*, Cuota*)> comparador) {
        if (bajo < alto) {
            int pi = partition(arr, bajo, alto, comparador);
            quickSortRecursivo(arr, bajo, pi - 1, comparador);
            quickSortRecursivo(arr, pi + 1, alto, comparador);
        }
    }

public:
    Prestamo(string i, double m, double tasa, int p, string est)
        : id(i), monto(m), tasaInteres(tasa), plazo(p), estatus(est), garantia(nullptr) {
    }

    // destructor: liberar memoria de cuotas y garantia
    ~Prestamo() {
        // liberar cuotas
        for (int j = 0; j < historialCuotas.getTamano(); j++) {
            delete *historialCuotas.obtenerEnPosicion(j);
        }
        // liberar garantia si existe
        if (garantia) delete garantia;
    }

    // calcular monto total a pagar (capital + interes simple)
    double calcularMontoTotal() const {
        double interes = monto * tasaInteres * (plazo / 12.0);
        return monto + interes;
    }

    // generar cuotas con amortizacion simple
    void generarCuotas() {
        double montoTotal = calcularMontoTotal();
        double cuotaMensual = montoTotal / plazo;

        // generar fechas de vencimiento (incrementa mes desde octubre 2025)
        int mesInicio = 11; // noviembre 2025 (primer vencimiento)
        int anioInicio = 2025;

        for (int i = 0; i < plazo; i++) {
            int mesVenc = mesInicio + i;
            int anioVenc = anioInicio;

            // ajustar anio si pasa de diciembre
            while (mesVenc > 12) {
                mesVenc -= 12;
                anioVenc++;
            }

            // formato: MM/YYYY
            string fechaVenc = (mesVenc < 10 ? "0" : "") + to_string(mesVenc) + "/" + to_string(anioVenc);

            Cuota* c = new Cuota(i + 1, cuotaMensual, fechaVenc);
            historialCuotas.insertarAlFinal(c);
        }
    }

    bool solicitar() {
        // lambda 1 integrante 1: aprobar prestamo segun monto
        auto aprobar = [this]() { return monto <= 10000.0; };
        return aprobar();
    }

    // metodos para manejar garantia
    void setGarantia(Garantia* g) { garantia = g; }
    Garantia* getGarantia() const { return garantia; }

    void agregarCuota(Cuota* c) { historialCuotas.insertarAlFinal(c); }

    bool pagarCuota(int numCuota) {
        // lambda 2 integrante 1: pagar cuota especifica
        if (numCuota < 1 || numCuota > historialCuotas.getTamano()) {
            cout << "Numero de cuota invalido.\n";
            return false;
        }

        Cuota* cuota = *historialCuotas.obtenerEnPosicion(numCuota - 1);
        return cuota->pagar();
    }

    // quicksort integrante 1: ordenar cuotas
    void ordenarCuotasQuick() {
        int n = historialCuotas.getTamano();
        if (n <= 1) return;

        // convertir lista a array temporal para ordenar
        Cuota** arr = new Cuota*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = *historialCuotas.obtenerEnPosicion(i);
        }

        // lambda 3 integrante 1: comparador para ordenar por numero de cuota (menor a mayor)
        auto comparador = [](Cuota* a, Cuota* b) {
            return a->getNum() < b->getNum();
        };

        quickSortRecursivo(arr, 0, n - 1, comparador);

        // reconstruir lista ordenada
        historialCuotas.limpiar();
        for (int i = 0; i < n; i++) {
            historialCuotas.insertarAlFinal(arr[i]);
        }

        delete[] arr;
    }

    // mostrar cronograma completo de pagos
    void mostrarCronograma() const {
        cout << "\n=== CRONOGRAMA DE PAGOS ===\n";
        cout << "Prestamo ID: " << id << "\n";
        cout << "Monto Original: S/ " << fixed << setprecision(2) << monto << "\n";
        cout << "Tasa Interes: " << (tasaInteres * 100) << "% anual\n";
        cout << "Plazo: " << plazo << " meses\n";
        cout << "Monto Total a Pagar: S/ " << calcularMontoTotal() << "\n";
        cout << "Cuota Mensual: S/ " << (calcularMontoTotal() / plazo) << "\n";

        if (garantia) {
            cout << "Garantia: ";
            garantia->mostrarInfo();
            cout << "\n";
        }

        cout << string(60, '-') << "\n";

        for (int i = 0; i < historialCuotas.getTamano(); i++) {
            Cuota* c = *historialCuotas.obtenerEnPosicion(i);
            c->mostrarInfo();
        }
    }

    // getters
    string getId() const { return id; }
    double getMonto() const { return monto; }
    double getTasaInteres() const { return tasaInteres; }
    int getPlazo() const { return plazo; }
    string getEstatus() const { return estatus; }
    int getCantidadCuotas() const { return historialCuotas.getTamano(); }
};

#endif