#include <string>

namespace animals {
  namespace mammals {
    namespace domestic {
      struct Cat {
        std::string name;
      };
    }
  }
}

namespace dom = animals::mammals::domestic;

int main (int argc, char** argv) {
  animals::mammals::domestic::Cat cat;
  dom::Cat otherCat;
}