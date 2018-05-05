#include <iostream>
#include <memory>
#include "Foo.h"

int main(int argc, char const *argv[])
{
	std::cout << "Instancio foo" << std::endl;
	std::shared_ptr<Foo> sp(new Foo());
	std::cout << "Cantidad de referencias: " << sp.use_count() << std::endl;
	{
		std::shared_ptr<Foo> internal = sp;
		std::cout << "Cantidad de referencias: " << sp.use_count() << std::endl;	
	}
	std::cout << "Cantidad de referencias: " << sp.use_count() << std::endl;
}