# Configurar directorio de instalación

Hay variables que ya vienen configuradas por default, como por ejemplo `${CMAKE_INSTALL_PREFIX}`. Esta variable, en entornos unix por ejemplo, tiene como valor por defecto /usr/local.
Podemos utilizarla para definir un directorio de instalación de nuestros ejecutables y recursos necesarios para la aplicación.

## Definiendo archivos de instalación

Podemos seleccionar un ejecutable como archivo a instalar

~~~{.cmake}
install(TARGETS example DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
~~~

Archivos

~~~{.cmake}
install(FILES foo.txt DESTINATION ${CMAKE_INSTALL_PREFIX}/etc/)
~~~

U otros tipos de recursos, como carpetas, bibliotecas, paquetes, headers, etc.

## Compilación

Si compilamos como se hace habitualmente

~~~{.bash}
mkdir build
cd build
cmake ..
make
make install
~~~

Al hacer `make install` nuestro ejecutable intentará instalarse en los directorios default del sistema.

Si por ejemplo ejecutamos, por ejemplo

~~~{.bash}
cmake .. -DCMAKE_INSTALL_PREFIX=$PWD
make
make install
~~~

Nuestro ejecutable se intentará instalar en el directorio actual como raiz.
