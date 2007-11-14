#include "Arquivos.h"
#include <stdio.h>

void gravarCodigosHuffman(FILE *arq, no_arv *arv);

char buffer[8];
int tamanhoBuffer;

void compactarArquivoHuffman(char *narqEntrada, char *narqSaida, no_arv *arv) {
    FILE *arq;

    /* Cria o arquivo. */
    arqSaida = fopen(narqSaida, "wb+");
    fputs("H\n", arqSaida);
    gravarCodigosHuffman(arqEntrada, arv);
    arqEntrada = fopen(narqEntrada, "wb+");
    gravarCodificacao(arqEntrada, arqSaida, arv);
    fclose(arqEntrada);
    fclose(arqSaida);
}

void gravarTabelaCodigos(FILE *arq, no_arv *arv) {
    if (arv != NULL) {
	if (arv->caractere != CAR_ESP) {
	    int profundidade, i;
	    sprintf("%d ",arv->caractere);
	    profundidade = arv->profundidade;
	    for (i = 0; i <= profundidade - 1; i ++) {
		putc(arv->codigo[i], arq);
	    }
	    putc('\n', arq);
	}
	mostrarCodigos(arv->esq);
	mostrarCodigos(arv->dir);
    }
}

void gravarCodificacao(FILE *arq, no_arv *arv) {
    
}

no_arv *buscarNo(no_arv *arv, const char caractere) {
    no_arv *arv_teste;
    if (arv != NULL) {
	if (arv->caractere == caractere) {
	    return arv;
	} else {
	    if ((arv_teste = buscarNo(arv->esq, caractere)) != NULL) {
		return arv_teste;
	    } else if ((arv_teste = buscarNo(arv->dir, caractere)) != NULL) {
		return arv_teste;
	    }
	}
    }

    return NULL;
}








//te adoro juarez, me da 10 no trabalçho vai!
