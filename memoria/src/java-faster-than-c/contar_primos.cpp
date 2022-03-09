
#include <cstdio>
#include <time.h>
#include <sys/time.h>

#define DATA_FILENAME "numeros.dat"

#define NUMEROS 1573888
#define MAX        1023

int main(int argc, char* argv[]) {
    int numeros[NUMEROS];
    bool es_primo[NUMEROS] = {0};

    FILE *f = fopen(DATA_FILENAME, "rb");
    if (!f) return -1;

    for (int i = 0; i < NUMEROS; ++i) {
        fread(&numeros[i], 4, 1, f);
    }

    fclose(f);

    struct timeval begin;
    gettimeofday(&begin, NULL);

    for (int divisor = 2; divisor < MAX; ++divisor) {
        for (int i = 0; i < NUMEROS; ++i) {
            if (es_primo[i] || divisor >= numeros[i]) {
                continue;
            }
            else {
                if (numeros[i] % divisor == 0) {
                    es_primo[i] = true;
                    continue;
                }
            }
        }
    }

    struct timeval end;
    gettimeofday(&end, NULL);
    unsigned long long elapsed = 1000 * (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000;

    int cant_primos = 0;
    for (int i = 0; i < NUMEROS; ++i) {
        if (es_primo[i]) {
            ++cant_primos;
        }
    }

    printf("Hay %i primos.\n", cant_primos);
    printf("Procesado en %llu milisegundos.\n", elapsed);
    
    return 0;
}
