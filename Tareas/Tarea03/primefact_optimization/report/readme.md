# Documento de Reporte
## _Aspectos Generales_
Para realizar el reporte se utilizó el caso de prueba **input021.txt**, que cuanta con 40 061 elementos a procesar.

## _Optimización 01 - Mapeo dinámico_

**1.** _Rendimiento del código antes de realizar las modificaciones_

Utilizando una mapeo estático de tipo bloque no balanceado se obtuvo una duración de _173.18s_.

**2.** _Profiling_

En este caso no es necesario ya que es impuesto en el enunciado.

**3.** _Modificaciones_

Se implementará un modelo de mapeo dinámico productor-consumidor que utilizará variables contadoras compartidas.

**4.** _Rendimiento del código después de realizar las modificaciones_

Utilizando una mapeo dinámico se obtuvo una duración de _165.18s_.

**5.** _Lecciones Aprendidas_

 El mapeo por bloque tuvo un *speedup* y _efficiency_ respectivamente de _7.56_ y _0.94_, mientras que el dinámico _7.92_ y _0.99_, por lo tanto considerando que la implementación es relativamente sencilla y también los resultados del análisis, el mapeo dinámico es superior al estático por bloque, y a su vez da muy buenos resultados.

 ## _Optimización 02 - Calcular Factores_

**1.** _Rendimiento del código antes de realizar las modificaciones_

El proyecto post-optim01 obtuvo una duración de _165.18s_.

**2.** _Profiling_

Como se puede observer en el análisis dinámico de código realizado la subrutina calcularFactores es la más crítica en cuestión de consumo de CPU. A su vez también la función sqtr(), que es parte del algoritmo de dicha subrutina.

![Analisis Dinamico](https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea03/primefact_optimization/report/analisis_dinamico.png)

**3.** _Modificaciones_

Siguiendo el consejo del profesor se usará una versión de factorización por rueda con 2 y 3 como bases (se agrega la 3 debido a que el algoritmo anterior ya incluía base 2). Además, se intentará eliminar la operación de sqtr() actual; en su lugar, se eleverá el iterador al cuadrado, tal cuestión permite verificarar los números de 5^2 a la raíz cuadrada de n^2, evitando así realizar operaciones de punto flotante, que demandan un gran consumo de CPU.

**4.** _Rendimiento del código después de realizar las modificaciones_

Se obtuvo una duración de _104.88s_.

**5.** _Lecciones Aprendidas_

La diferencia entre los tiempos es de _60.29s_, lo cual es una gran diferencia a favor. A su vez el programa con solo una optimización tuvo un *speedup* y _efficiency_ respectivamente de _7.92_ y _0.99_, mientras que aplicando la segunda optimización se obtuvieron _12.48_ y _1.56_, esto representa en el programa un gran aumento a favor en todos los aspectos.

## _Comparación de Optimizaciones_

En general el caso más lento y menos eficiente corresponde al **serial**, este tuvo una duración de _1308.94s_; es un tiempo muy grande y se debe tomar en cuenta que solo se calcularon _40 061_ elementos. Con respecto a la **optimización 01** se obtuvo un incremento tanto a en el speedup como el efficiency, sin embargo no es tan grande, aún así considerando que se están utlizando una cantidad de recursos aproximadamente similares, definitivamente vale la pena incluir el mapeo dinámico. Finalmente la **optimización 02** es la que realmente marca un gran diferencia a favor del programa, modificar la subrutina de calcularFactores le brindó un speedup de _12.48s_ y una efficiency de _1.56_, estos son excelentes resultados que a su vez quedan retratados con la duración del programa, que es de tan solo _104.88s_. En general lo que produjo el ahora superior desempeño del programa fue: realizar un mapeo en tiempo de ejecución con el modelo productor-consumidor, utilizar una forma de factorización por rueda y evitar operaciones de punto flotante.

![Grafico Optimizations](https://github.com/JosueRR/ppc21b-04-josue_retana/blob/master/Tareas/Tarea03/primefact_optimization/report/grafico_optimization.png)