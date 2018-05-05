# C++ Avanzado

Features y otros trucos que nos ofrece C++

* Namespaces

* Keyword *friend*

* Smart pointers

* Range-based *for*

---

## Namespaces

Permiten agrupar funciones, clases, variables, etc. para evitar colisión de nombres.

--

~~~{.cpp}
namespace {
  atributos y métodos
}
~~~

---

### Namespace std

El namespace mas conocido es el standard

~~~{.cpp}
#include <vector>
#include <iostream>

int main (int argc, char** argv) {
  std::vector<int> v;
  std::cout << "Hola" << std::endl;
}
~~~

---

### Usando namespaces

~~~{.cpp}
#include <vector>
#include <iostream>

using std::cout;

int main (int argc, char** argv) {
  using std::endl;

  std::vector<int> v;
  cout << "Hola" << endl;
}
~~~

--

~~~{.cpp}
int foo () {
  // cout << "Foo" << endl; No compila
  cout << "Foo" << std::endl; 
}
~~~


---

### Usando namespaces (parte 2)

~~~{.cpp}
#include <vector>
#include <iostream>

using namespace std;

int main (int argc, char** argv) {
  vector<int> v;
  cout << "Hola" << endl;
}
~~~

---

~~~{.cpp}
#include <vector>
#include <algorithm>

//using namespace std; // Descomentar provoca ambigüedad

int count = 0;

int main (int argc, char** argv) {
  std::vector<int> v{1,2,3,1,2,1};
  std::sort(v.begin(), v.end());
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == 1) {
      count++;
    } else {
      break;
    }
  }
}
~~~

Ver https://stackoverflow.com/questions/2712076/how-to-use-an-iterator/2712125

---

## Crear namespaces propios

~~~{.cpp}
#include <string>

namespace foo {
  struct Cat {
    std::string name;
  };
}

int main (int argc, char** argv) {
  foo::Cat cat;
  cat.name = "michi";
}
~~~

---

~~~{.cpp}
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
  Cat crashCat;
}
~~~

---

## Namespaces anónimos

Poseen un comportamiento muy similar al keyword `static`, limitando el alcance de las variables a la unidad de compilación

~~~{.cpp}
//file 4a.cpp
namespace {
  int local;
}

void func() {
  local = 2;
}
~~~

~~~{.cpp}
//file 4b.cpp
namespace {
  int local;
}

void func();

int main (int argc, char** argv) {
  local = 1;
  func();
}
~~~

---

## Referencias

C++ International Standard, sección 7.3

---

# Keyword Friend

--

Permite una forma más selectiva de romper el encapsulamiento de una clase

---

## Caso de ejemplo: armar un stack

~~~{.cpp}
class Stack {
public:
  void push(int i);
  int pop();
  unsigned int size() const;
private:
  std::vector<int> buffer;
};

class StackTest {
public:
  void testBuffer();
};
~~~

---

*¿Cómo hago para visualizar el contenido del buffer desde StackTest?*

--

~~~{.cpp}
class Stack {
public:
  void push(int i);
  int pop();
  unsigned int size() const;
private:
  friend class StackTest;
  std::vector<int> buffer;
};
~~~

~~~{.cpp}
void StackTest::testBuffer() {
  Stack s;
  if (s.buffer.empty()) {
    std::cout << "Stack ctor ok!" << std::endl;
  }
}
~~~

---

### Imprimir el contenido del stack usando un stream

Deseo poder ejecutar el siguiente código

~~~{.cpp}
Stack s;
std::cout << s << std::endl;
~~~

--

`std::ostream` no está especializado para `Stack`, por lo que debo definir el operador `operator<<` como una función externa.

~~~{.cpp}
std::ostream& operator<< (std::ostream& stream, const Stack& stack) {
  stream << "[";
  for (int i = 0; i < stack.buffer.size(); ++i) {
    stream << stack.buffer[i];
    /*...*/
  }
  return stream;
}
~~~

--

~~~{.cpp}
class Stack {
/*...*/
friend std::ostream& operator<< (std::ostream& stream, const Stack& stack);
}
~~~

---

# Smart Pointers

C++11 nos provee de punteros inteligentes:

* `unique_ptr`

* `shared_ptr`

* `weak_ptr`

---

## Unique_ptr

Encapsula un puntero a un objeto en el heap. Este puntero no es copiable, únicamente puede moverse.
Cuando el `unique_ptr` termina su ciclo de vida, destruye al objeto al que está apuntando

---

## Shared_ptr

Encapsula un puntero a un objeto en el heap. A diferencia del `unique_ptr`, posee un contador de referencias.
Cuando un `shared_ptr` es copiado (mediante asignación o constructor por copia), el contador es incrementado.
Cuando el puntero termina su ciclo de vida o se le asigna otro valor, se decrementa el contador.
Cuando el contador llega a 0, se libera el objeto apuntado.

---

## Weak_ptr

Es muy similar a `shared_ptr`, y está hecho para interactuar con ellos. Un `weak_ptr` puede apuntar a una dirección "gestionada" por un `shared_ptr`.
A diferencia del mismo, al asignarle un valor al `weak_ptr`, no se incrementa el contador de referencias del `shared_ptr`.
Esto es especialmente útil para evitar leaks por referencias circulares.
Para acceder a su contenido, el `weak_ptr` debe ser promocionado a `shared_ptr` de forma temporal.


---

# Otras lecturas interesantes

Acerca de las categorías de las expresiones en C++ (glvalues, rvalues, etc)

* http://en.cppreference.com/w/cpp/language/value_category

* http://www.stroustrup.com/terminology.pdf

* http://www.stroustrup.com/C++11FAQ.html#rval