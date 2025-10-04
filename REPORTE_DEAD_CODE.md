# REPORTE DE DEAD CODE - SISTEMA FINANCIERO
## Fecha: 4 de Octubre, 2025

---

## RESUMEN EJECUTIVO

Se realizó un análisis exhaustivo de todo el código fuente del proyecto para identificar funciones, métodos y código que nunca se utiliza (dead code). Este reporte documenta todos los hallazgos y proporciona recomendaciones.

---

## 🔴 DEAD CODE CRÍTICO (ALTO IMPACTO)

### 1. MÉTODO `ejecutar()` EN TRANSACCIONES - NUNCA SE LLAMA

**Severidad:** ALTA  
**Impacto en Rúbrica:** Afecta conteo de lambdas del integrante 3

#### Archivos Afectados:
- `Transaccion.h` - línea 39: `virtual bool ejecutar() = 0;`
- `Deposito.h` - línea 29: `bool ejecutar() override`
- `Retiro.h` - línea 31: `bool ejecutar() override`

#### Descripción del Problema:
El método abstracto `ejecutar()` está definido en la clase base `Transaccion` y se implementa en las clases derivadas `Deposito` y `Retiro` con **6 lambdas de validación** (3 en cada clase). Sin embargo, **NUNCA SE INVOCA** en todo el proyecto.

#### Búsqueda Realizada:
```
grep -R "->ejecutar()" .  → 0 resultados
grep -R ".ejecutar()" .   → 0 resultados
```

#### Código Muerto Específico:

**En Deposito.h (líneas 29-62):**
- Lambda #1 integrante 3: `montoValido` - validar monto positivo
- Lambda #2 integrante 3: `metodoValido` - validar método depósito
- Lambda #3 integrante 3: `confirmar` - confirmar ejecución exitosa

**En Retiro.h (líneas 31-64):**
- Lambda #1 integrante 3: `montoValido` - validar monto positivo
- Lambda #2 integrante 3: `canalValido` - validar canal retiro
- Lambda #3 integrante 3: `confirmar` - confirmar ejecución exitosa

#### ¿Por Qué Está Muerto?

En `SistemaFinanciero.h`, método `procesarSiguienteTransaccion()` (línea ~825):
```cpp
// ejecutar segun tipo
bool exito = false;
if (op->esDeposito) {
    exito = op->cuenta->depositar(op->transaccion->getMonto());  // ← Llama directo a cuenta
} else {
    exito = op->cuenta->retirar(op->transaccion->getMonto());     // ← Llama directo a cuenta
}
```

**El sistema ejecuta directamente sobre la cuenta, NO sobre la transacción.**

#### Impacto:
- ❌ **6 lambdas documentadas como parte del integrante 3 NO SE EJECUTAN**
- ❌ Validaciones dentro de `ejecutar()` nunca se aplican
- ❌ Mensajes de confirmación nunca se muestran
- ⚠️ Reduce el conteo real de lambdas usadas: 17 documentadas → 11 realmente usadas

#### Recomendaciones:
**OPCIÓN A - Usar el método ejecutar() (RECOMENDADO):**
```cpp
// En SistemaFinanciero::procesarSiguienteTransaccion()
// CAMBIAR ESTO:
bool exito = false;
if (op->esDeposito) {
    exito = op->cuenta->depositar(op->transaccion->getMonto());
} else {
    exito = op->cuenta->retirar(op->transaccion->getMonto());
}

// POR ESTO:
bool exito = op->transaccion->ejecutar();
if (exito) {
    // Aplicar cambio a cuenta
    if (op->esDeposito) {
        op->cuenta->depositar(op->transaccion->getMonto());
    } else {
        op->cuenta->retirar(op->transaccion->getMonto());
    }
}
```

**OPCIÓN B - Eliminar el código muerto:**
- Eliminar método abstracto `ejecutar()` de `Transaccion.h`
- Eliminar implementaciones en `Deposito.h` y `Retiro.h`
- Actualizar documentación reduciendo conteo de lambdas
- ⚠️ Esto afecta negativamente el cumplimiento de la rúbrica

---

## 🟡 DEAD CODE MODERADO (FUNCIONES NO UTILIZADAS)

### 2. GETTERS SIN USO

#### 2.1 `SistemaFinanciero::getHistoricoGlobal()`
**Archivo:** `SistemaFinanciero.h` - línea 1072  
**Definición:** `HistoricoTransacciones& getHistoricoGlobal() { return historicoGlobal; }`  
**Uso:** 0 referencias en todo el proyecto  
**Recomendación:** Mantener (podría usarse en futuras extensiones) o eliminar

#### 2.2 `SistemaFinanciero::getGestorClientes()`
**Archivo:** `SistemaFinanciero.h` - línea 1073  
**Definición:** `GestorClientes& getGestorClientes() { return gestor; }`  
**Uso:** 0 referencias en todo el proyecto  
**Recomendación:** Mantener (podría usarse en futuras extensiones) o eliminar

#### 2.3 `Retiro::getCanal()`
**Archivo:** `Retiro.h` - línea 68  
**Definición:** `string getCanal() const { return canal; }`  
**Uso:** 0 referencias en todo el proyecto  
**Recomendación:** Mantener (getter estándar de encapsulamiento) o eliminar

### 3. MÉTODOS DE CUENTAAHORROS SIN USO

#### 3.1 `calcularInteres()`
**Archivo:** `CuentaAhorros.h` - línea 69  
**Lambda:** Lambda #4 integrante 2 - calcular interés diario  
**Uso:** 0 referencias (solo mencionado en documentación)  
**Impacto:** Lambda documentada pero nunca ejecutada  
**Recomendación:** Agregar llamada en algún método de reporte o eliminar

#### 3.2 `esElegiblePromocion()`
**Archivo:** `CuentaAhorros.h` - línea 80  
**Lambda:** Lambda #5 integrante 2 - verificar elegibilidad promoción  
**Uso:** 0 referencias (solo mencionado en documentación)  
**Impacto:** Lambda documentada pero nunca ejecutada  
**Recomendación:** Agregar llamada en algún método de reporte o eliminar

### 4. MÉTODOS DE GESTORCLIENTES SIN USO

#### 4.1 `filtrarPorSaldo()`
**Archivo:** `GestorClientes.h` - línea 157  
**Lambda:** Lambda #2 integrante 3 - filtrar clientes por saldo  
**Uso:** 0 referencias (solo mencionado en documentación)  
**Impacto:** Lambda documentada pero nunca ejecutada  
**Recomendación:** Agregar opción en menú de reportes o eliminar

### 5. MÉTODOS DE HISTORICOTRANSACCIONES SIN USO

#### 5.1 `filtrarPorMonto()`
**Archivo:** `HistoricoTransacciones.h` - línea 107  
**Lambda:** Lambda #3 integrante 4 - filtrar transacciones por monto  
**Uso:** 0 referencias (solo mencionado en documentación)  
**Impacto:** Lambda documentada pero nunca ejecutada  
**Recomendación:** Agregar opción en menú de reportes o eliminar

### 6. MÉTODOS DE ARCHIVOMANAGER SIN USO

#### 6.1 `ordenarClientesSelection()`
**Archivo:** `ArchivoManager.h` - línea 144  
**Algoritmo:** Selection Sort O(n²)  
**Uso:** 0 referencias en todo el proyecto  
**Impacto:** Algoritmo de ordenamiento documentado pero nunca usado  
**Recomendación:** 
- Llamar en `guardarDatos()` para ordenar antes de guardar
- O eliminar si no se necesita

#### 6.2 `archivoExiste()`
**Archivo:** `ArchivoManager.h` - línea 195  
**Uso:** 0 referencias (solo llamado internamente por `crearRespaldo()`)  
**Recomendación:** Mantener (utility method útil)

#### 6.3 `crearRespaldo()`
**Archivo:** `ArchivoManager.h` - línea 202  
**Uso:** 0 referencias en todo el proyecto  
**Recomendación:** Agregar opción en menú de administración o eliminar

### 7. MÉTODOS RECURSIVOS SIN USO DIRECTO

#### 7.1 `Pila::vaciarRecursivo()`
**Archivo:** `Pila.h` - línea 104  
**Recursividad:** Integrante 4  
**Uso:** 0 referencias en todo el proyecto  
**Nota:** Implementado para cumplir requisito de recursividad  
**Recomendación:** Mantener (cumple rúbrica) o demostrar su uso

#### 7.2 `Cola::tamanoRecursivo()`
**Archivo:** `Cola.h` - línea 98  
**Recursividad:** Integrante 3  
**Uso:** 0 referencias en todo el proyecto  
**Nota:** Implementado para cumplir requisito de recursividad  
**Recomendación:** Mantener (cumple rúbrica) o demostrar su uso

#### 7.3 `ListaDoble::buscarRecursivo()`
**Archivo:** `ListaDoble.h` - línea 188  
**Recursividad:** Integrante 2  
**Uso:** 0 referencias en todo el proyecto  
**Nota:** Implementado para cumplir requisito de recursividad  
**Recomendación:** Mantener (cumple rúbrica) o demostrar su uso

### 8. MÉTODOS DE ESTRUCTURA LISTASIMPLE/LISTADOBLE/PILA/COLA SIN USO

#### 8.1 `ListaSimple/Pila::invertir()`
**Archivo:** `ListaSimple.h` línea 167, `Pila.h` línea 72  
**Método personalizado:** Integrante 1 y 4  
**Uso:** 0 referencias directas en el flujo principal  
**Recomendación:** Mantener (método personalizado para cumplir rúbrica)

---

## 🟢 CÓDIGO VÁLIDO (NO ES DEAD CODE)

Los siguientes métodos SÍ se usan correctamente:

✅ `ordenarCuotasQuick()` - usado en ver cronograma de préstamos  
✅ `ordenarHistorialMerge()` - usado en ver historial de cuenta  
✅ `ordenarClientesHeap()` - usado en generar reporte ordenado  
✅ `ordenarShell()` - usado en ver historial global  
✅ `solicitar()` - usado al solicitar préstamo  
✅ `listarCuentas()` - usado en múltiples lugares  
✅ `listarPrestamos()` - usado en múltiples lugares  
✅ `mostrarInfo()` - usado en varias clases  
✅ `contarRecursivo()` - usado indirectamente por `tamanoRecursivo()`  

---

## ESTADÍSTICAS FINALES

### Conteo de Dead Code:
- **Métodos críticos no usados:** 1 (ejecutar + 6 lambdas)
- **Getters no usados:** 3
- **Métodos con lambdas no usados:** 4 (con 4 lambdas)
- **Algoritmos de ordenamiento no usados:** 1 (Selection Sort)
- **Métodos recursivos sin uso directo:** 3
- **Utilities no usados:** 2

### Impacto en Conteo de Lambdas:
- **Lambdas documentadas:** 17
- **Lambdas realmente ejecutadas:** 11 (después de eliminar las de ejecutar())
- **Diferencia:** -6 lambdas

### Impacto en Cumplimiento de Rúbrica:
- **Lambdas requeridas:** 12 (3 por integrante × 4)
- **Lambdas usadas actualmente:** 11
- **Estado:** ⚠️ **DEFICIENTE POR 1 LAMBDA**

---

## RECOMENDACIONES PRIORITARIAS

### ACCIÓN INMEDIATA REQUERIDA:

#### 1. CRÍTICO - Implementar uso de `ejecutar()` (ALTA PRIORIDAD)
```cpp
// En SistemaFinanciero.h línea ~825
// Cambiar procesarSiguienteTransaccion() para llamar ejecutar()
```
**Esto recupera 6 lambdas y cumple completamente la rúbrica.**

#### 2. RECOMENDADO - Agregar llamadas a métodos con lambdas
- Llamar `calcularInteres()` en algún reporte de cuenta
- Llamar `esElegiblePromocion()` al listar cuentas
- Llamar `filtrarPorSaldo()` en menú de reportes
- Llamar `filtrarPorMonto()` en menú de historial

#### 3. OPCIONAL - Agregar funcionalidades faltantes
- Usar `ordenarClientesSelection()` antes de guardar
- Agregar opción de `crearRespaldo()` en menú admin
- Demostrar uso de métodos recursivos en menú de pruebas

---

## PLAN DE ACCIÓN SUGERIDO

### Fase 1 - Crítico (Implementar YA)
1. ✅ Modificar `procesarSiguienteTransaccion()` para llamar `ejecutar()`
2. ✅ Verificar que las 6 lambdas se ejecuten correctamente
3. ✅ Actualizar documentación confirmando las 17 lambdas funcionales

### Fase 2 - Recomendado (Antes de entregar)
1. Agregar llamadas a `calcularInteres()` y `esElegiblePromocion()`
2. Agregar opción de filtrar por saldo en menú
3. Agregar opción de filtrar por monto en menú

### Fase 3 - Opcional (Mejoras)
1. Implementar respaldo de archivos
2. Crear menú de pruebas para métodos recursivos
3. Limpiar getters no usados

---

## CONCLUSIÓN

El proyecto tiene **dead code significativo** que afecta el cumplimiento de la rúbrica, específicamente en el conteo de lambdas. La implementación del método `ejecutar()` es **CRÍTICA** para cumplir con los requisitos mínimos.

**Estado Actual:** ⚠️ 11/12 lambdas funcionales (DEFICIENTE)  
**Estado Después de Corrección:** ✅ 17/12 lambdas funcionales (EXCEDE)

Se recomienda implementar las correcciones de **Fase 1** inmediatamente antes de la entrega del proyecto.

---

**Generado:** 4 de Octubre, 2025  
**Análisis Completo:** 22 archivos .h, 1 archivo .cpp  
**Método:** Búsqueda exhaustiva con grep + análisis manual

