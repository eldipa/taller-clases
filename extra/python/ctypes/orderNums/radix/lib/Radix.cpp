#include "Radix.h"
#include <vector>

#define ALPHA 10
#define MAX_LEN 4

extern "C" {

void sort(MyVector vector) {
    // Puedo instanciar objetos felizmente
    Radix radix(vector.data, vector.size);
    // Hace un ordenamiento in-place, solo con fines didacticos
    radix.sort();
}

}


Radix::Radix(char** values, int size) : values(values), size(size) {}

void Radix::sort() {
    auto bucketList = buildBuckets(ALPHA);
    for (int charIdx = MAX_LEN - 1; charIdx >= 0; --charIdx){
        for (int valueIdx = 0; valueIdx < this->size; ++valueIdx) {
            char* value = values[valueIdx];
            int bucketIdx = value[charIdx] - 48;
            bucketList[bucketIdx].push_back(value);
        }
         // Ahora plancho el radix
        int offset = 0;
        for (int bIdx = 0; bIdx < ALPHA; ++bIdx) {
            std::copy(bucketList[bIdx].begin(),
                      bucketList[bIdx].end(),
                      this->values + offset);
            offset += bucketList[bIdx].size();
            bucketList[bIdx].clear();
        }
    }
}

std::vector<std::vector<char*> > Radix::buildBuckets(int size) const {
    std::vector<std::vector<char*> > buckets(size);
    return buckets;
}
