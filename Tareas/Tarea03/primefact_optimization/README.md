# README DEL PROYECTO
## _Descripción Del Problema a Resolver_


El programa recibe una lista de números enteros positivos y calcula su factorización prima, de forma concurrente.

Se desarrolla la solución en C; se recibe la lista de números por entrada estándar y produce por salida 
estándar una lista con los números en el mismo orden en que fueron ingresados. El usuario podrá ingresar un número que corresponde a la cantidad de hilos a crear, si el usuario no ingresa nigún número, o ingresa alguno inválido, el cantidad default de hilos será la cantidad que tenga el sistema donde se corre el programa. 

Cada línea de la salida 
contiene un número ingresado seguido de su factorización prima. A continuación un ejemplo del programa:

| Entrada Estándar | Salida Estándar |
| ------ | ------ |
| 1 | 1: NA |
| 7 | 7: 7 |
| 25 | 25: 5^2 |
| 87 | 87: 3 29 |
| -40 | -40: invalid number |
| prueba | invalid number |

Se puede encontrar más información del diseño [aquí](https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea02/primefact_pthread/design/readme.md).

# _Manual de Usuario_
## ¿Cómo construir el proyecto?
Ingrese el comando:
`make`
Esto generará la contrucción de todo el proyecto.
## ¿Cómo correr el programa?
Debe abrir una terminal dentro de la carpeta bin. Existen dos formas de interactuar con el programa:

**1.** Ingresar números uno, por uno: cuando se terminen de ingresar los números deseados se debe presionar `Ctrl + d` , posterior se imprimirá la solución con respecto al orden de entrada.

**2.** Redirigir la entrada con un archivo: se imprimirá el resultado de lo almacenado en el archivo, visualmente será instantaneo.

**Para la opción número 1**:
Ingrese a la carpeta bin, abra una terminal, ingrese el siguiente comando:

`./primefact_serial`

Para finalizar el programa presione las teclas:

`Ctrl + d`

**Para la opción número 2**:
Ingrese a la carpeta bin, abra una terminal, ingrese el siguiente comando:

`./primefact_serial < nombreArchivo.txt`

Reemplace nombreArchivo por el nombre de su archivo.

## ¿Cómo remover los archivos y carpetas generados por el programa?
Para esto ingrese el comando:

`make clean`

## ¿Qué otras comprobaciones puedo realizar?
Se pueden verificar si existen **fugas de memoria** con el comando:

`make memcheck`

Se pueden verificar si existen **errores o mala legibilidad en el código** con el comando:

`make lint`

Se puede **generar documentación en Doxygen** con el comando:

`make doc`

Se pueden detectar **thread errors** con el comando:

`make helgrind`

Se pueden realizar **todas las verificaciones anteriores** con el comando:

`make all`

## Algunos ejemplos en terminal
Cuando se ingresan datos de uno por uno debería verse la siguiente forma:

`./primefact_serial`

` 0`

`-1`

`0: NA`

`-1: invalid number`

Cuando se ingresan datos con txt debería verse la siguiente forma:

`./primefact_serial < input000.txt`

`0: NA`

`2: 2`

`9: 3^2`

`10: 2 5`

`52: 2^2 13`

`81: 3^4`

`100: 2^2 5^2`

`113: 113`

`180: 2^2 3^2 5`

`1000: 2^3 5^3`

`1024: 2^10`

## _Créditos_

**Autor**: Josué Retana Rodríguez

**Correo**: josue.retanarodriguez@ucr.ac.cr
