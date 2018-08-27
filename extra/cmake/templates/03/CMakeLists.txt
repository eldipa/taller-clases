cmake_minimum_required(VERSION 2.8)
project(cmake-example)

#Archivos del servidor
add_executable(example
  hello.cpp
)

###################
#  Configuracion  #
###################

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

# Puedo usar un target de compilación o archivos de todo tipo
install(TARGETS example DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
# Copio un archivo foo.txt al directorio de instalación
install(FILES foo.txt DESTINATION ${CMAKE_INSTALL_PREFIX}/etc/)

