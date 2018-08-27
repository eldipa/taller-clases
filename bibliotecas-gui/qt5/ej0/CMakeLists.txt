project(qt5-demo)

# Busca el módulo Widgets de la biblioteca Qt5
# en particular toma la configuración de /usr/lib/x86_64-linux-gnu/cmake/Qt5/Qt5WidgetsConfig.cmake

# find_package(Qt5 COMPONENTS Widgets Core <...>) es una forma más feliz de
# agregar paquetes, ver https://blog.kitware.com/cmake-finding-qt5-the-right-way/
find_package(Qt5Widgets)

add_executable(step-0
  main.cpp)

# Linkea libQt5Widgets.so al ejecutable
target_link_libraries(step-0 Qt5::Widgets)
