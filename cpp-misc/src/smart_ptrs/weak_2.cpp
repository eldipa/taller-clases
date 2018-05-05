#include <iostream>
#include <memory>


int main(int argc, char const *argv[])
{
    std::weak_ptr<int> weakPointer;

    {
        std::shared_ptr<int> internal(new int(5));
        weakPointer = internal;
        // Lock genera un shared_ptr
        std::cout << *weakPointer.lock() << std::endl;
        std::cout << "Usos: " <<internal.use_count() << std::endl;
        std::shared_ptr<int> foo = weakPointer.lock();
        std::cout << "Usos: " <<internal.use_count() << std::endl;
    }
    std::cout << "Saliendo del bloque anonimo" << std::endl;
    std::cout << *weakPointer.lock() << std::endl;
    std::cout << "Fin prueba de weak pointers" << std::endl;
    return 0;
}