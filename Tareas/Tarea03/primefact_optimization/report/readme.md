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

Se intentará eliminar la operación de sqtr() actual; en su lugar, se eleverá el iterador al cuadro, tal cuestión permite verificarar los números de 3^2 a la raíz cuadrada de n^2, evitando así realizar operaciones de punto flotante que demandan un gran consumo de CPU.

**4.** _Rendimiento del código después de realizar las modificaciones_

Se obtuvo una duración de _?_.

**5.** _Lecciones Aprendidas_

 not_yet.