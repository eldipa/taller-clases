cmake_minimum_required(VERSION 2.8)

project(sockets)

set (CMAKE_C_STANDARD "99")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors")

add_executable(00-create 00-create.c)

add_executable(01-connect 01-connect.c)

add_executable(02-getaddrinfo 02-getaddrinfo.c)

add_executable(03-send-recv 03-send-recv.c)
