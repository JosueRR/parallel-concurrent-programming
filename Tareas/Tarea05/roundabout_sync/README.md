# README DEL PROYECTO
## _Descripción Del Problema a Resolver_


El problema consiste en desarrollar un programa que simule el tráfico en una rotonda con entradas y salidas en los cuatro puntos cardinales (N, O, S, E), la cual es transitada por vehículos que corresponden a hilos de ejecución.  

# _Manual de Usuario_
## ¿Cómo construir el proyecto?
Ingrese el comando:  

`make`

Esto generará la contrucción de todo el proyecto.  

## ¿Cómo correr el programa?
Se debe digitar el comando

`make run`

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

## _Créditos_

**Autor**: Josué Retana Rodríguez

**Correo**: josue.retanarodriguez@ucr.ac.cr
