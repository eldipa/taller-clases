# Archivos .in

Creamos un archivo `config.h.in` que funcionará como *template* para crear un archivo `config.h`.
Las variables van a ser escritas con el formato `@NOMBRE_VAR@`, y el valor lo definiremos en el archivo CMakeLists.txt llamando a la función `set(NOMBRE_VAR "valor")`

Para indicar qué un archivo template debe ser procesado, utilizamos la función `configure_file(<template> <destino>)`

## Compilación

Compilamos como se hace habitualmente

~~~{.bash}
mkdir build
cd build
cmake ..
make
~~~
