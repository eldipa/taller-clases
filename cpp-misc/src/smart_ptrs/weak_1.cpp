#include <iostream>
#include <memory>


int main(int argc, char const *argv[])
{
    std::weak_ptr<int> weakPointer;
    std::shared_ptr<int> sharedPointer;

    {
        std::shared_ptr<int> internal(new int(5));
        std::cout << "Asignando internal a weakPointer" << std::endl;
        weakPointer = internal;
        // Lock genera un shared_ptr
        std::cout << "WeakPointer -> " << *weakPointer.lock() << std::endl;
        std::cout << "Usos: " <<internal.use_count() << std::endl;
        std::cout << "Creando el shared_ptr foo a partir de weakPointer" << std::endl;
        std::shared_ptr<int> foo = weakPointer.lock();
        std::cout << "Usos: " <<internal.use_count() << std::endl;
        std::cout << "Asignando internal a sharedPointer" << std::endl;
        sharedPointer = internal;
        std::cout << "Usos: " <<sharedPointer.use_count() << std::endl;
        std::cout << "SharedPointer -> " << *sharedPointer << std::endl;
    }
    std::cout << "Saliendo del bloque anonimo" << std::endl;
    std::cout << "Usos: " << sharedPointer.use_count() << std::endl;
    std::cout << "SharedPointer -> " <<*sharedPointer << std::endl;
    std::cout << "WeakPointer -> "  << *weakPointer.lock() << std::endl;
    std::cout << "Fin prueba de weak pointers" << std::endl;
    return 0;
}