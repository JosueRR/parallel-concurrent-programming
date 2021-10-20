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

 El mapeo por bloque tuvo un speedup y efficiency respectivamente de 7.56 y 0.94, mientras que el dinámico 7.92 y 0.99, por lo tanto considerando que la implementación es relativamente sencilla y también los resultados del análisis, el mapeo dinámico es superior al estático por bloque, y a su vez da muy buenos resultados.