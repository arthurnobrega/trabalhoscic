#include "Relatorio.h"

int contarNroBitsArquivo(FILE *arq) {
    char ch;
    int nroBits = 0;
    ch = fgetc(arq);
    while (!feof(arq)) {
        nroBits += 8;
        ch = fgetc(arq);
    }

    return nroBits;
}
