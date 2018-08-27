#include <iostream>

namespace {
  int local;
}

void func();

int main (int argc, char** argv) {
  local = 1;
  std::cout << local << std::endl;
  func();
  std::cout << local << std::endl;
}