#ifndef STACK_H
#define STACK_H
#include <vector>
#include <ostream>

class StackTest;

class Stack {
public:
    void push(int i);
    int pop();
    unsigned int size() const;
private:
    // el keyword `friend` es independiente de si es privado o publico
    friend class StackTest;
    friend std::ostream& operator<< (std::ostream& stream, const Stack& stack);
    std::vector<int> buffer;
};

std::ostream& operator<< (std::ostream& stream, const Stack& stack);

#endif
