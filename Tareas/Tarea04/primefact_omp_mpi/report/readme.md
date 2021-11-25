# Documento de Reporte
## _Aspectos Generales_
Para realizar el reporte se utilizó el caso de prueba **input021.txt**, que cuenta con 40 061 elementos a procesar. También, las pruebas se realizan en un cluster que cuenta con 8 CPUs.

## _Optimización 01 - Mapeo dinámico_

**1.** _Rendimiento del código antes de realizar las modificaciones_

Utilizando una mapeo estático de tipo bloque no balanceado se obtuvo una duración de _173.18s_.

**2.** _Profiling_

En este caso no es necesario ya que es impuesto en el enunciado.

**3.** _Modificaciones_

Se implementará un modelo de mapeo dinámico productor-consumidor que utilizará variables contadoras compartidas protegidas por mutex.

**4.** _Rendimiento del código después de realizar las modificaciones_

Utilizando una mapeo dinámico se obtuvo una duración de _165.18s_.

**5.** _Lecciones Aprendidas_

 El mapeo por bloque tuvo un *speedup* y _efficiency_ respectivamente de _7.56_ y _0.94_, mientras que el dinámico _7.92_ y _0.99_, por lo tanto considerando que la implementación es relativamente sencilla y también los resultados del análisis, el mapeo dinámico es superior al estático por bloque, y a su vez da muy buenos resultados.

 ## _Optimización 02 - Calcular Factores_

**1.** _Rendimiento del código antes de realizar las modificaciones_

El proyecto post-optim01 obtuvo una duración de _165.18s_.

**2.** _Profiling_

Como se puede observar en el análisis dinámico de código realizado, la subrutina calcularFactores es la más crítica en cuestión de consumo de CPU. A su vez también la función sqtr(), que es parte del algoritmo de dicha subrutina.

![Analisis Dinamico](https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea03/primefact_optimization/report/analisis_dinamico.png)

**3.** _Modificaciones_

Se usará una versión de factorización por rueda con 2 y 3 como bases (se agrega la 3 debido a que el algoritmo anterior ya incluía base 2). Además, se intentará eliminar la operación de sqtr() actual; en su lugar, se eleverá el iterador al cuadrado, tal cuestión permite verificarar los números de 5^2 a la raíz cuadrada de n^2, evitando así realizar operaciones de punto flotante, que demandan un gran consumo de CPU.

**4.** _Rendimiento del código después de realizar las modificaciones_

Se obtuvo una duración de _104.88s_.

**5.** _Lecciones Aprendidas_

La diferencia entre los tiempos es de _60.29s_, lo cual es una gran diferencia a favor. A su vez el programa con solo una optimización tuvo un *speedup* y _efficiency_ respectivamente de _7.92_ y _0.99_, mientras que aplicando la segunda optimización se obtuvieron _12.48_ y _1.56_, esto representa en el programa un gran aumento a favor en todos los aspectos.

## _Comparación de Optimizaciones_

En general el caso más lento y menos eficiente corresponde al **serial**, este tuvo una duración de _1308.94s_; es un tiempo muy grande y se debe tomar en cuenta que solo se calcularon _40 061_ elementos. Con respecto a la **optimización 01** se obtuvo un incremento tanto a en el speedup como el efficiency, sin embargo no es tan grande, aún así considerando que se están utlizando una cantidad de recursos aproximadamente similares, definitivamente vale la pena incluir el mapeo dinámico. Finalmente la **optimización 02** es la que realmente marca un gran diferencia a favor del programa, modificar la subrutina de calcularFactores le brindó un speedup de _12.48s_ y una efficiency de _1.56_, estos son excelentes resultados que a su vez quedan retratados con la duración del programa, que es de tan solo _104.88s_. En general lo que produjo el ahora superior desempeño del programa fue: realizar un mapeo en tiempo de ejecución con el modelo productor-consumidor, utilizar una forma de factorización por rueda y evitar operaciones de punto flotante.

![Grafico Optimizations](https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea03/primefact_optimization/report/grafico_optimization.png)

## _Comparación de Grado de Concurrencia_

En el caso cuando se utiliza **1** solo hilo se puede observar que tiene una duración bastante extensa, sin embargo gracias a las optimizaciones, sigue siendo menor que su versión original serial. En el caso de **5C** y **1C*** se puede observar como su *speedup* es justamente la mitad del otro, es decir un comportamiento esperado ya que dura aproximadamente el doble, donde hay una diferencia es en su _efficiency_ donde inclusive **5C** supera, aunque por muy poco, a **1C**. En los de **2C** y **4C** se puede observar un patrón, mantienen una duración muy similar, sin embargo, a partir de este punto la _efficiency_ baja drasticamente, es decir ya se llegó al punto donde crear más hilos no afecta el desempeño de forma positiva. Finalmente con el caso **D** se puede concluir que crear una cantidad hilos igual a la cantidad de entradas no es _víable_, ya que un programa con entradas grandes (en este caso más de 40 000), es muy propenso a fallar, y tan siquiera poder cumplir con su principal objetivo. Dado que la maquina donde se realizan las pruebas no puede crear esta cantidad de hilos, se deciden crear _1000 hilos_; a partir de esto obtenemos un _speedup_ y _efficiency_ respectivamente de _12.53_ y _0.00_, con lo cual queda demostrado que a pesar de mantener una consistencia en el tiempo de duración, la _efficiency_ es extremadamente mala. En general la cantidad de hilos óptima para conseguir el **mejor rendimiento** serían tantos hilos como CPUs hay en la computadora que ejecuta el programa; con esa cantidad se tiene un balance adecuado estre _speedup_ y _efficiency_. Con menos haría que el programa tarde mucho y con más se estaría desperdiciando recursos por un resultado similar.

![Grafico Concurrencia](https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea03/primefact_optimization/report/grafico_concurrency_level.jpeg)

En la gráfica se puede notar como Pthreads superó a OpenMP, aún así obtuvieron resultados muy similares y la diferencia es de solo algunos segundos. Esta diferencia (en este caso), y por lo tanto eligir si se utiliza tecnología imperativa o declarativa recae en el programador, depende de las necesidades. Finalmente es importante mencionar la facilidad que conlleva implementar teclogía declarativa (OpenMP), en donde una línea de código realiza una tarea que con Pthreads requiere múltiples métodos.

![Grafico OMPvsPthreads](https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea04/primefact_omp_mpi/report/grafico_pthreadsVSopenmp.png)