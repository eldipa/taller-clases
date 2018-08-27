cmake_minimum_required(VERSION 2.6)
project(cpp-misc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -ggdb")

add_executable(ej0
  ej0.cpp
)

add_executable(ej1
  ej1.cpp
)

add_executable(ej2
  ej2.cpp
)

add_executable(ej3
  ej3.cpp
)

add_executable(ej4
  ej4a.cpp
  ej4b.cpp
)