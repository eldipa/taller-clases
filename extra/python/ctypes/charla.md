# Python + ctypes

## Caso de estudio: Algoritmo de sufijos DC3

### Descripción breve del algoritmo

El algoritmo para construir arrays de sufijos **DC3** funciona, de forma muy resumida, de la siguiente manera:

    DC3:
    Armo un array con los índices 3n+1 y 3n+2 del texto, al que llamamos B12.
    Ordeno estos índices de forma que las triplas que indexan estén ordenadas
    Si dos índices apuntan a triplas iguales, aplico recursivamente.
    Armo un array con los índices 3n (B0)
    Mergeo B0 y B12 utilizando B12 para desempatar colisiones en B0
    Devuelvo los índices ordenados

Si asumimos que B12 se ordena en O(N) (por ejemplo, usando *RadixSort*, por teorema del maestro se comprueba que el órden del algoritmo es O(N)

### Estructuras utilizadas

Se utilizó un **array en memoria** para almacenar el texto, cada caracter fue representado como un entero. Se utilizó otro array de enteros para almacenar índices.
Los buckets para el radix-sort se organizaron en **vectores de vectores**.

### Primeras pruebas

Las primeras pruebas del algoritmo obviamente no funcionaban, por lo que se fue emparchando el script hasta lograr que indexe. Esto llevó a un **código mal estructurado y extenso**. Se corrieron pruebas con profiler, llegando a tiempos como los siguientes:


| Números aleatorios | 100K  | 200K  | 400K  | 800K  | 1.6M  | 3.2M  |
| ------------------ | ----- | ----- | ----- | ----- | ----- | ----- |
| Tiempo (s)         | 7.726 | 22.2  | 37.05 | 78.41 | 171.8 | 352.2 |

#### Resultados del profiler

El siguiente es uno de los resultados devueltos por el *profiler* al indexar 3.2M números aleatorios:

~~~
51437160 function calls (51437156 primitive calls) in 354.489 seconds

   Ordered by: internal time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        6   78.969   13.162   79.184   13.197 dc3.py:155(_createRadix)
        3   49.855   16.618   84.355   28.118 dc3.py:126(merge)
        3   42.560   14.187   45.561   15.187 dc3.py:172(_sortAndFilter)
      3/1   35.032   11.677  292.811  292.811 dc3.py:58(radixSortB12)
  6755549   31.033    0.000   31.033    0.000 dc3.py:208(_isB0first)
  4503703   22.427    0.000   22.427    0.000 dc3.py:201(_b12ToIndex)
        6   21.343    3.557   28.850    4.808 dc3.py:165(_sortTriplet)
  4503703   17.589    0.000   17.589    0.000 dc3.py:194(_indexToB12)
 32474071   17.039    0.000   17.039    0.000 {method 'append' of 'list' objects}
        3   10.665    3.555   54.870   18.290 dc3.py:108(radixSortB0)
~~~

Como se puede apreciar, la función que más tiempo tomó fue _createRadix, que se encarga de **crear una lista de listas** del tamaño del "alfabeto".
La siguiente función es *merge*, que realiza un apareo entre 2 listas.

### Identificar qué optimizar

#### Optimizaciones triviales

Si bien algunas funciones claramente toman más tiempo que otras, también es bueno identificar qué optimizaciones son triviales, por ejemplo:
* *División de enteros*: ¿El resultado de la división devuelve un entero o un flotante? ¿Estoy utilizando el operador correcto?
* *Constantes calculadas*: ¿Estoy consultando un valor constante? Ej: len(array)

## Primer optimización: sortTriplet

La función elegida a optimizar claramente fue _createRadix. En vez de optimizarla para que corra más rápido, se buscó la forma de directamente eliminarla.
La primer optimización que se aplicó fue la de migrar *sortTriplet* de python a C++ ¿Por qué? porque la mitad de las llamadas a createRadix se ejecutan ahí.
Se implementó *radixSort* en C++, de forma tal que la creación del radix se haga en C++.

### Comunicación entre C(C++) y Python

Python se comunica a módulos de C a través del módulo **ctypes**.
*ctypes* permite cargar una biblioteca dinámica y llamar a la api de C que provea. Para esto también nos permite trabajar con tipos nativos de C.

