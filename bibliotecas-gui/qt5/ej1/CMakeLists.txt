project(qt5-demo)

# Find the QtWidgets library
find_package(Qt5Widgets)

add_executable(step-1
  main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(step-1 Qt5::Widgets)
