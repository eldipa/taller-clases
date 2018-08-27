#include <iostream>
#include <memory>
#include "Foo.h" 

int main(int argc, char** argv) {
    std::cout << "Inicio prueba 2" << std::endl;
    std::cout << "Creando Foo en el heap" << std::endl;
    std::unique_ptr<Foo> ptrA(new Foo());
    std::cout << "Copiando puntero" << std::endl;
    // No compila porque la copia está prohibida
    // std::unique_ptr<Foo> ptrB(ptrA);
    std::unique_ptr<Foo> ptrB(std::move(ptrA));
    std::cout << "Liberando ptrA" << std::endl;
    ptrA.reset();
    std::cout << "Liberando ptrB" << std::endl;
    ptrB.reset();
    std::cout << "Fin prueba 2" << std::endl;
}

