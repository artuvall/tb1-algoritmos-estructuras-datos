#ifndef CUOTA_H
#define CUOTA_H
//Cuota.h
#include <string>

using namespace std;

class Cuota {
private:
    int num;
    double monto;
    string fechaVenc;
    bool pagado;

public:
    Cuota(int n, double m, string f, bool p = false)
        : num(n), monto(m), fechaVenc(f), pagado(p) {
    }

    bool pagar() {
        pagado = true;
        return true;
    }
};

#endif