# Diseño del Programa
## _Bosquejo General de la Solución_

El programa se puede dividir en tres grandes partes: lectura, impresión y cálculo de factores. En general funcionará de la siguiente forma:

- El usuario ingresa una lista de números enteros por la entrada estándar.
- El programa lee línea, realiza verificaciones, según el caso asigna un resultado y lo imprime. (Este paso se repite por cada línea).
- Al terminar el programa, la consola tendrá el resultado: una lista con los números en el mismo orden en que fueron ingresados. Cada línea de la salida contiene un número ingresado seguido de su factorización prima, o en su defecto número inválido. 

## _Diagrama en UML_

![Diagrama UML](https://lucid.app/publicSegments/view/5dadf237-9bcb-4e87-9278-22a838872e5d/image.png)

https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea01/primefact_serial/design/UML_diagrama.png

## _Subrutinas y Archivos_

Para desarrollar una solución se crearán los siguientes archivos con las siguientes funciones:
- main: objeto controlador del programa, llama las funciones necesarias para resolver el problema.
- primefact.h: contiene y define lo que compone a la clase; atributos y métodos.
- primefact.c: implementación de la clase y sus definiciones.
