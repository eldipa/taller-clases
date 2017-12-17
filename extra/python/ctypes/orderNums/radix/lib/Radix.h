#ifndef RADIX_H
#define RADIX_H

#include <vector>

// Parte visible de la biblioteca

extern "C" {
    struct MyVector {
    char** data;
    int size;
    };

    void sort(MyVector vector);
}

class Radix {
public:
    Radix(char** values, int size);
    void sort();
private:
    std::vector<std::vector<char*> > buildBuckets(int size) const;
    char** values;
    int size;
};

#endif