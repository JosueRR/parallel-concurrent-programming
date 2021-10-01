# Diseño del Programa
## _Bosquejo General de la Solución_

El programa se puede dividir en cuatro grandes partes: lectura, impresión, algoritmo de cálculo de factores y paralelizar el cálculo de factores. En general se funcionará de la siguiente forma:

- El usuario ingresa una lista de números enteros por la entrada estándar.
- El programa lee las líneas, realiza verificaciones, según el caso asigna un resultado y lo imprime.
- Al terminar el programa, la consola tendrá el resultado: una lista con los números en el mismo orden en que fueron ingresados. Cada línea de la salida contiene un número ingresado seguido de su factorización prima, o en su defecto número inválido. 

## _Diagrama de Secuencia en UML_

![Diagrama Secuencia UML](https://lucid.app/publicSegments/view/5dadf237-9bcb-4e87-9278-22a838872e5d/image.png)


## _Estructura General de la Solución_

La solución del problema se dividirá en 4 partes con las siguientes responsabilidades:
- main: controlador del programa, llama las funciones necesarias para resolver el problema..
- primefact: contiene las subrutinas relacionadas a lectura, impresión y el algoritmo de cálculo de factores.
- parallel: contiene las subrutinas necesarias para crear calcular los fact. primos de forma concurrente.

## _Archivos_

La solución del problema se dividirá en 5 archivos con las siguientes funciones:
- main: objeto controlador del programa.
- primefact.h: contiene y define lo que compone a la clase; atributos y métodos.
- primefact.c: implementación de la clase y sus definiciones.
- parallel.h: contiene y define lo que compone a la clase; atributos y métodos.
- parallel.c: implementación de la clase y sus definiciones.

## _Subrutinas y Estructuras_

La solución del va a utilizar las siguientes estructuras:
- BloqueDatos: representa una entrada del usuario.
- EstructuraArreglo: representa un arreglo de entradas.
- shared_data: representa los datos compartidos por los hilos.
- private_data: representa los datos privados de cada hilo.

La solución del problema se va modularizar en las siguientes subrutinas:

**Lectura y Validación**

- lecturaDatos: lee una entrada y crea un arreglo dinámico.
- validarEntrada: realiza validaciones realcionadas a una entrada.
- initArray: inicializa el arreglo de datos.
- insertArray: inserta un elemento al arreglo de datos.
- freeArray: libera la memoria utilizada por el arreglo.

**Algoritmo Calculo de Factores**

- calcularFactores: calcula los factores primos de un número dado.
- agregarElemento: agrega un factor a un arreglo.

**Impresión**

- printArregloFactores: imprime una lista de factores.
- printResult: imprime el resultado general (invoca printArregloFactores).

**Paralelizar el Programa**

- repartirTareas: reparte los índice sobre los cuales deberían trabajar lso hilos.
- initParalelizador: asigna la cantidad de hilos e invoca al método que hace los cálculos.
- createThreads: crea los hilos y los invoca.
- calcularFactorParalelo: calculo los factores dado un hilo.
 
## _Diagrama General en UML_

![Diagrama General UML](https://lucid.app/publicSegments/view/ff41f3bb-2eaf-4818-906a-e74e3fc7cf78/image.png)

## _Diagrama de Memoria_ ##

![Diagrama Memoria]()
