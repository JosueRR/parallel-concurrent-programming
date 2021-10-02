# Diseño del Programa
## _Bosquejo General de la Solución_

El programa se puede dividir en tres grandes partes: lectura, impresión y cálculo de factores. En general funcionará de la siguiente forma:

- El usuario ingresa una lista de números enteros por la entrada estándar.
- El programa lee línea, realiza verificaciones, según el caso asigna un resultado y lo imprime. (Este paso se repite por cada línea).
- Al terminar el programa, la consola tendrá el resultado: una lista con los números en el mismo orden en que fueron ingresados. Cada línea de la salida contiene un número ingresado seguido de su factorización prima, o en su defecto número inválido. 

## _Diagrama de Secuencia en UML_

![Diagrama Secuencia UML](https://lucid.app/publicSegments/view/5dadf237-9bcb-4e87-9278-22a838872e5d/image.png)

https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea01/primefact_serial/design/UML_diagrama.png

## _Archivos_

La solución del problema se dividirá en 3 archivos con las siguientes funciones:
- main: objeto controlador del programa, llama las funciones necesarias para resolver el problema.
- primefact.h: contiene y define lo que compone a la clase; atributos y métodos.
- primefact.c: implementación de la clase y sus definiciones.

## _Subrutinas_

La solución del proble se va modularizar en las siguientes subrutinas:
- lecturaDatos: lee una línea de texto y clasifica el tipo de número según el caso.
- calcularFactores: calcula los factores primos de un número dado.
- agregarElemento: agrega un elemento a un arreglo.
- impresionDatos: imprime los resultados de la solución.
 
## _Diagrama General en UML_

![Diagrama General UML](https://lucid.app/publicSegments/view/3af809c4-4a78-49a8-a18b-f138e7af44f7/image.png)
https://lucid.app/publicSegments/view/3af809c4-4a78-49a8-a18b-f138e7af44f7/image.png

## _Diagrama de Memoria_

![Diagrama de Memoria](https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea02/primefact_pthread/design/Diagrama_Memoria.png)
