#include <stdio.h>

int sum(int* values, int size);

int main(int argc, char** argv) {
    int values[4] = {1, 2, 5, 7};
    int result = sum(values, 4);
    printf("Test [1, 2, 5, 7] = %d\n", result);
    return 0;
}
