# OrderNums

Wrapper en python para una función que ordena numeros de 4 dígitos.
/
## Instrucciones

Para compilar, ejecutar `make`.

Para generar un archivo de prueba, ejecutar `python3 test/genData.py <archivo>`

Para correr, ejecutar `python3 main.py <archivo>`, es necesario que esté compilada la biblioteca dinámica.

## Cambios

Al igual que en cSum, compilamos una biblioteca dinámica con la que interactuamos mediante ctypes.

En esta aplicación utilizamos una biblioteca compilada con C++. Cuando compilamos código C++, el código objeto y bibliotecas que se generan tienen los nombres de las funciones con la firma completa. Esta forma de almacenar las entradas de las funciones se conoce como *name mangling*. Para desactivar el *mangling* y que nuestras funciones de C++ sean compatibles con C, envolvemos nuestra función con `extern "C" {}`

También utilizamos un struct plano (es decir, sin métodos ni nada propio de C++), para que sea compatible con C.

En el modulo de python utilizamos `ctypes.Structure` para armar un struct compatible con el de C++ (que a su vez es compatible con C). Los strings se representan con un char*.


## Notas

La aplicación ejecuta un algoritmo de ordenamiento tanto en C como en Python. Al evaluar el performance de ambos, se puede ver que el algoritmo en C es más lento. Si se realiza un profile del ordenamiento en C, se puede apreciar que la llamada a C tarda aproximadamente el 10% del tiempo, y el otro 90% es la conversión de objetos Python a los compatibles con C y viceversa.

Por este motivo, se remarca que esta conversión es costosa y debe evitarse lo mayor posible.

### Profiling

Un *profile* es un informe de los tiempos de ejecución de una aplicación

Para realizar un profile de una función en python se puede utilizar una herramienta llamada *kernprof*. *Kernprof* se instala con *pip*, para ejecutarlo sólamente tenemos que anteponer `kernprof -l` a la llamada de nuestro script. Esto nos genera un archivo con el mismo nombre que el script más la extensión *.lprof*.
Este archivo luego puede ser abierto con el modulo *line_profiler*, ejecutando `python -m line_profiler <script>`

Marcamos las funciones que queremos evaluar colocando la anotación `@profile` arriba de donde la definimos.