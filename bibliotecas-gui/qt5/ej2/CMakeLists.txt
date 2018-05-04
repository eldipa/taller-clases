project(qt5-demo)

# Find the QtWidgets library
find_package(Qt5Widgets)

add_executable(step-2
  Greeter.cpp
  main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(step-2 Qt5::Widgets)
