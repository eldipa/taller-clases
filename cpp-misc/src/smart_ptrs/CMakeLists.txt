cmake_minimum_required(VERSION 2.6)
project(cpp-misc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -ggdb")

add_executable(unique_ptr_1
  Foo.cpp
  unique_ptr_1.cpp
)

add_executable(unique_ptr_2
  Foo.cpp
  unique_ptr_2.cpp
)

add_executable(shared_ptr
  Foo.cpp
  shared_ptr.cpp
)

add_executable(weak_ptr_1
  Foo.cpp
  weak_1.cpp
)

add_executable(weak_ptr_2
  Foo.cpp
  weak_2.cpp
)