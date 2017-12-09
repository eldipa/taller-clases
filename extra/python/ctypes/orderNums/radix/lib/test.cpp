#include <vector>
#include "Radix.h"

int main() {
    std::vector<char*> v;
    char* a = "1234";
    char* b = "3231";
    char* c = "1133";
    char* d = "1324";
    MyVector mv;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);
    mv.data = v.data();
    mv.size = 4;
    sort(mv);
}

