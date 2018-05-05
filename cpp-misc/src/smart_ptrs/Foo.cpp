#include "Foo.h"
#include <iostream>

Foo::Foo() {
    std::cout << "Constructor Foo" << std::endl;
}

Foo::~Foo() {
    std::cout << "Destructor Foo" << std::endl;
}
