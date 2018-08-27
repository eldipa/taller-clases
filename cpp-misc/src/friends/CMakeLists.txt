cmake_minimum_required(VERSION 2.6)
project(cpp-misc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -ggdb")

add_executable(ejFriends
  Stack.cpp
  StackTest.cpp
  main.cpp
)
