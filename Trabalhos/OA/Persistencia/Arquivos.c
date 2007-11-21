#include "Arquivos.h"

int abrirArquivo(FILE *arq, char *nomeArq, char *modo) {

    arq = fopen(nomeArq, modo);
    if (arq == NULL) {
	return 0;
    }

    return 1;
}
