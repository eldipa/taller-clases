
#include <cstdio>
#include <time.h>
#include <sys/time.h>
#include <cstdlib>

#define DATA_FILENAME "numeros.dat"

#define NUMEROS         1573888
#define PUNTOS          NUMEROS/2
#define SEGMENTOS       PUNTOS/2

#define ROUNDS 1000

typedef struct {
    int x;
    int y;
} Punto;

typedef struct {
    Punto a;
    Punto b;
} Segmento;

int main(int argc, char* argv[]) {
    Segmento* segmentos = (Segmento*) malloc(sizeof(Segmento) * SEGMENTOS);

    FILE *f = fopen(DATA_FILENAME, "rb");
    if (!f) return -1;

    for (int i = 0; i < SEGMENTOS; ++i) {
        fread(&segmentos[i], 4, 4, f);
    }

    fclose(f);

    struct timeval begin;
    gettimeofday(&begin, NULL);

    int max_norma_al_cuadrado = 0;
    int max_segmento_i = 0;
    for (int r = 0; r < ROUNDS; ++r) {
        for (int i = 0; i < SEGMENTOS; ++i) {
            int norma_al_cuadrado =
                (segmentos[i].a.x - segmentos[i].b.x) * (segmentos[i].a.x - segmentos[i].b.x) +\
                (segmentos[i].a.y - segmentos[i].b.y) * (segmentos[i].a.y - segmentos[i].b.y);
            if (norma_al_cuadrado > max_norma_al_cuadrado) {
                max_segmento_i = i;
                max_norma_al_cuadrado = norma_al_cuadrado;
            }
        }
    }

    struct timeval end;
    gettimeofday(&end, NULL);
    unsigned long long elapsed = 1000 * (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000;

    printf("Segmento mas largo: %i\n", max_segmento_i);
    printf("Procesado en %llu milisegundos.\n", elapsed);

    free(segmentos);

    return 0;
}

