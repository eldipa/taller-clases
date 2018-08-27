#include <iostream>
#include <memory>
#include "Foo.h" 

int main(int argc, char** argv) {
    std::cout << "Inicio prueba 1" << std::endl;
    std::cout << "Creando Foo en el heap" << std::endl;
    std::unique_ptr<Foo> ptrA(new Foo());
    std::cout << "Fin prueba 1" << std::endl;
}
