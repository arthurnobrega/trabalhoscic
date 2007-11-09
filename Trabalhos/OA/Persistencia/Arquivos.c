#include "Arquivos.h"
#include <stdio.h>

void gravarCodigosHuffman(FILE *arq, no_arv *arv);

void compactarArquivoHuffman(char *nomeArq, no_arv *arv) {
    FILE *arq;

    /* Cria o arquivo. */
    arq = fopen(nomeArq, "w");
    fputs("H\n", arq);
    gravarCodigosHuffman(arq, arv);
    fclose(arq);
}

void gravarCodigosHuffman(FILE *arq, no_arv *arv) {
    int tamanho = 0,numero = 0, mask = 0;
    if (arv != NULL) {
	if (arv->caractere != CAR_ESP) {
	    tamanho = arv->tam_cod;
	    numero = arv->codigo;
	    mask = 1 << (tamanho - 1);
	    // Mostrar código como binário com o número de casas
	    //que está armazenado no campo profundidade.
	    fprintf(arq, "%d", arv->caractere);
	    fputc(' ', arq);
	    fputc(numero & mask ? '1' : '0', arq);
	    mask = (mask >> 1) & ~(1 << (tamanho - 1));
	    while (mask) {
		fputc(numero & mask ? '1' : '0', arq);
		mask >>= 1;
	    }
	    fputc('\n', arq);
	}
	gravarCodigosHuffman(arq, arv->esq);
	gravarCodigosHuffman(arq, arv->dir);
    }
}
