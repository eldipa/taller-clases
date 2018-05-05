#include <vector>
#include <iostream>

using std::cout;

int main (int argc, char** argv) {
  using std::endl;

  std::vector<int> v;
  cout << "Hola" << endl;
  return 0;
}

int foo () {
  // cout << "Hola" << endl; No compila
  cout << "Hola" << std::endl; 
  return 0;
}
