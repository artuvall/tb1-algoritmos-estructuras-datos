# RESUMEN COMPLETO DEL PROYECTO - SISTEMA FINANCIERO
## Análisis Detallado y Explicación para Principiantes

---

## 📚 ÍNDICE
1. [Introducción al Proyecto](#introduccion)
2. [Conceptos Básicos](#conceptos-basicos)
3. [Estructura del Proyecto](#estructura)
4. [Cumplimiento de Rúbrica](#rubrica)
5. [Explicación Detallada por Archivo](#archivos)
6. [Workflow del Sistema](#workflow)
7. [Cómo Usar el Sistema](#uso)
8. [Nuevas Funcionalidades: Persona Natural y Jurídica](#nuevas-funcionalidades)

---

## 1. INTRODUCCIÓN AL PROYECTO {#introduccion}

Este es un **Sistema Financiero** (tipo banco) que permite:
- Registrar clientes (personas naturales o empresas)
- Abrir cuentas bancarias (ahorros o corrientes)
- Realizar depósitos y retiros
- Solicitar préstamos
- Generar reportes ordenados
- Guardar/cargar datos desde archivos
- **NUEVO:** Diferenciación entre Persona Natural y Persona Jurídica

**¿Qué es un Sistema Financiero?**
Imagina que eres el dueño de un banco pequeño. Necesitas un programa que te ayude a:
- Llevar registro de tus clientes (personas individuales y empresas)
- Controlar las cuentas bancarias de cada cliente
- Registrar todas las transacciones (depósitos, retiros)
- Aprobar o rechazar préstamos
- Organizar la información
- **NUEVO:** Validar documentos (DNI para personas, RUC para empresas)

Este programa hace exactamente eso.

---

## 2. CONCEPTOS BÁSICOS {#conceptos-basicos}

### ¿Qué es Programación Orientada a Objetos (POO)?

**Analogía Simple:**
Piensa en objetos del mundo real. Un "Cliente" en el banco tiene:
- **Atributos** (características): nombre, email, código de cliente
- **Métodos** (acciones): registrarse, abrir cuenta, solicitar préstamo

En POO, creamos "clases" que son como "moldes" o "plantillas":
- **Clase Cliente**: El molde que define cómo debe ser un cliente
- **Objeto cliente**: Una persona específica creada usando ese molde

**Ejemplo:**
```cpp
Cliente* juan = new Cliente("001", "Juan", "Perez", "juan@email.com", "C001", "2025-01-01");
// juan es un OBJETO de la clase Cliente
```

### ¿Qué son los Templates (Programación Genérica)?

**Analogía:**
Imagina que tienes una caja que puede guardar cualquier tipo de objeto: libros, juguetes, ropa, etc.

Los templates permiten crear estructuras de datos que funcionan con **cualquier tipo**:
```cpp
ListaSimple<Cliente*>  // Lista que guarda clientes
ListaSimple<Prestamo*> // Lista que guarda préstamos
ListaSimple<int>       // Lista que guarda números
```

La misma estructura (ListaSimple) funciona para diferentes tipos de datos.

### ¿Qué son las Estructuras de Datos?

Son formas de **organizar y almacenar información** en la memoria.

**1. Lista Simple (ListaSimple.h)**
- Como una fila de personas esperando en el banco
- Cada persona apunta a la siguiente
- Solo puedes avanzar hacia adelante

```
[Cliente1] -> [Cliente2] -> [Cliente3] -> NULL
```

**2. Lista Doble (ListaDoble.h)**
- Como una fila donde puedes ir hacia adelante Y hacia atrás
- Cada elemento apunta al siguiente Y al anterior

```
NULL <- [Dato1] <-> [Dato2] <-> [Dato3] -> NULL
```

**3. Pila (Pila.h)**
- Como una pila de platos
- El último que entra es el primero que sale (LIFO)
- Solo puedes sacar el plato de arriba

```
[Plato3] <- top (último en entrar, primero en salir)
[Plato2]
[Plato1]
```

**4. Cola (Cola.h)**
- Como la fila del banco
- El primero que llega es el primero en ser atendido (FIFO)

```
FRENTE -> [Persona1] [Persona2] [Persona3] <- FINAL
          (sale)                  (entra)
```

### ¿Qué son las Lambdas?

Son **funciones pequeñas y anónimas** que puedes crear en el momento.

**Analogía:**
En lugar de crear una función completa con nombre, creas una "mini-función" temporal.

```cpp
// Función tradicional
bool esPositivo(int x) {
    return x > 0;
}

// Lambda (función anónima)
auto esPositivo = [](int x) { return x > 0; };
```

**Ventaja:** Son más cortas y puedes escribirlas donde las necesitas.

---

## 3. ESTRUCTURA DEL PROYECTO {#estructura}

### Jerarquía de Clases (Herencia) - ACTUALIZADO

```
Persona (abstracta)
├── PersonaNatural ✅ MEJORADA
│   └── ClienteNatural ✅ NUEVA
├── PersonaJuridica ✅ MEJORADA
│   └── ClienteJuridica ✅ NUEVA
└── Cliente

CuentaBancaria (abstracta)
├── CuentaAhorros
└── CuentaCorriente

Transaccion (abstracta)
├── Deposito
└── Retiro

Estructuras Genéricas
├── ListaSimple<T>
├── ListaDoble<T>
├── Pila<T>
└── Cola<T>

Gestión
├── GestorClientes
├── SistemaFinanciero ✅ MEJORADO
├── ArchivoManager
└── HistoricoTransacciones

Otros
├── Prestamo
├── Cuota
└── Garantia
```

---

## 4. CUMPLIMIENTO DE RÚBRICA {#rubrica}

### ✅ A. POO y Programación Genérica con 15+ Entidades

**23 Entidades totales (ACTUALIZADO):**
1-23. [Lista completa en CUMPLIMIENTO_RUBRICA.md]
- **NUEVAS:** ClienteNatural, ClienteJuridica
- **MEJORADAS:** PersonaNatural, PersonaJuridica, Persona

### ✅ B. Estructuras Genéricas con Templates y 21 Lambdas (ACTUALIZADO)

**INTEGRANTE 5 - 9 Lambdas (6 NUEVAS):**
1. Comparador por nombre (ArchivoManager)
2. Formatear y escribir cliente (ArchivoManager)
3. Parsear línea (ArchivoManager)
4. **NUEVA:** Validar DNI (PersonaNatural)
5. **NUEVA:** Validar fecha (PersonaNatural)
6. **NUEVA:** Validar RUC persona natural (PersonaNatural)
7. **NUEVA:** Validar RUC persona jurídica (PersonaJuridica)
8. **NUEVA:** Validar DNI representante (PersonaJuridica)
9. **NUEVA:** Validar razón social (PersonaJuridica)

...existing code...

---

## 5. EXPLICACIÓN DETALLADA POR ARCHIVO {#archivos}

### **ENTIDADES DEL DOMINIO**

#### Persona.h (Clase Base Abstracta) - MEJORADA

**¿Qué cambió?**
Se agregaron más atributos y métodos abstractos para soportar diferentes tipos de personas.

**Nuevos atributos:**
- `telefono`: Número de contacto
- `direccion`: Domicilio o dirección fiscal

**Nuevos métodos abstractos:**
```cpp
virtual void mostrarInformacion() = 0;  // Cada tipo muestra su info
virtual string obtenerTipo() = 0;        // "PERSONA NATURAL" o "PERSONA JURIDICA"
virtual string obtenerDocumento() = 0;   // DNI o RUC según tipo
```

**Método útil:**
```cpp
string getNombreCompleto() const {
    if (apellido.empty()) {
        return nombre; // para juridica: solo razon social
    }
    return nombre + " " + apellido; // para natural: nombre + apellido
}
```

#### PersonaNatural.h (Hereda de Persona) - COMPLETAMENTE REDISEÑADA ✅

**¿Qué es una Persona Natural?**
Es un **individuo**, una persona física como tú o yo. Tiene DNI, fecha de nacimiento, y puede tener RUC si trabaja de forma independiente.

**Atributos:**
```cpp
string dni;                 // documento nacional de identidad (8 digitos)
string fechaNacimiento;     // formato: DD/MM/AAAA
string ruc;                 // ruc personal (opcional, 11 digitos, empieza con 10)
bool tieneRuc;              // indica si tiene ruc
```

**Ejemplo de uso:**
```cpp
// Persona natural SIN RUC (empleado o estudiante)
PersonaNatural* juan = new PersonaNatural(
    "PN001",           // id sistema
    "Juan",            // nombre
    "Perez",           // apellido
    "juan@email.com",  // email
    "987654321",       // telefono
    "Av. Lima 123",    // direccion
    "12345678",        // dni
    "15/05/1990"       // fecha nacimiento
);

// Persona natural CON RUC (trabajador independiente)
PersonaNatural* maria = new PersonaNatural(
    "PN002",           // id sistema
    "Maria",           // nombre
    "Lopez",           // apellido
    "maria@email.com", // email
    "987654322",       // telefono
    "Jr. Cusco 456",   // direccion
    "87654321",        // dni
    "20/03/1985",      // fecha nacimiento
    "10876543210"      // ruc (empieza con 10)
);
```

**Validaciones con Lambdas:**

**Lambda 1: Validar DNI**
```cpp
auto validarDni = [](const string& d) { 
    if (d.length() != 8) return false;
    for (char c : d) {
        if (!isdigit(c)) return false;
    }
    return true;
};
```
- Verifica que tenga exactamente 8 dígitos
- Todos los caracteres deben ser números

**Lambda 2: Validar Fecha**
```cpp
auto validarFecha = [](const string& f) {
    return f.length() == 10 && f[2] == '/' && f[5] == '/';
};
```
- Formato: DD/MM/AAAA
- Ejemplo válido: "15/05/1990"

**Lambda 3: Validar RUC Personal**
```cpp
auto validarRucNatural = [](const string& r) {
    if (r.length() != 11) return false;
    if (r[0] != '1' || r[1] != '0') return false;
    for (char c : r) {
        if (!isdigit(c)) return false;
    }
    return true;
};
```
- RUC persona natural: 11 dígitos
- **Debe empezar con "10"** (característica que lo diferencia de RUC empresarial)

**Métodos útiles:**

**calcularEdad():**
```cpp
int calcularEdad() const {
    if (fechaNacimiento.length() >= 10) {
        int anioNac = stoi(fechaNacimiento.substr(6, 4));
        return 2025 - anioNac; // año actual
    }
    return 0;
}
```

**esMayorDeEdad():**
```cpp
bool esMayorDeEdad() const {
    return calcularEdad() >= 18;
}
```

**agregarRuc():**
```cpp
void agregarRuc(string nuevoRuc) {
    ruc = nuevoRuc;
    tieneRuc = true;
    cout << "RUC agregado exitosamente.\n";
}
```
- Permite agregar RUC posteriormente cuando la persona empiece actividad comercial

#### PersonaJuridica.h (Hereda de Persona) - COMPLETAMENTE REDISEÑADA ✅

**¿Qué es una Persona Jurídica?**
Es una **empresa**, una **sociedad** constituida legalmente. No es una persona física, sino una organización que tiene RUC empresarial y representante legal.

**Atributos:**
```cpp
string ruc;                     // ruc empresarial (11 digitos, empieza con 20)
string razonSocial;             // nombre legal de la empresa
string tipoSociedad;            // SAC, SRL, SA, EIRL, Asociacion, etc.
string representanteLegal;      // nombre del representante legal
string dniRepresentante;        // dni del representante
string fechaConstitucion;       // fecha de constitucion de la empresa
```

**Ejemplo de uso:**
```cpp
PersonaJuridica* empresa = new PersonaJuridica(
    "PJ001",                    // id sistema
    "Constructora ABC",         // razon social
    "info@construccionesabc.com", // email
    "014567890",                // telefono
    "Jr. Comercio 456",         // direccion fiscal
    "20123456789",              // ruc empresarial (empieza con 20)
    "SAC",                      // tipo de sociedad
    "Maria Lopez",              // representante legal
    "87654321",                 // dni del representante
    "10/01/2020"                // fecha constitucion
);
```

**Tipos de Sociedad comunes en Perú:**
- **SAC:** Sociedad Anónima Cerrada
- **SRL:** Sociedad de Responsabilidad Limitada
- **SA:** Sociedad Anónima
- **EIRL:** Empresa Individual de Responsabilidad Limitada
- **Asociación:** Sin fines de lucro

**Validaciones con Lambdas:**

**Lambda 1: Validar RUC Empresarial**
```cpp
auto validarRucJuridica = [](const string& r) {
    if (r.length() != 11) return false;
    if (r[0] != '2' || r[1] != '0') return false;
    for (char c : r) {
        if (!isdigit(c)) return false;
    }
    return true;
};
```
- RUC empresarial: 11 dígitos
- **Debe empezar con "20"** (esto lo diferencia del RUC personal)

**Lambda 2: Validar DNI del Representante**
```cpp
auto validarDniRep = [](const string& d) {
    if (d.length() != 8) return false;
    for (char c : d) {
        if (!isdigit(c)) return false;
    }
    return true;
};
```

**Lambda 3: Validar Razón Social**
```cpp
auto validarRazonSocial = [](const string& rs) {
    return !rs.empty() && rs.length() >= 3;
};
```

**Métodos útiles:**

**cambiarRepresentante():**
```cpp
void cambiarRepresentante(string nuevoRep, string nuevoDni) {
    representanteLegal = nuevoRep;
    dniRepresentante = nuevoDni;
    cout << "Representante legal actualizado exitosamente.\n";
}
```
- Se usa cuando hay cambio en la junta de socios

**calcularAntiguedad():**
```cpp
int calcularAntiguedad() const {
    if (fechaConstitucion.length() >= 10) {
        int anioConst = stoi(fechaConstitucion.substr(6, 4));
        return 2025 - anioConst;
    }
    return 0;
}
```

**puedeOperar():**
```cpp
bool puedeOperar() const {
    return ruc.length() == 11 && !representanteLegal.empty();
}
```

#### ClienteNatural.h - NUEVA CLASE ✅

**¿Qué hace?**
Combina PersonaNatural con funcionalidad bancaria. Es una persona natural que es cliente del banco.

**Atributos adicionales:**
```cpp
string codigoCliente;           // codigo unico en el banco
string fechaRegistro;           // fecha de alta como cliente
ListaSimple<CuentaBancaria*> cuentas;
ListaSimple<Prestamo*> prestamos;
```

**Herencia múltiple de funcionalidad:**
- De PersonaNatural: DNI, edad, RUC opcional
- Propios: cuentas bancarias, préstamos

**Métodos específicos:**
- `agregarCuenta()`: Asocia cuenta bancaria
- `agregarPrestamo()`: Asocia préstamo
- `calcularSaldoTotal()`: Suma saldo de todas las cuentas
- `elegibleParaCredito()`: Mayor de edad + al menos 1 cuenta

**Ejemplo de uso completo:**
```cpp
// 1. Crear cliente natural
ClienteNatural* cliente = new ClienteNatural(
    "PN001", "Juan", "Perez", "juan@email.com",
    "987654321", "Av. Lima 123", "12345678", "15/05/1990",
    "CLI001", "03/10/2025"
);

// 2. Abrir cuenta
CuentaAhorros* cuenta = new CuentaAhorros("0011234567", 1000.0, 
                                          cliente->getNombreCompleto(), 
                                          "03/10/2025", 0.05);
cliente->agregarCuenta(cuenta);

// 3. Solicitar préstamo
Prestamo* prestamo = new Prestamo("PREST001", 3000.0, 12, "Aprobado");
cliente->agregarPrestamo(prestamo);

// 4. Ver información completa
cliente->mostrarInformacion();
// Muestra: datos personales + DNI + cuentas + préstamos
```

#### ClienteJuridica.h - NUEVA CLASE ✅

**¿Qué hace?**
Combina PersonaJuridica con funcionalidad bancaria. Es una empresa que es cliente del banco.

**Atributos adicionales:**
```cpp
string codigoCliente;           // codigo unico en el banco
string fechaRegistro;           // fecha de alta como cliente
ListaSimple<CuentaBancaria*> cuentas;
ListaSimple<Prestamo*> prestamos;
```

**Métodos específicos empresariales:**
- `calcularLimiteCredito()`: Basado en antigüedad y saldo
- `elegibleParaCreditoEmpresarial()`: Mínimo 1 año de antigüedad

**Cálculo de límite de crédito:**
```cpp
double calcularLimiteCredito() const {
    double saldoTotal = calcularSaldoTotal();
    int antiguedad = calcularAntiguedad();
    
    // credito base: 10 veces el saldo promedio
    double limiteBase = saldoTotal * 10;
    
    // bonificacion por antiguedad: 5% adicional por cada año
    double bonificacion = limiteBase * (antiguedad * 0.05);
    
    return limiteBase + bonificacion;
}
```

**Ejemplo:**
- Empresa con 3 años de antigüedad
- Saldo total: $10,000
- Límite base: $100,000
- Bonificación: $100,000 * (3 * 0.05) = $15,000
- **Límite total: $115,000**

...existing code...

---

## 6. WORKFLOW DEL SISTEMA {#workflow}

### Flujo Completo de Uso - ACTUALIZADO

**PASO 1: INICIAR SISTEMA**
```
main() crea SistemaFinanciero
  └─> SistemaFinanciero() constructor carga datos de "clientes.txt"
       └─> ArchivoManager lee archivo
            └─> Crea Clientes y los agrega a GestorClientes
```

**PASO 2: REGISTRAR CLIENTE - ACTUALIZADO ✅**
```
Usuario selecciona opción 1
  └─> Sistema pregunta: ¿Persona Natural o Jurídica?
       
       SI ES NATURAL:
       └─> Ingresa datos personales (nombre, apellido, email, teléfono, dirección)
            └─> Ingresa DNI (validado con lambda: 8 dígitos)
                 └─> Ingresa fecha de nacimiento (validado con lambda: DD/MM/AAAA)
                      └─> ¿Tiene RUC? (s/n)
                           └─> Si sí: ingresa RUC (validado: 11 dígitos, empieza con 10)
                                └─> Se crea ClienteNatural
                                     └─> sistema.registrarClienteNatural(cliente)
                                          └─> clientesNaturales.insertarAlFinal(cliente)
       
       SI ES JURIDICA:
       └─> Ingresa datos de empresa (razón social, email, teléfono, dirección fiscal)
            └─> Ingresa RUC empresarial (validado: 11 dígitos, empieza con 20)
                 └─> Ingresa tipo de sociedad (SAC, SRL, SA, etc.)
                      └─> Ingresa representante legal y DNI (validado: 8 dígitos)
                           └─> Ingresa fecha de constitución
                                └─> Se crea ClienteJuridica
                                     └─> sistema.registrarClienteJuridico(cliente)
                                          └─> clientesJuridicos.insertarAlFinal(cliente)
```

**PASO 3: ABRIR CUENTA - ACTUALIZADO ✅**
```
Usuario selecciona opción 2
  └─> Sistema pregunta: ¿Cliente Natural o Jurídico?
       └─> Muestra lista de clientes del tipo seleccionado
            └─> Usuario ingresa código de cliente
                 └─> Sistema busca en lista correspondiente
                      └─> Usuario selecciona tipo de cuenta
                           └─> Se crea CuentaAhorros o CuentaCorriente
                                └─> cliente.agregarCuenta(cuenta)
```

**PASO 4: REALIZAR DEPÓSITO - ACTUALIZADO ✅**
```
Usuario selecciona opción 3
  └─> Sistema pregunta: ¿Cliente Natural o Jurídico?
       └─> Sistema busca cliente por código en lista correspondiente
            └─> Sistema muestra cuentas del cliente
                 └─> Usuario selecciona cuenta y monto
                      └─> cuenta.depositar(monto)
                           ├─> saldo += monto
                           └─> Se crea Transaccion tipo Deposito
                                └─> Se agrega al historialTransacciones
```

**PASO 5: SOLICITAR PRÉSTAMO - ACTUALIZADO ✅**
```
Usuario selecciona opción 4
  └─> Sistema pregunta: ¿Cliente Natural o Jurídico?
       └─> Sistema busca cliente en lista correspondiente
            └─> Usuario solicita monto y plazo
                 └─> Se crea objeto Prestamo
                      └─> prestamo.solicitar() evalúa con lambda
                           ├─> Si monto < 5000: APROBADO
                           └─> Si monto >= 5000: RECHAZADO
                                └─> cliente.agregarPrestamo(prestamo)
```

**PASO 7: LISTAR TODOS LOS CLIENTES - NUEVO ✅**
```
Usuario selecciona opción 7
  └─> Sistema recorre clientesNaturales
       └─> Muestra: nombre, DNI, código, cuentas, préstamos
            └─> Sistema recorre clientesJuridicos
                 └─> Muestra: razón social, RUC, código, representante, cuentas, préstamos
                      └─> Muestra totales por tipo
```

---

## 7. CÓMO USAR EL SISTEMA {#uso}

### Compilar y Ejecutar

**En macOS/Linux:**
```bash
cd /Users/arturovalladolid/repos/ConsoleApplication52
g++ -std=c++17 ConsoleApplication52.cpp -o sistema_financiero
./sistema_financiero
```

**En Windows:**
```cmd
cd ConsoleApplication52
g++ -std=c++17 ConsoleApplication52.cpp -o sistema_financiero.exe
sistema_financiero.exe
```

### Ejemplo de Uso Completo - ACTUALIZADO

**1. Registrar una persona natural:**
```
Seleccione opción: 1
Tipo de persona: 1 (Natural)

--- DATOS PERSONALES ---
ID Sistema: PN001
Nombre: Juan
Apellido: Perez
Email: juan@email.com
Telefono: 987654321
Direccion: Av. Lima 123

--- DOCUMENTO DE IDENTIDAD ---
DNI (8 digitos): 12345678
Fecha Nacimiento (DD/MM/AAAA): 15/05/1990

--- RUC (Opcional) ---
Tiene RUC? (s/n): n

--- DATOS BANCARIOS ---
Codigo Cliente: CLI001
Fecha Registro (DD/MM/2025): 03/10/2025

✅ Cliente persona natural registrado exitosamente!
```

**2. Registrar una persona jurídica (empresa):**
```
Seleccione opción: 1
Tipo de persona: 2 (Jurídica)

--- DATOS DE LA EMPRESA ---
ID Sistema: PJ001
Razon Social: Constructora ABC
Email: info@construccionesabc.com
Telefono: 014567890
Direccion Fiscal: Jr. Comercio 456

--- RUC EMPRESARIAL ---
RUC (11 digitos, inicia con 20): 20123456789

--- TIPO DE SOCIEDAD ---
Ejemplos: SAC, SRL, SA, EIRL, Asociacion
Tipo: SAC

--- REPRESENTANTE LEGAL ---
Nombre Completo: Maria Lopez
DNI Representante: 87654321

--- CONSTITUCION ---
Fecha Constitucion (DD/MM/AAAA): 10/01/2020

--- DATOS BANCARIOS ---
Codigo Cliente: CLI002
Fecha Registro (DD/MM/2025): 03/10/2025

✅ Cliente persona juridica registrado exitosamente!
```

**3. Abrir cuenta para persona natural:**
```
Seleccione opción: 2
Tipo de cliente: 1 (Natural)

=== CLIENTES NATURALES ===
1. Juan Perez | Codigo: CLI001 | DNI: 12345678

Ingrese codigo del cliente: CLI001

Tipo de cuenta:
1. Cuenta de Ahorros
2. Cuenta Corriente
Opcion: 1

Numero de cuenta: 0011234567
Saldo inicial: 1000

✅ Cuenta abierta exitosamente!
```

**4. Listar todos los clientes:**
```
Seleccione opción: 7

=== TODOS LOS CLIENTES DEL SISTEMA ===

--- PERSONAS NATURALES ---

1. Juan Perez
   DNI: 12345678 | Codigo: CLI001
   Cuentas: 1 | Prestamos: 0

--- PERSONAS JURIDICAS ---

1. Constructora ABC
   RUC: 20123456789 | Codigo: CLI002
   Rep. Legal: Maria Lopez
   Cuentas: 0 | Prestamos: 0

Total clientes naturales: 1
Total clientes juridicos: 1
```

---

## 8. NUEVAS FUNCIONALIDADES: PERSONA NATURAL Y JURÍDICA {#nuevas-funcionalidades}

### 📌 Diferencias Clave

| Característica | Persona Natural | Persona Jurídica |
|---------------|-----------------|------------------|
| **¿Qué es?** | Individuo (persona física) | Empresa (sociedad) |
| **Documento principal** | DNI (8 dígitos) | RUC (11 dígitos, empieza con 20) |
| **RUC** | Opcional (11 dígitos, empieza con 10) | Obligatorio (11 dígitos, empieza con 20) |
| **Fecha importante** | Fecha de nacimiento | Fecha de constitución |
| **Representación** | Se representa a sí mismo | Representante legal (persona designada) |
| **Validaciones** | DNI + fecha de nacimiento | RUC + DNI del representante |
| **Métodos especiales** | calcularEdad(), esMayorDeEdad() | calcularAntiguedad(), calcularLimiteCredito() |

### 📌 ¿Cuándo usar cada tipo?

**Usa Persona Natural cuando:**
- Es un cliente individual
- Tiene DNI
- Puede o no tener RUC (trabajador independiente)
- Ejemplo: Juan Perez, estudiante o empleado

**Usa Persona Jurídica cuando:**
- Es una empresa registrada
- Tiene RUC empresarial
- Tiene representante legal
- Ejemplo: "Constructora ABC SAC"

### 📌 Validaciones Automáticas

El sistema valida automáticamente con lambdas:

**Para Persona Natural:**
✅ DNI: exactamente 8 dígitos
✅ Fecha: formato DD/MM/AAAA
✅ RUC (si aplica): 11 dígitos, empieza con "10"

**Para Persona Jurídica:**
✅ RUC empresarial: 11 dígitos, empieza con "20"
✅ DNI del representante: 8 dígitos
✅ Razón social: no vacía, mínimo 3 caracteres

### 📌 Ejemplos Reales

**Persona Natural con RUC:**
- Arquitecto independiente
- Médico que emite recibos por honorarios
- Contador freelance
- **RUC empieza con 10:** 10123456789

**Persona Jurídica:**
- Constructora ABC SAC
- Supermercados XYZ SRL
- Clínica Médica SA
- **RUC empieza con 20:** 20123456789

---

## 9. CONCEPTOS AVANZADOS EXPLICADOS

### ¿Qué es un Algoritmo de Ordenamiento?

**Analogía:**
Tienes un montón de cartas desordenadas y quieres ordenarlas del 1 al 10.

**Diferentes algoritmos:**

**1. QuickSort (Integrante 1)**
- Elige un "pivote" (carta del medio)
- Separa: menores a la izquierda, mayores a la derecha
- Repite recursivamente
- **Velocidad:** Rápido en promedio O(n log n)

**2. MergeSort (Integrante 2)**
- Divide las cartas en mitades
- Ordena cada mitad
- Combina las mitades ordenadas
- **Velocidad:** Siempre O(n log n), estable

**3. HeapSort (Integrante 3)**
- Construye un "montón" (árbol especial)
- Extrae el máximo repetidamente
- **Velocidad:** O(n log n) garantizado

**4. ShellSort (Integrante 4)**
- Ordena elementos lejanos primero
- Reduce el espacio gradualmente
- **Velocidad:** Mejor que O(n²), depende de gaps

**5. SelectionSort (Integrante 5)**
- Busca el mínimo en toda la lista
- Lo coloca al inicio
- Repite para el resto
- **Velocidad:** O(n²), simple pero lento

### ¿Qué es Recursividad?

**Analogía:**
Imagina muñecas rusas (matryoshkas). Para contar todas las muñecas:
1. Cuenta la muñeca actual (1)
2. Abre la muñeca y cuenta las internas (recursión)

**Ejemplo en código:**
```cpp
int contarRecursivo(Nodo<T>* nodo) {
    if (!nodo) return 0;  // Caso base: no hay más nodos
    return 1 + contarRecursivo(nodo->siguiente);  // 1 + conteo del resto
}
```

**¿Cuándo se detiene?**
Cuando llega al "caso base" (cuando no hay más nodos).

### ¿Qué son los Punteros?

**Analogía:**
Un puntero es como una dirección de casa. No es la casa en sí, sino la dirección donde está la casa.

```cpp
Cliente* cliente;  // Puntero: guarda la dirección de memoria
Cliente cliente2;  // Objeto: guarda el objeto completo
```

**¿Por qué usar punteros?**
- Eficiencia: No copias objetos grandes, solo pasas su dirección
- Polimorfismo: Puedes tener un puntero a CuentaBancaria que apunte a CuentaAhorros
- Memoria dinámica: Creas objetos que viven más allá de una función

---

## 10. GLOSARIO DE TÉRMINOS - ACTUALIZADO

**Abstracta:** Clase que no se puede instanciar directamente, sirve como plantilla.

**DNI:** Documento Nacional de Identidad (8 dígitos en Perú), identifica a personas naturales.

**RUC:** Registro Único de Contribuyentes (11 dígitos en Perú):
- Empieza con "10": Persona natural con actividad económica
- Empieza con "20": Persona jurídica (empresa)

**Persona Natural:** Individuo, persona física con DNI.

**Persona Jurídica:** Empresa, sociedad constituida con RUC empresarial.

**Representante Legal:** Persona natural designada para actuar en nombre de una empresa.

**Razón Social:** Nombre legal completo de una empresa.

**SAC:** Sociedad Anónima Cerrada (tipo de empresa en Perú).

**Template:** Permite crear código genérico que funciona con cualquier tipo.

**Lambda:** Función anónima pequeña definida en el lugar donde se usa.

---

## 11. PREGUNTAS FRECUENTES - ACTUALIZADO

**P: ¿Cuál es la diferencia entre PersonaNatural y Cliente?**
R: PersonaNatural es una persona física con DNI. ClienteNatural hereda de PersonaNatural y agrega funcionalidad bancaria (cuentas, préstamos).

**P: ¿Por qué el RUC de persona natural empieza con 10 y el empresarial con 20?**
R: Es el estándar de SUNAT en Perú. El prefijo identifica el tipo de contribuyente.

**P: ¿Una persona natural puede tener RUC?**
R: Sí, es opcional. Lo necesita si trabaja de forma independiente y emite comprobantes.

**P: ¿Qué pasa si cierro el programa?**
R: Los datos se pierden UNLESS guardes con opción 6 (guardar datos).

---

## CONCLUSIÓN - ACTUALIZADO

Este Sistema Financiero es un proyecto completo que demuestra:
- ✅ Dominio de POO (herencia múltiple, polimorfismo, abstracción)
- ✅ Programación genérica con templates
- ✅ Uso avanzado de 21 lambdas (6 más que el mínimo)
- ✅ Implementación de estructuras de datos complejas
- ✅ Conocimiento de algoritmos de ordenamiento
- ✅ Manejo de archivos y persistencia
- ✅ Desarrollo de interfaz de usuario en consola
- ✅ **NUEVO:** Diferenciación real entre persona natural y jurídica
- ✅ **NUEVO:** Validaciones robustas con lambdas específicas
- ✅ **NUEVO:** Sistema de RUC con prefijos correctos
- ✅ **NUEVO:** 23 entidades (8 más que el mínimo)

El proyecto cumple al **140% con todos los requisitos** de la rúbrica y está listo para ser presentado.

---

**Fecha de creación:** 3 de Octubre, 2025
**Autores:** Equipo de 5 integrantes
**Versión:** 2.0 - Completa con Sistema de Personas Natural y Jurídica
**Última actualización:** Sistema de diferenciación de tipos de persona implementado