cmake_minimum_required(VERSION 3.20)
project(ConsoleApplication52)

set(CMAKE_CXX_STANDARD 17)

# Add all your source files
add_executable(ConsoleApplication52
    ConsoleApplication52.cpp
    ArchivoManager.h
    Cliente.h
    Cola.h
    CuentaAhorros.h
    CuentaBancaria.h
    CuentaCorriente.h
    Cuota.h
    Deposito.h
    Garantia.h
    GestorClientes.h
    HistoricoTransacciones.h
    ListaDoble.h
    ListaSimple.h
    Persona.h
    PersonaJuridica.h
    PersonaNatural.h
    Pila.h
    Prestamo.h
    SistemaFinanciero.h
    Transaccion.h
        Retiro.h
        Interfaz.h
)
