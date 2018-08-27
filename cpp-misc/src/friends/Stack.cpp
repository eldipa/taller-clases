#include "Stack.h"
#include <ostream>

void Stack::push(int i) {
    this->buffer.push_back(i);
}

int Stack::pop() {
    int i = this->buffer.back();
    this->buffer.pop_back();
    return i;
}

unsigned int Stack::size() const {
    return this->buffer.size();
}

std::ostream& operator<< (std::ostream& stream, const Stack& stack) {
  stream << "[";
  if (!stack.buffer.empty()) {
    stream << stack.buffer[0];
  }
  for (unsigned int i = 1; i < stack.buffer.size(); ++i) {
    stream << ", " << stack.buffer[i];
  }
  stream << "]";
  return stream;
}
