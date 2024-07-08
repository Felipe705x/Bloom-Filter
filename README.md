# Bloom-Filter

## Funcionalidad

El proyecto implementa una estructura de datos probabilística conocida como *Bloom Filter* que permite verificar si un elemento fue insertado o no: pudiendo equivocarse al responder que el elemento sí fue insertado, pero no al decir que no lo fue.

Además de implementar esta estructura, el proyecto ejecuta tests para comparar la eficiencia de una busqueda de secuencias de palabras entre un método de busqueda que utiliza el filtro y otro que no. Adicionalmente, se obtiene la tasa de falsos-positivos del filtro de Bloom para cada comparación.

## Directorios

- `build`: Se utiliza para almacenar temporalmente los archivos necesarios para comipilar el programa. En este directorió debiese encontrar el ejecutable del programa, llamado `main`
- `data`: Contiene los datos utilizados para los tests (dos archivos .csv)
- `include`: Contiene los encabezados de las funciones, métodos, clases y estructuras
- `source`: Contiene la implementación de los archivos en `include`


## Instrucciones de uso

Para esta sección, necesitará que este ubicado en la carpeta `Bloom-Filter` tanto para compilar como para ejecutar. Esto debe cumplirse también para cualquier sesión de terminal usada en las siguientes subsecciones

### Como compilar:

1. Abrir terminal (PowerShell o Bash)
2. Ejecutar el siguiente comando en la terminal: `make`
    - Si este comando presenta errores: intentar usar privilegios de administrador o bien cerrar y abrir los archivos y carpetas relacionadas

### Como ejecutar:

1. Abrir terminal (PowerShell o Bash)
2. Si en la carpeta `build` está presente el ejecutable `main`: 
    - Ejecutar el siguiente comando en la terminal: `build/main`
    - En caso contrario, ejecutar el siguente comando en la terminal: `make run`

## Notas

- Creditos a Austin Appleby, creador de la función de hash no criptográfica utlizada en el proyecto: *MurmurHash*
- Autores del proyecto:
    - Felipe Avendaño A.
    - Martin Bravo
