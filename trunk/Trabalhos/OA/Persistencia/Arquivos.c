#include "Arquivos.h"
#include <stdio.h>

void compactarArquivoHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int tamanho);
void gravarTabelaCodigos(FILE *arq, no_arv *arv);
void gravarCodificacao(FILE *arqEntrada, FILE *arqSaida, no_arv *arv);
no_arv *buscarNo(no_arv *arv, const char caractere);

unsigned char buffer = 0;
int tamanhoBuffer = 0;

void compactarArquivoHuffman(char *narqEntrada, char *narqSaida, no_arv *arv, int tamanho) {
    FILE *arqSaida, *arqEntrada;
    char temp[TAM_MAX];

    /* Abre o arquivo de Entrada. */
    arqEntrada = fopen(narqEntrada, "r");
    /* Cria o arquivo de Saída. */
    arqSaida = fopen(narqSaida, "wb");

    fwrite("H\n", 2, 2 , arqSaida);
    sprintf(temp, "%d", tamanho);
    fwrite(temp, sizeof(temp), 1, arqSaida);
    gravarTabelaCodigos(arqSaida, arv);
    gravarCodificacao(arqEntrada, arqSaida, arv);
    fclose(arqEntrada);
    fclose(arqSaida);
}

void gravarTabelaCodigos(FILE *arqSaida, no_arv *arv) {
    if (arv->esq == NULL) {
	int profundidade, i;
	char temp[1];

	temp[0] = arv->caractere;
	fwrite(temp, 1, 1, arqSaida);
	profundidade = arv->profundidade;
	for (i = 0; i <= profundidade - 1; i++) {
	    temp[0] = arv->codigo[i];
	    fwrite(temp, 1, 1, arqSaida);
	}
	fwrite("\n", 1, 1, arqSaida);
    } else {
	gravarTabelaCodigos(arqSaida, arv->esq);
	gravarTabelaCodigos(arqSaida, arv->dir);
    }
}

void gravarCodificacao(FILE *arqEntrada, FILE *arqSaida, no_arv *arv) {
    char ch;
    no_arv *no;
    int profundidade, i;
    char temp[1];

    while ((ch = fgetc(arqEntrada)) != EOF) {
	no = buscarNo(arv, ch);
	profundidade = no->profundidade;
	for (i = 0; i <= profundidade - 1; i++) {
	    buffer <<= 1;
	    if (no->codigo[i] == '1') {
		buffer |= 1;
	    }
	    tamanhoBuffer++;
	    if (tamanhoBuffer == 8) {
		temp[0] = buffer;
		fwrite(temp, 1, 1, arqSaida);
		buffer = 0;
		tamanhoBuffer = 0;
	    }
	}
    }
}

no_arv *buscarNo(no_arv *arv, const char caractere) {
    no_arv *no;
    if (arv->esq == NULL) {
	if (arv->caractere == caractere) {
	    return arv;
	}
    } else {
	if ((no = buscarNo(arv->esq, caractere)) != NULL) {
	    return no;
	} else if ((no = buscarNo(arv->dir, caractere)) != NULL) {
	    return no;
	}
    }
    return NULL;
}
