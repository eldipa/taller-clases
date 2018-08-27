#include "StackTest.h"
#include "Stack.h"
#include <iostream>
#include <sstream>

void StackTest::testSize() const {
    Stack stack;
    stack.push(9);
    if (stack.buffer.size() != 1) {
        std::cerr << "ERROR! buffer.size != 1" << std::endl;
        return;
    }
    std::cout << "testSize ok!" << std::endl;
}

// Uso un string stream porque podría testear contra el string generado...
void StackTest::testToStream() const {
    Stack stack;
    std::stringstream stream;
    // Imprime stack vacio
    stream << stack;
    std::cout << stream.str() << std::endl;
    // Reseteo stream
    stream.str(std::string());
    stream.clear();
    stack.push(1);
    // Imprime [1]
    stream << stack;
    std::cout << stream.str() << std::endl;
    stream.str(std::string());
    stream.clear();
    // Imprime [20]
    stack.push(20);
    stream << stack;
    std::cout << stream.str() << std::endl;
    std::cout << "testToStream ok!" << std::endl;
}
