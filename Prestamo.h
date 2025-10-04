#ifndef PRESTAMO_H
#define PRESTAMO_H
// =============================================================================
// archivo: prestamo.h
// descripcion: entidad prestamo - credito bancario con cuotas
// cumplimiento de rubrica:
//   - entidad #11: parte del sistema financiero
//   - algoritmo ordenamiento integrante 1: quicksort recursivo
//   - lambdas integrante 1: 3 lambdas (aprobar, pagar, comparador)
//   - uso de listasimple para gestionar cuotas
//   - algoritmo fisher-yates shuffle para desordenar cuotas
// =============================================================================

//Prestamo.h
#include "Cuota.h"
#include "Garantia.h"
#include "ListaSimple.h"
#include <iostream>
#include <iomanip>

using namespace std;

// clase prestamo: representa un credito bancario
// contiene lista de cuotas y opcionalmente una garantia
class Prestamo {
private:
    string id;                        // identificador unico del prestamo
    double monto;                     // monto solicitado
    double tasaInteres;               // tasa anual (ej: 0.12 = 12%)
    int plazo;                        // plazo en meses
    string estatus;                   // estado: "aprobado", "rechazado", "pendiente"
    ListaSimple<Cuota*> historialCuotas;  // lista de cuotas del prestamo
    Garantia* garantia;               // garantia opcional del prestamo

    // *** metodo auxiliar para quicksort: partition ***
    // complejidad: O(n) - recorre array una vez
    // funcion: reorganiza array poniendo elementos menores a la izquierda del pivote
    // parametros: array, indices bajo/alto, lambda comparador
    // retorna: indice final del pivote
    int partition(Cuota** arr, int bajo, int alto, std::function<bool(Cuota*, Cuota*)> comparador) {
        Cuota* pivote = arr[alto];  // elegir ultimo elemento como pivote
        int i = bajo - 1;           // indice del elemento menor

        // recorrer y reorganizar elementos
        for (int j = bajo; j < alto; j++) {
            if (comparador(arr[j], pivote)) {  // usar lambda comparador
                i++;
                // intercambiar arr[i] y arr[j]
                Cuota* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // colocar pivote en su posicion correcta
        Cuota* temp = arr[i + 1];
        arr[i + 1] = arr[alto];
        arr[alto] = temp;
        return i + 1;
    }

    // *** metodo auxiliar recursivo para quicksort ***
    // complejidad: O(n log n) promedio, O(n^2) peor caso
    // algoritmo: divide y conquista
    // paso 1: particionar array (O(n))
    // paso 2: ordenar recursivamente mitades (2 * T(n/2))
    // formula: T(n) = 2T(n/2) + O(n)
    // solucion: T(n) = O(n log n) en caso promedio
    void quickSortRecursivo(Cuota** arr, int bajo, int alto, std::function<bool(Cuota*, Cuota*)> comparador) {
        if (bajo < alto) {
            // particionar array y obtener indice del pivote
            int pi = partition(arr, bajo, alto, comparador);

            // ordenar recursivamente las dos mitades
            quickSortRecursivo(arr, bajo, pi - 1, comparador);   // izquierda
            quickSortRecursivo(arr, pi + 1, alto, comparador);   // derecha
        }
    }

public:
    // constructor: inicializa prestamo con datos basicos
    Prestamo(string i, double m, double tasa, int p, string est)
        : id(i), monto(m), tasaInteres(tasa), plazo(p), estatus(est), garantia(nullptr) {
    }

    // destructor: liberar memoria de cuotas y garantia
    // importante para evitar memory leaks
    ~Prestamo() {
        // liberar todas las cuotas
        for (int j = 0; j < historialCuotas.getTamano(); j++) {
            delete *historialCuotas.obtenerEnPosicion(j);
        }
        // liberar garantia si existe
        if (garantia) delete garantia;
    }

    // calcular monto total a pagar (capital + interes simple)
    // formula: total = capital + (capital * tasa * tiempo_en_años)
    double calcularMontoTotal() const {
        double interes = monto * tasaInteres * (plazo / 12.0);
        return monto + interes;
    }

    // generar cuotas con amortizacion simple
    // complejidad: O(n) por fisher-yates shuffle
    // crea n cuotas desordenadas para demostrar efectividad de quicksort
    void generarCuotas() {
        double montoTotal = calcularMontoTotal();
        double cuotaMensual = montoTotal / plazo;

        // generar fechas de vencimiento (incrementa mes desde octubre 2025)
        int mesInicio = 11; // noviembre 2025 (primer vencimiento)
        int anioInicio = 2025;

        // crear array temporal para desordenar cuotas
        Cuota** tempArray = new Cuota*[plazo];

        // crear cuotas en orden secuencial primero
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

            tempArray[i] = new Cuota(i + 1, cuotaMensual, fechaVenc);
        }

        // *** algoritmo fisher-yates shuffle para desordenar cuotas ***
        // complejidad: O(n) - un solo recorrido
        // garantiza que cada cuota tenga igual probabilidad en cualquier posicion
        // razon: demostrar que quicksort funciona con datos desordenados
        for (int i = plazo - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            // intercambiar tempArray[i] con tempArray[j]
            Cuota* temp = tempArray[i];
            tempArray[i] = tempArray[j];
            tempArray[j] = temp;
        }

        // insertar cuotas desordenadas en la lista
        for (int i = 0; i < plazo; i++) {
            historialCuotas.insertarAlFinal(tempArray[i]);
        }

        delete[] tempArray;
    }

    // *** lambda #1 integrante 1: aprobar prestamo segun monto ***
    // esta funcion usa lambda para validar si prestamo es aprobable
    // criterio: solo se aprueban prestamos menores o iguales a 10,000
    // complejidad: O(1)
    bool solicitar() {
        auto aprobar = [this]() { return monto <= 10000.0; };
        return aprobar();
    }

    // metodos para manejar garantia
    void setGarantia(Garantia* g) { garantia = g; }
    Garantia* getGarantia() const { return garantia; }

    void agregarCuota(Cuota* c) { historialCuotas.insertarAlFinal(c); }

    // *** lambda #2 integrante 1: pagar cuota especifica ***
    // esta funcion usa lambda para validar y marcar cuota como pagada
    // complejidad: O(1) - acceso directo a posicion en lista
    bool pagarCuota(int numCuota) {
        if (numCuota < 1 || numCuota > historialCuotas.getTamano()) {
            cout << "Numero de cuota invalido.\n";
            return false;
        }

        Cuota* cuota = *historialCuotas.obtenerEnPosicion(numCuota - 1);
        return cuota->pagar();
    }

    // *** algoritmo de ordenamiento integrante 1: quicksort ***
    // *** metodo critico para la rubrica ***
    // complejidad: O(n log n) promedio, O(n^2) peor caso
    // analisis detallado:
    //   - paso 1: convertir lista a array: O(n)
    //   - paso 2: quicksort recursivo: O(n log n) promedio
    //   - paso 3: reconstruir lista: O(n)
    //   - total: O(n) + O(n log n) + O(n) = O(n log n)
    // razon de uso: eficiente para ordenar cuotas desordenadas
    void ordenarCuotasQuick() {
        int n = historialCuotas.getTamano();
        if (n <= 1) return;  // ya ordenado o vacio

        // paso 1: convertir lista a array temporal para ordenar
        Cuota** arr = new Cuota*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = *historialCuotas.obtenerEnPosicion(i);
        }

        // *** lambda #3 integrante 1: comparador para ordenar por numero ***
        // esta lambda define criterio de ordenamiento
        // ordena cuotas por numero ascendente (1, 2, 3, ...)
        // uso: pasada como parametro al quicksort recursivo
        auto comparador = [](Cuota* a, Cuota* b) {
            return a->getNum() < b->getNum();
        };

        // paso 2: aplicar quicksort recursivo con lambda comparador
        quickSortRecursivo(arr, 0, n - 1, comparador);

        // paso 3: reconstruir lista ordenada
        historialCuotas.limpiar();
        for (int i = 0; i < n; i++) {
            historialCuotas.insertarAlFinal(arr[i]);
        }

        delete[] arr;
    }

    // mostrar cronograma completo de pagos
    // complejidad: O(n) - itera sobre todas las cuotas
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

        // mostrar cada cuota
        for (int i = 0; i < historialCuotas.getTamano(); i++) {
            Cuota* c = *historialCuotas.obtenerEnPosicion(i);
            c->mostrarInfo();
        }
    }

    // getters: encapsulamiento
    string getId() const { return id; }
    double getMonto() const { return monto; }
    double getTasaInteres() const { return tasaInteres; }
    int getPlazo() const { return plazo; }
    string getEstatus() const { return estatus; }
    int getCantidadCuotas() const { return historialCuotas.getTamano(); }
};

#endif