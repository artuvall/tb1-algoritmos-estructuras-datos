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

---

## 1. INTRODUCCIÓN AL PROYECTO {#introduccion}

Este es un **Sistema Financiero** (tipo banco) que permite:
- Registrar clientes
- Abrir cuentas bancarias (ahorros o corrientes)
- Realizar depósitos y retiros
- Solicitar préstamos
- Generar reportes ordenados
- Guardar/cargar datos desde archivos

**¿Qué es un Sistema Financiero?**
Imagina que eres el dueño de un banco pequeño. Necesitas un programa que te ayude a:
- Llevar registro de tus clientes
- Controlar las cuentas bancarias de cada cliente
- Registrar todas las transacciones (depósitos, retiros)
- Aprobar o rechazar préstamos
- Organizar la información

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

### Jerarquía de Clases (Herencia)

```
Persona (abstracta)
├── PersonaNatural
├── PersonaJuridica
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
├── SistemaFinanciero
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

**21 Entidades totales:**
1. Persona (abstracta) ✓
2. PersonaNatural ✓
3. PersonaJuridica ✓
4. Cliente ✓
5. CuentaBancaria (abstracta) ✓
6. CuentaAhorros ✓
7. CuentaCorriente ✓
8. Transaccion (abstracta) ✓
9. Deposito ✓
10. Retiro ✓
11. Prestamo ✓
12. Cuota ✓
13. Garantia ✓
14. GestorClientes ✓
15. SistemaFinanciero ✓
16. ArchivoManager ✓
17. HistoricoTransacciones ✓
18. ListaSimple<T> ✓
19. ListaDoble<T> ✓
20. Pila<T> ✓
21. Cola<T> ✓

### ✅ B. Estructuras Genéricas con Templates y 15 Lambdas (3 por integrante)

**INTEGRANTE 1 - ListaSimple:**
- Lambda 1: Prestamo.h línea 53 (aprobar préstamo según monto)
- Lambda 2: Prestamo.h línea 58 (pagar primera cuota no pagada)
- Lambda 3: Prestamo.h línea 74 (comparador para ordenar por número de cuota)

**INTEGRANTE 2 - ListaDoble:**
- Lambda 1: CuentaBancaria.h línea 79 (comparador para ordenar por fecha)
- Lambda 2: CuentaBancaria.h línea 99 (formatear información de cuenta)
- Lambda 3: CuentaAhorros.h línea 30 (validar límite de retiro)

**INTEGRANTE 3 - Cola:**
- Lambda 1: GestorClientes.h línea 51 (comparador para ordenar por código)
- Lambda 2: GestorClientes.h línea 81 (filtrar clientes con saldo mayor a monto)
- Lambda 3: GestorClientes.h línea 89 (contar clientes activos)

**INTEGRANTE 4 - Pila:**
- Lambda 1: HistoricoTransacciones.h línea 28 (comparador para ordenar por monto)
- Lambda 2: HistoricoTransacciones.h línea 37 (verificar si necesita intercambio)
- Lambda 3: HistoricoTransacciones.h línea 57 (filtrar transacciones por monto mínimo)

**INTEGRANTE 5 - ArchivoManager:**
- Lambda 1: ArchivoManager.h línea 38 (comparador por nombre)
- Lambda 2: ArchivoManager.h línea 60 (formatear y escribir cliente)
- Lambda 3: ArchivoManager.h línea 82 (parsear línea)

### ✅ C. 4 Estructuras de Datos Distintas

1. **ListaSimple** (Integrante 1) - usada en Cliente, GestorClientes, Prestamo
2. **ListaDoble** (Integrante 2) - usada en CuentaBancaria, HistoricoTransacciones
3. **Cola** (Integrante 3) - estructura genérica implementada
4. **Pila** (Integrante 4) - estructura genérica implementada

### ✅ D. Cada Estructura con 3+ Métodos Custom

**ListaSimple (Integrante 1):**
1. insertarAlInicio() - línea 48
2. obtenerEnPosicion() - línea 77
3. invertir() - línea 85

**ListaDoble (Integrante 2):**
1. insertarAlFinal() - línea 48
2. eliminarPorValor() - línea 59
3. obtenerEnPosicion() - línea 76

**Cola (Integrante 3):**
1. buscar() - línea 36
2. vaciar() - línea 41
3. contar() - línea 49

**Pila (Integrante 4):**
1. buscar() - línea 39
2. invertir() - línea 44
3. contarSi() - línea 49

### ✅ E. 5 Algoritmos de Ordenamiento Avanzados

1. **QuickSort** (Integrante 1) - Prestamo.h línea 65
2. **MergeSort** (Integrante 2) - CuentaBancaria.h línea 72
3. **HeapSort** (Integrante 3) - GestorClientes.h línea 38
4. **ShellSort** (Integrante 4) - HistoricoTransacciones.h línea 17
5. **SelectionSort** (Integrante 5) - ArchivoManager.h línea 30

### ✅ F. Aplicación en Consola con Usabilidad

- Menú principal claro y funcional
- Mensajes informativos para el usuario
- Validaciones de entrada
- Separadores visuales (líneas de '=')
- Opción de guardar antes de salir

---

## 5. EXPLICACIÓN DETALLADA POR ARCHIVO {#archivos}

### **ESTRUCTURAS DE DATOS GENÉRICAS**

#### ListaSimple.h (Integrante 1)
**¿Qué hace?**
Implementa una lista enlazada simple donde cada elemento apunta al siguiente.

**Componentes clave:**
```cpp
template <typename T>
struct Nodo {
    T dato;           // El valor que guarda
    Nodo* siguiente;  // Apunta al siguiente nodo
};
```

**Métodos importantes:**
- `insertarAlFinal(T dato)`: Agrega un elemento al final de la lista
- `insertarAlInicio(T dato)`: Agrega un elemento al inicio (más rápido)
- `buscar(predicado)`: Busca un elemento usando una condición lambda
- `obtenerEnPosicion(int pos)`: Obtiene el elemento en la posición especificada
- `invertir()`: Invierte el orden de todos los elementos

**¿Por qué es útil?**
- Tamaño dinámico (crece según necesites)
- Inserción/eliminación rápida al inicio
- Usada para guardar clientes, cuentas, préstamos

#### ListaDoble.h (Integrante 2)
**¿Qué hace?**
Similar a ListaSimple pero cada nodo apunta al anterior Y al siguiente.

**Ventaja sobre ListaSimple:**
Puedes recorrer la lista en ambas direcciones.

**Métodos importantes:**
- `insertarAlFinal(T dato)`: Agrega al final (más eficiente que ListaSimple)
- `filtrar(filtro)`: Crea una nueva lista con elementos que cumplan una condición
- `invertir()`: Invierte la lista más eficientemente
- `aplicar(func)`: Aplica una función a cada elemento

**¿Por qué es útil?**
- Ideal para historial de transacciones (puedes navegar hacia atrás)
- Eliminación más eficiente en medio de la lista

#### Pila.h (Integrante 4)
**¿Qué hace?**
Implementa una pila (stack) - último en entrar, primero en salir.

**Analogía:**
Como una pila de libros. Solo puedes agregar o quitar libros desde arriba.

**Métodos principales:**
- `push(T dato)`: Coloca un elemento arriba de la pila
- `pop()`: Saca y devuelve el elemento de arriba
- `top()`: Mira el elemento de arriba sin sacarlo
- `buscar(predicado)`: Busca un elemento en la pila
- `invertir()`: Invierte el orden de la pila

**¿Cuándo usar una pila?**
- Deshacer acciones (Ctrl+Z)
- Navegación de páginas web (botón "atrás")
- Evaluación de expresiones matemáticas

#### Cola.h (Integrante 3)
**¿Qué hace?**
Implementa una cola (queue) - primero en entrar, primero en salir.

**Analogía:**
Como la fila del banco. El primero que llega es el primero en ser atendido.

**Métodos principales:**
- `encolar(T dato)`: Agrega un elemento al final de la cola
- `desencolar()`: Saca y devuelve el elemento del frente
- `frente()`: Mira el elemento del frente sin sacarlo
- `vaciar()`: Elimina todos los elementos
- `contar(condicion)`: Cuenta elementos que cumplen una condición

**¿Cuándo usar una cola?**
- Sistema de turnos
- Procesar tareas en orden de llegada
- Impresión de documentos

---

### **ENTIDADES DEL DOMINIO**

#### Persona.h (Clase Base Abstracta)
**¿Qué es una clase abstracta?**
Es una clase que sirve como "plantilla" pero nunca se crea directamente.

```cpp
class Persona {
protected:
    string id;
    string nombre;
    string apellido;
    string email;
    
public:
    virtual bool validar() = 0;  // = 0 significa "abstracto"
};
```

**¿Por qué abstracta?**
No tiene sentido crear una "Persona" genérica. Queremos crear PersonaNatural o PersonaJuridica específicamente.

#### Cliente.h (Hereda de Persona)
**¿Qué hace?**
Representa un cliente del banco con sus cuentas y préstamos.

**Atributos clave:**
- `ListaSimple<CuentaBancaria*> cuentas`: Todas las cuentas del cliente
- `ListaSimple<Prestamo*> prestamos`: Todos los préstamos del cliente
- `codigo`: Identificador único del cliente

**Métodos importantes:**
- `agregarCuenta(CuentaBancaria* cu)`: Asocia una cuenta al cliente
- `agregarPrestamo(Prestamo* pr)`: Asocia un préstamo al cliente
- `obtenerCuenta(int pos)`: Obtiene una cuenta específica
- `listarCuentas()`: Muestra todas las cuentas del cliente
- `mostrarInfo()`: Muestra información completa del cliente

**¿Por qué es importante?**
Es la entidad central del sistema. Todo gira alrededor de los clientes.

#### CuentaBancaria.h (Clase Base Abstracta)
**¿Qué hace?**
Define la estructura común de todas las cuentas bancarias.

**Atributos protegidos:**
```cpp
protected:
    string numCuenta;
    double saldo;
    string titular;
    ListaDoble<Transaccion*> historialTransacciones;
```

**Métodos virtuales puros:**
```cpp
virtual bool depositar(double monto) = 0;
virtual bool retirar(double monto) = 0;
```

**¿Qué significa "virtual"?**
Permite que las clases hijas (CuentaAhorros, CuentaCorriente) implementen su propia versión.

**Algoritmo de ordenamiento:**
- **MergeSort** para ordenar historial de transacciones
- Divide la lista en mitades recursivamente
- Combina las mitades ordenadas

#### CuentaAhorros.h (Hereda de CuentaBancaria)
**¿Qué hace?**
Cuenta de ahorros con intereses y límite de retiro diario.

**Características especiales:**
- `tasaInteres`: Porcentaje de interés anual
- `limiteRetiroDiario`: Máximo que puedes retirar por día

**Implementación de métodos:**
```cpp
bool depositar(double monto) override {
    saldo += monto;  // Aumenta el saldo
    // Registra la transacción
    return true;
}

bool retirar(double monto) override {
    // Valida que el monto esté dentro del límite
    if (monto <= saldo && monto <= limiteRetiroDiario) {
        saldo -= monto;
        return true;
    }
    return false;
}
```

**Lambdas usadas:**
1. Validar límite de retiro
2. Calcular interés diario
3. Verificar elegibilidad para promoción

#### CuentaCorriente.h (Hereda de CuentaBancaria)
**¿Qué hace?**
Cuenta corriente con sobregiro (puedes gastar más de lo que tienes).

**Característica especial:**
- `sobreGiro`: Monto adicional que puedes gastar más allá de tu saldo

**Ejemplo:**
Si tienes $100 en tu cuenta y un sobregiro de $500, puedes retirar hasta $600.

#### Prestamo.h
**¿Qué hace?**
Representa un préstamo solicitado por un cliente.

**Atributos:**
- `monto`: Cantidad prestada
- `plazo`: Meses para pagar
- `estatus`: "Pendiente", "Aprobado", "Rechazado"
- `historialCuotas`: Lista de cuotas del préstamo

**Método de aprobación:**
```cpp
bool solicitar() {
    // Lambda para aprobar según monto
    auto aprobar = [this]() { return monto < 5000.0; };
    return aprobar();
}
```

**Algoritmo de ordenamiento:**
- **QuickSort** para ordenar cuotas
- Usa partición recursiva
- Muy eficiente en promedio O(n log n)

#### Transaccion.h (Clase Base Abstracta)
**¿Qué hace?**
Define la estructura de cualquier transacción bancaria.

**Atributos comunes:**
- `idTransaccion`: Identificador único
- `monto`: Cantidad de dinero
- `fecha`: Cuándo se realizó
- `tipo`: "Deposito", "Retiro", etc.

**Clases hijas:**
- **Deposito**: Entrada de dinero
- **Retiro**: Salida de dinero

---

### **GESTIÓN Y CONTROL**

#### GestorClientes.h
**¿Qué hace?**
Administra todos los clientes del sistema.

**Responsabilidades:**
- Registrar nuevos clientes
- Buscar clientes por código
- Ordenar clientes
- Contar clientes activos
- Imprimir lista de clientes

**Método clave:**
```cpp
Cliente* buscarPorCodigo(const string& codigo) {
    // Lambda para comparar código
    auto pred = [codigo](Cliente* cl) { 
        return cl->getCodigo() == codigo; 
    };
    Cliente** resultado = listaClientes.buscar(pred);
    return resultado ? *resultado : nullptr;
}
```

**Algoritmo de ordenamiento:**
- **HeapSort** para ordenar clientes
- Construye un heap (árbol binario especial)
- Extrae elementos ordenados uno por uno
- Complejidad O(n log n) garantizada

#### SistemaFinanciero.h
**¿Qué hace?**
Es el "cerebro" del sistema. Coordina todas las operaciones.

**Métodos principales:**

**1. registrarNuevoCliente(Cliente* nuevo)**
```cpp
void registrarNuevoCliente(Cliente* nuevo) {
    if (nuevo->validar()) {
        gestor.registrarNuevoCliente(nuevo);
        cout << "Cliente registrado exitosamente!\n";
    }
}
```

**2. abrirCuenta()**
- Muestra lista de clientes
- Solicita código del cliente
- Pregunta tipo de cuenta (Ahorros o Corriente)
- Crea la cuenta y la asocia al cliente

**3. depositoRetiro()**
- Busca el cliente
- Muestra sus cuentas
- Permite seleccionar una cuenta
- Ejecuta depósito o retiro

**4. solicitarPrestamo()**
- Busca el cliente
- Solicita monto y plazo
- Evalúa aprobación (lambda verifica monto < $5000)
- Asocia préstamo al cliente

**5. generarReporteOrdenado()**
- Ordena clientes con HeapSort
- Muestra lista ordenada
- Cuenta clientes activos

**6. guardarDatos()**
- Ordena clientes con SelectionSort
- Guarda en archivo "clientes.txt"

#### ArchivoManager.h
**¿Qué hace?**
Maneja la persistencia de datos (guardar y cargar desde archivos).

**Formato del archivo:**
```
ID,Nombre,Codigo
001,Juan,C001
002,Maria,C002
```

**Métodos:**

**guardarClientesArchivo():**
```cpp
void guardarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {
    ofstream out(archivo);  // Abre archivo para escribir
    
    auto escribir = [&out](Cliente* cl) { 
        out << cl->getId() << "," 
            << cl->getNombre() << "," 
            << cl->getCodigo() << endl; 
    };
    
    lista.imprimir(escribir);  // Escribe cada cliente
    out.close();
}
```

**cargarClientesArchivo():**
```cpp
void cargarClientesArchivo(const string& archivo, ListaSimple<Cliente*>& lista) {
    ifstream in(archivo);  // Abre archivo para leer
    string line;
    
    while (getline(in, line)) {
        // Usa stringstream para separar por comas
        stringstream ss(line);
        string id, nombre, codigo;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, codigo, ',');
        
        // Crea cliente y lo agrega a la lista
        Cliente* cl = new Cliente(id, nombre, "", "", codigo, "");
        lista.insertarAlFinal(cl);
    }
}
```

**Algoritmo de ordenamiento:**
- **SelectionSort** recursivo
- Busca el mínimo en cada iteración
- Lo coloca en su posición correcta
- Llama recursivamente para el resto

#### HistoricoTransacciones.h
**¿Qué hace?**
Mantiene un registro de todas las transacciones del sistema.

**Algoritmo de ordenamiento:**
- **ShellSort** para ordenar transacciones
- Usa gaps (espacios) decrecientes
- Mejora de InsertionSort
- Muy eficiente para datos casi ordenados

---

## 6. WORKFLOW DEL SISTEMA {#workflow}

### Flujo Completo de Uso

**PASO 1: INICIAR SISTEMA**
```
main() crea SistemaFinanciero
  └─> SistemaFinanciero() constructor carga datos de "clientes.txt"
       └─> ArchivoManager lee archivo
            └─> Crea Clientes y los agrega a GestorClientes
```

**PASO 2: REGISTRAR CLIENTE**
```
Usuario selecciona opción 1
  └─> Ingresa datos (ID, nombre, apellido, email, codigo, fecha)
       └─> Se crea objeto Cliente
            └─> sistema.registrarNuevoCliente(cliente)
                 └─> gestor.registrarNuevoCliente(cliente)
                      └─> listaClientes.insertarAlFinal(cliente)
```

**PASO 3: ABRIR CUENTA**
```
Usuario selecciona opción 2
  └─> Sistema muestra lista de clientes
       └─> Usuario ingresa código de cliente
            └─> Sistema busca cliente (lambda compara códigos)
                 └─> Usuario selecciona tipo de cuenta
                      └─> Se crea CuentaAhorros o CuentaCorriente
                           └─> cliente.agregarCuenta(cuenta)
```

**PASO 4: REALIZAR DEPÓSITO**
```
Usuario selecciona opción 3
  └─> Sistema muestra clientes y solicita código
       └─> Sistema muestra cuentas del cliente
            └─> Usuario selecciona cuenta y monto
                 └─> cuenta.depositar(monto)
                      ├─> saldo += monto
                      └─> Se crea Transaccion tipo Deposito
                           └─> Se agrega al historialTransacciones
```

**PASO 5: SOLICITAR PRÉSTAMO**
```
Usuario selecciona opción 4
  └─> Sistema solicita monto y plazo
       └─> Se crea objeto Prestamo
            └─> prestamo.solicitar() evalúa con lambda
                 ├─> Si monto < 5000: APROBADO
                 └─> Si monto >= 5000: RECHAZADO
                      └─> cliente.agregarPrestamo(prestamo)
```

**PASO 6: GENERAR REPORTE**
```
Usuario selecciona opción 5
  └─> gestor.ordenarClientesHeap()
       └─> HeapSort ordena clientes por código
            └─> gestor.imprimirClientes()
                 └─> Lambda formatea cada cliente
                      └─> Muestra en pantalla
```

**PASO 7: GUARDAR DATOS**
```
Usuario selecciona opción 6
  └─> archiver.ordenarClientesSelection()
       └─> SelectionSort ordena por nombre
            └─> archiver.guardarClientesArchivo()
                 └─> Lambda escribe cada cliente en formato CSV
                      └─> Archivo "clientes.txt" actualizado
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

### Ejemplo de Uso Completo

**1. Registrar un cliente:**
```
Seleccione opción: 1
ID: 001
Nombre: Juan
Apellido: Perez
Email: juan@email.com
Codigo: C001
Fecha Registro: 2025-01-01
```

**2. Abrir una cuenta:**
```
Seleccione opción: 2
Ingrese codigo del cliente: C001
Seleccione tipo de cuenta:
1. Cuenta de Ahorros
2. Cuenta Corriente
Opcion: 1
Ingrese numero de cuenta: ACC001
Ingrese saldo inicial: 1000
```

**3. Realizar un depósito:**
```
Seleccione opción: 3
Ingrese codigo del cliente: C001
Seleccione numero de cuenta: 1
1. Deposito
2. Retiro
Opcion: 1
Ingrese monto: 500
```

**4. Solicitar un préstamo:**
```
Seleccione opción: 4
Ingrese codigo del cliente: C001
Ingrese monto del prestamo: 3000
Ingrese plazo (meses): 12
```

**5. Generar reporte:**
```
Seleccione opción: 5
(Sistema ordena y muestra todos los clientes)
```

**6. Guardar datos:**
```
Seleccione opción: 6
(Sistema guarda en clientes.txt)
```

---

## 8. CONCEPTOS AVANZADOS EXPLICADOS

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

## 9. VERIFICACIÓN DE RÚBRICA COMPLETA

### ✅ CHECKLIST FINAL

**A. POO y 15+ Entidades:** ✅ 21 entidades implementadas

**B. Templates y 15 Lambdas:** ✅ 
- 4 estructuras genéricas (ListaSimple, ListaDoble, Pila, Cola)
- 15 lambdas documentadas (3 por integrante)

**C. 4 Estructuras de Datos:** ✅
- ListaSimple (Integrante 1)
- ListaDoble (Integrante 2)
- Cola (Integrante 3)
- Pila (Integrante 4)

**D. 3 Métodos por Estructura:** ✅
- Cada estructura tiene 3+ métodos custom implementados y documentados

**E. 5 Algoritmos de Ordenamiento:** ✅
- QuickSort (Integrante 1) - Prestamo
- MergeSort (Integrante 2) - CuentaBancaria
- HeapSort (Integrante 3) - GestorClientes
- ShellSort (Integrante 4) - HistoricoTransacciones
- SelectionSort (Integrante 5) - ArchivoManager

**F. Aplicación en Consola:** ✅
- Menú funcional e intuitivo
- Mensajes claros
- Validaciones
- Estética con separadores

---

## 10. GLOSARIO DE TÉRMINOS

**Abstracta:** Clase que no se puede instanciar directamente, sirve como plantilla.

**Template:** Permite crear código genérico que funciona con cualquier tipo.

**Lambda:** Función anónima pequeña definida en el lugar donde se usa.

**Puntero:** Variable que guarda la dirección de memoria de otra variable.

**Override:** Reemplazar un método de la clase padre en la clase hija.

**Virtual:** Permite que un método sea sobrescrito por clases hijas.

**Herencia:** Clase que obtiene atributos y métodos de otra clase padre.

**Polimorfismo:** Capacidad de tratar objetos de diferentes tipos con la misma interfaz.

**LIFO:** Last In, First Out (Último en entrar, primero en salir) - Pila.

**FIFO:** First In, First Out (Primero en entrar, primero en salir) - Cola.

**O(n log n):** Notación Big O, indica la velocidad de un algoritmo.

**Recursividad:** Función que se llama a sí misma.

---

## 11. PREGUNTAS FRECUENTES

**P: ¿Por qué usamos punteros en las listas?**
R: Para no copiar objetos completos. Es más eficiente pasar direcciones de memoria.

**P: ¿Qué diferencia hay entre ListaSimple y ListaDoble?**
R: ListaDoble permite navegar en ambas direcciones, pero usa más memoria.

**P: ¿Cuándo usar Pila vs Cola?**
R: Pila para "deshacer" o procesar en orden inverso. Cola para procesar en orden de llegada.

**P: ¿Por qué tantos algoritmos de ordenamiento?**
R: Cada uno tiene ventajas en diferentes situaciones (datos grandes, casi ordenados, etc.)

**P: ¿Qué pasa si cierro el programa?**
R: Los datos se pierden UNLESS guardes con opción 6 (guardar datos).

---

## CONCLUSIÓN

Este Sistema Financiero es un proyecto completo que demuestra:
- ✅ Dominio de POO (herencia, polimorfismo, abstracción)
- ✅ Programación genérica con templates
- ✅ Uso avanzado de lambdas
- ✅ Implementación de estructuras de datos complejas
- ✅ Conocimiento de algoritmos de ordenamiento
- ✅ Manejo de archivos y persistencia
- ✅ Desarrollo de interfaz de usuario en consola

El proyecto cumple al 100% con todos los requisitos de la rúbrica y está listo para ser presentado.

---

**Fecha de creación:** 3 de Octubre, 2025
**Autores:** Equipo de 5 integrantes
**Versión:** 1.0 - Completa y Funcional

