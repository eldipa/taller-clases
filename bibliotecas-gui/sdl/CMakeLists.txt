cmake_minimum_required(VERSION 2.8)

project(qt-sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sdldemo
  src/Area.cpp
  src/SdlTexture.cpp
  src/SdlException.cpp
  src/SdlWindow.cpp
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (sdl-hello
  src/mainSdlHello.cpp  
)

add_executable (sdl-events
  src/mainSdlEvents.cpp
)


target_link_libraries(sdl-hello sdldemo SDL2 SDL2_image)
target_link_libraries(sdl-events sdldemo SDL2 SDL2_image)

install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
