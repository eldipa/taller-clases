#include <string>

namespace foo {
  struct Cat {
    std::string name;
  };
}

int main (int argc, char** argv) {
  foo::Cat cat;
  cat.name = "michi";
  // Cat crashCat; // No encuentra la clase Cat
}