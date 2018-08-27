# CSum

Wrapper en python para una función que suma enteros en C.

## Instrucciones

Para compilar, ejecutar `make`.

Para correr, ejecutar `python3 cSum.py`, es necesario que esté compilada la biblioteca dinámica.

## ¿Cómo funciona?

Compilamos nuestra biblioteca dinámica con los siguientes flags:

* `-fPIC`: *Position independent code*, codigo reubicable para ser cargado dinámicamente.

* `-shared`: Para que la salida sea una biblioteca dinámica en vez de un ejecutable.

Y utilizamos la biblioteca *ctypes* de python para interactuar con nuestra biblioteca de C

Ejemplo:

~~~{.python}
# Cargo la dll
_sumDLL = ctypes.CDLL('./libsum.so')
# Configuro la firma de mi función sum
_sumDLL.sum.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
~~~

## Ventajas y desventajas

La biblioteca ctypes nos permite interactuar con bibliotecas compiladas, no solo en C, sino en otros lenguajes como Fortran, C++, Rust, Go, etc.

Python es un lenguaje de alto nivel muy flexible e intuitivo. El uso de lenguajes de más bajo nivel nos ayuda a combatir cuellos de botella que vayamos encontrando en la ejecución de nuestra aplicación.

Los lenguajes de más bajo nivel en general poseen un control de memoria más fuerte, y además permiten concurrencia mediante hilos, cosa que en Python no es del todo real debido al Global Interpreter Lock (*GIL*)

Por otro lado, la comunicación entre el entorno de python y la interfaz de ctypes es bastante lenta debido a la necesidad de crear wrappers para las estructuras nativas de C. Es recomendable minimizar la cantidad de conversiones de un tipo de dato a otro.
