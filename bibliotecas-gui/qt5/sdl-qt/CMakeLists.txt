project(qt-sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find the QtWidgets library
find_package(Qt5Widgets)

qt5_wrap_ui(UIS_HEADERS
  ui/mainWindow.ui
)

add_library(sdlqtexample
  src/Area.cpp
  src/SdlImage.cpp
  src/SdlWindow.cpp
)

message("Headers generados: ${UIS_HEADERS}")
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (sdl-standalone
  src/mainSDL.cpp  
)

add_executable (qt-standalone
  src/mainQt.cpp
  src/MainWindow.cpp
  ${UIS_HEADERS}
)

add_executable (qt-plus-sdl
  src/mainQtSDL.cpp
  src/MainWindow.cpp
  ${UIS_HEADERS}
)

target_link_libraries(qt-standalone Qt5::Widgets)
target_link_libraries(sdl-standalone sdlqtexample SDL2 SDL2_image)
target_link_libraries(qt-plus-sdl sdlqtexample Qt5::Widgets SDL2 SDL2_image)

install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
