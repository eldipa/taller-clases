# Variables con valor default

Tomamos los mismos archivos del paso anterior, pero esta vez verificamos si la variable template está definida. Si no lo está, le asignamos un valor default.

~~~{.cmake}
if(NOT USER)
  set(USER "Anon")
endif(NOT USER)
~~~

## Compilación

Si compilamos como se hace habitualmente

~~~{.bash}
mkdir build
cd build
cmake ..
make
~~~

Nuestra variable `USER` toma el valor `Anon`

Si por ejemplo ejecutamos, por ejemplo

~~~{.bash}
cmake .. -DUSER=Pepe
make
~~~

Nuestra variable `USER` toma el valor `Pepe`
