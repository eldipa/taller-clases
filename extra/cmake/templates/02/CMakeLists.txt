cmake_minimum_required(VERSION 2.8)
project(cmake-example)

#Archivos del servidor
add_executable(example
  hello.cpp
)

###################
#  Configuracion  #
###################

# Puedo definir funciones desde la linea de comando ejecutando `cmake -D USER=Algo`

if(NOT USER)
  set(USER "Anon")
endif(NOT USER)

# Esta variable será levantada desde el template
message(STATUS "USER: ${USER}")

# El primero es el template, el segundo es el destino
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

