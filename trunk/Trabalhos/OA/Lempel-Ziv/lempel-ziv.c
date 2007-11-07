#include <stdio.h>
#include <stdlib.h>

struct no_arv {
    unsigned char caractere;
    struct no_arv *ant;
    struct no_arv *prox;
};

typedef struct no_arv no_arv;

int main() {
    int tamanho = 6;
    int numero = 32;
    int mask = 1 << (tamanho - 1);
    putchar(numero & mask ? '1' : '0');
    mask = (mask >> 1) & ~(1 << (tamanho - 1));
    do {
	putchar(numero & mask ? '1' : '0');
    } while (mask >>= 1);
    putchar('\n');
    return 0;
}
